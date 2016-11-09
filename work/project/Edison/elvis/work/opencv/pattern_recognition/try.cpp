#include <stdio.h>
#include <string.h>
#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/highgui.h>
#include <opencv/ml.h>
#include <opencv2/face.hpp>

using namespace cv;

//globle variables
int nTrainFaces         = 0;    // number of trainning images
int nEigens             = 0;    // number of eigenvalues
IplImage** faceImgArr       = 0;    // array of face images
CvMat* personNumTruthMat    = 0;    // array of person numbers
IplImage* pAvgTrainImg      = 0;    // the average image
IplImage** eigenVectArr     = 0;    // eigenvectors
CvMat* eigenValMat      = 0;    // eigenvalues
CvMat* projectedTrainFaceMat    = 0;    // projected training faces

//// Function prototypes
void learn();
void recognize();
void doPCA();
void storeTrainingData();
int loadTrainingData(CvMat** pTrainPersonNumMat);
int findNearestNeighbor(float* projectedTestFace);
int loadFaceImgArray(char* filename);
void printUsage();

int main( int argc, char** argv )
{
    if((argc != 2) && (argc != 3)){
        printUsage();
        return -1;
    }

    if( !strcmp(argv[1], "train" )){
        learn();
    } else if( !strcmp(argv[1], "test") ){
        recognize();
    } else {
        printf("Unknown command: %s\n", argv[1]);
    }
    return 0;
}

void printUsage(){
    printf("Usage: eigenface <command>\n",
           "  Valid commands are\n"
           "    train\n"
           "    test\n"
           );
}

void learn(){
    int i;
    // load training data
    nTrainFaces = loadFaceImgArray("train.txt");
    if( nTrainFaces < 2){
        fprintf(
                stderr,
                "Need 2 or more training faces\n"
                "Input file contains only %d\n",
                nTrainFaces
                );
        return;
    }

    // do PCA on the training faces
    doPCA();

    // project the training images onto the PCA subspace
    projectedTrainFaceMat = cvCreateMat(nTrainFaces, nEigens, CV_32FC1);
    for(i = 0; i < nTrainFaces; i ++){
        cvEigenDecomposite(
                           faceImgArr[i],
                           nEigens,
                           eigenVectArr,
                           0, 0,
                           pAvgTrainImg,
                           projectedTrainFaceMat->data.fl + i*nEigens
                           );
    }

    // store the recognition data as an xml file
    storeTrainingData();
}

int loadFaceImgArray(char* filename){
    FILE* imgListFile = 0;
    char imgFilename[512];
    int iFace, nFaces = 0;

    // open the input file
    imgListFile = fopen(filename, "r");

    // count the number of faces
    while( fgets(imgFilename, 512, imgListFile) ) ++ nFaces;
    rewind(imgListFile);

    // allocate the face-image array and person number matrix
    faceImgArr = (IplImage **)cvAlloc( nFaces*sizeof(IplImage *) );
    personNumTruthMat = cvCreateMat( 1, nFaces, CV_32SC1 );

    // store the face images in an array
    for(iFace=0; iFace<nFaces; iFace++){
        //read person number and name of image file
        fscanf(imgListFile, "%d %s", personNumTruthMat->data.i+iFace, imgFilename);

        // load the face image
        faceImgArr[iFace] = cvLoadImage(imgFilename, CV_LOAD_IMAGE_GRAYSCALE);
    }

    fclose(imgListFile);

    return nFaces;
}

void doPCA(){
    int i;
    CvTermCriteria calcLimit;
    CvSize faceImgSize;

    // set the number of eigenvalues to use
    nEigens = nTrainFaces - 1;

    // allocate the eigenvector images
    faceImgSize.width = faceImgArr[0]->width;
    faceImgSize.height = faceImgArr[0]->height;
    eigenVectArr = (IplImage**)cvAlloc(sizeof(IplImage*) * nEigens);
    for(i=0; i<nEigens; i++){
        eigenVectArr[i] = cvCreateImage(faceImgSize, IPL_DEPTH_32F, 1);
    }

    // allocate the eigenvalue array
    eigenValMat = cvCreateMat( 1, nEigens, CV_32FC1 );

    // allocate the averaged image
    pAvgTrainImg = cvCreateImage(faceImgSize, IPL_DEPTH_32F, 1);

    // set the PCA termination criterion
    calcLimit = cvTermCriteria( CV_TERMCRIT_ITER, nEigens, 1);

    // compute average image, eigenvalues, and eigenvectors
    cvCalcEigenObjects(
                       nTrainFaces,
                       (void*)faceImgArr,
                       (void*)eigenVectArr,
                       CV_EIGOBJ_NO_CALLBACK,
                       0,
                       0,
                       &calcLimit,
                       pAvgTrainImg,
                       eigenValMat->data.fl
                       );
}

