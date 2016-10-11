#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

#include "tool.cpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;
using namespace cv::ml;

int main()
{

    const string image_path = "./orl_faces/";

    vector<Mat> images;
    vector<Mat> check;
    vector<int> labels;
    vector<int> verify;
    int size = 40 , sub_size = 10;
    double rate = 0.8;
    string name = "";
    for(int i = 1 ; i <= size ; i++)
    {
        for(int j = 1 ; j <= sub_size ; j++)
        {
            name = image_path + 's' + cv_int_to_string(i) +"/"
                + cv_int_to_string(j) + ".pgm";
            if(j < sub_size * rate)
            {
                images.push_back(imread(name , CV_LOAD_IMAGE_GRAYSCALE));
                labels.push_back(i);
            }
            else
            {
                check.push_back(imread(name , CV_LOAD_IMAGE_GRAYSCALE));
                verify.push_back(i);
            }
        }
    }

    //Setup the BPNetwork
    double alpha = 1;
    double beta = 1;
    double weight_scale = 0.1;
    double back_moment = 0.1;
    Mat layerSizes=(Mat_<int>(1,5) << 5,2,2,2,5);
    Ptr<ANN_MLP> bp = ANN_MLP::create();
    bp->empty();
    // Set up BPNetwork's parameters
    bp->setActivationFunction(ANN_MLP::SIGMOID_SYM , alpha , beta);
    bp->setBackpropMomentumScale(0.1);
    bp->setBackpropWeightScale(0.1);
    bp->setTrainMethod(ANN_MLP::BACKPROP , weight_scale , back_moment);
    bp->setLayerSizes(layerSizes);

    float aim[3][5] = {{0,0,0,0,0},{1,1,1,1,1},{0,0,0,0,0}};
    Mat labelsMat(3, 5, CV_32FC1, aim);

    float trainingData[3][5] = { {1,2,3,4,5},{111,112,113,114,115}, {21,22,23,24,25} };
    Mat trainingDataMat(3, 5, CV_32FC1, trainingData);
    cout << "Training." << endl;
    bp->train(trainingDataMat , 0 , labelsMat);
    cout << "Done." << endl;

    bp->save("CV-MODEL");
    // Train the BPNetwork
    //params.train_method=CvANN_MLP_TrainParams::RPROP;
    //params.rp_dw0 = 0.1;
    //params.rp_dw_plus = 1.2;
    //params.rp_dw_minus = 0.5;
    //params.rp_dw_min = FLT_EPSILON;
    //params.rp_dw_max = 50.;
    // Set up training data
    /*
      float lable[3][5] = {{0,0,0,0,0},{1,1,1,1,1},{0,0,0,0,0}};
      Mat labelsMat(3, 5, CV_32FC1, labels);

      float trainingData[3][5] = { {1,2,3,4,5},{111,112,113,114,115}, {21,22,23,24,25} };
      Mat trainingDataMat(3, 5, CV_32FC1, trainingData);
      Mat layerSizes=(Mat_<int>(1,5) << 5,2,2,2,5);

      //cout << bp->getWeights(1) << endl;

      bp.create(layerSizes,CvANN_MLP::SIGMOID_SYM);//CvANN_MLP::SIGMOID_SYM
      //CvANN_MLP::GAUSSIAN
      //CvANN_MLP::IDENTITY

      bp->setLayerSizes(layerSizes);

      cout << "Get the LayerSizes : " << endl << bp->getLayerSizes() << endl;
      cout << "Get the layer for [" << 2 << "]" << bp->getWeights(0) << endl;

      bp->train(trainingDataMat , 0 , labelsMat);
      bp->save("model.cv");
    */

    //bp->train(const Ptr<cv::ml::TrainData> &trainData, int flags)
    //bp->train(trainingDataMat, labelsMat, Mat(),Mat(), params);
    // Data for visual representation
    /*
      int width = 512, height = 512;
      Mat image = Mat::zeros(height, width, CV_8UC3);
      Vec3b green(0,255,0), blue (255,0,0);
      // Show the decision regions given by the SVM
      for (int i = 0; i < image.rows; ++i)
      for (int j = 0; j < image.cols; ++j)
      {
      Mat sampleMat = (Mat_<float>(1,5) << i,j,0,0,0);
      Mat responseMat;
      bp.predict(sampleMat,responseMat);
      float* p=responseMat.ptr<float>(0);
      float response=0.0f;
      for(int k=0;k<5;i++){
      //  cout<<p[k]<<" ";
      response+=p[k];
      }
      if (response >2)
      image.at<Vec3b>(j, i)  = green;
      else
      image.at<Vec3b>(j, i)  = blue;
      }

      // Show the training data
      int thickness = -1;
      int lineType = 8;
      circle( image, Point(501,  10), 5, Scalar(  0,   0,   0), thickness, lineType);
      circle( image, Point(255,  10), 5, Scalar(255, 255, 255), thickness, lineType);
      circle( image, Point(501, 255), 5, Scalar(255, 255, 255), thickness, lineType);
      circle( image, Point( 10, 501), 5, Scalar(255, 255, 255), thickness, lineType);

      imwrite("result.png", image);        // save the image

      imshow("BP Simple Example", image); // show it to the user
      waitKey(0);
    */
    return EXIT_SUCCESS;
}
