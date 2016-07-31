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
    double alpha = 1;
    double beta = 1;
    double weight_scale = 0.1;
    double back_moment = 0.1;
    Mat layerSizes=(Mat_<int>(1,5) << 5,2,2,2,5);
    Ptr<ANN_MLP> bp = ANN_MLP::create();
    bp->empty();
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

    return EXIT_SUCCESS;
}