void storeTrainingData(){
    CvFileStorage* fileStorage;
    int i;

    // create a file-storage interface
    fileStorage = cvOpenFileStorage( "facedata.xml", 0, CV_STORAGE_WRITE);

    // store all the data
    cvWriteInt( fileStorage, "nEigens", nEigens);
    cvWriteInt( fileStorage, "nTrainFaces", nTrainFaces );
    cvWrite(fileStorage, "trainPersonNumMat", personNumTruthMat, cvAttrList(0, 0));
    cvWrite(fileStorage, "eigenValMat", eigenValMat, cvAttrList(0,0));
    cvWrite(fileStorage, "projectedTrainFaceMat", projectedTrainFaceMat, cvAttrList(0,0));
    cvWrite(fileStorage, "avgTrainImg", pAvgTrainImg, cvAttrList(0,0));

    for(i=0; i<nEigens; i++){
        char varname[200];
        sprintf( varname, "eigenVect_%d", i);
        cvWrite(fileStorage, varname, eigenVectArr[i], cvAttrList(0,0));
    }

    //release the file-storage interface
    cvReleaseFileStorage( &fileStorage );
}

void recognize(){
    int i, nTestFaces = 0;      // the number of test images
    CvMat* trainPersonNumMat = 0;   // the person numbers during training
    float* projectedTestFace = 0;

    // load test images and ground truth for person number
    nTestFaces = loadFaceImgArray("test.txt");
    printf("%d test faces loaded\n", nTestFaces);

    // load the saved training data
    if( !loadTrainingData( &trainPersonNumMat ) ) return;

    // project the test images onto the PCA subspace
    projectedTestFace = (float*)cvAlloc( nEigens*sizeof(float) );
    for(i=0; i<nTestFaces; i++){
        int iNearest, nearest, truth;

        // project the test image onto PCA subspace
        cvEigenDecomposite(
                           faceImgArr[i],
                           nEigens,
                           eigenVectArr,
                           0, 0,
                           pAvgTrainImg,
                           projectedTestFace
                           );

        iNearest = findNearestNeighbor(projectedTestFace);
        truth = personNumTruthMat->data.i[i];
        nearest = trainPersonNumMat->data.i[iNearest];

        printf("nearest = %d, Truth = %d\n", nearest, truth);
    }
}

int loadTrainingData(CvMat** pTrainPersonNumMat){
    CvFileStorage* fileStorage;
    int i;

    // create a file-storage interface
    fileStorage = cvOpenFileStorage( "facedata.xml", 0, CV_STORAGE_READ );
    if( !fileStorage ){
        fprintf(stderr, "Can't open facedata.xml\n");
        return 0;
    }

    nEigens = cvReadIntByName(fileStorage, 0, "nEigens", 0);
    nTrainFaces = cvReadIntByName(fileStorage, 0, "nTrainFaces", 0);
    *pTrainPersonNumMat = (CvMat*)cvReadByName(fileStorage, 0, "trainPersonNumMat", 0);
    eigenValMat = (CvMat*)cvReadByName(fileStorage, 0, "eigenValMat", 0);
    projectedTrainFaceMat = (CvMat*)cvReadByName(fileStorage, 0, "projectedTrainFaceMat", 0);
    pAvgTrainImg = (IplImage*)cvReadByName(fileStorage, 0, "avgTrainImg", 0);
    eigenVectArr = (IplImage**)cvAlloc(nTrainFaces*sizeof(IplImage*));
    for(i=0; i<nEigens; i++){
        char varname[200];
        sprintf( varname, "eigenVect_%d", i );
        eigenVectArr[i] = (IplImage*)cvReadByName(fileStorage, 0, varname, 0);
    }

    // release the file-storage interface
    cvReleaseFileStorage( &fileStorage );

    return 1;
}

int findNearestNeighbor(float* projectedTestFace){
    double leastDistSq = DBL_MAX;
    int i, iTrain, iNearest = 0;

    for(iTrain=0; iTrain<nTrainFaces; iTrain++){
        double distSq = 0;

        for(i=0; i<nEigens; i++){
            float d_i = projectedTestFace[i] -
                projectedTrainFaceMat->data.fl[iTrain*nEigens + i];
            distSq += d_i*d_i;
        }

        if(distSq < leastDistSq){
            leastDistSq = distSq;
            iNearest = iTrain;
        }
    }

    return iNearest;
}
