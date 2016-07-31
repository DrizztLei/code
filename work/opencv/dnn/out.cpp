#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <memory>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
using namespace cv::dnn;
using namespace cv::ml;
using namespace cv;
using namespace std;

/**
  function head
*/
void cv_print_parameter(int argc , char ** argv);
int main(int argc , char ** argv);
void data_read(string filename);

/**
   function body
*/
int main(int argc, char ** argv)
{
    cv_print_parameter(argc , argv);
    Ptr<ANN_MLP> mlp = ANN_MLP::create();
    ANN_MLP::TrainFlags weight_flag = ANN_MLP::UPDATE_WEIGHTS;
    ANN_MLP::ActivationFunctions fx = ANN_MLP::SIGMOID_SYM;
    ANN_MLP::TrainingMethods method = ANN_MLP::BACKPROP;
    mlp->empty();
    mlp->setTrainMethod(method, 0, 0);
    mlp->setActivationFunction(fx, 0, 0);
    mlp->setTrainMethod(weight_flag, 0, 0);
    mlp->setLayerSizes(5);
    mlp->setBackpropMomentumScale(0.1);
    float trainingData[3][5] = { {1,2,3,4,5},{111,112,113,114,115}, {21,22,23,24,25} };
    Mat trainingDataMat(3, 5, CV_32FC1, trainingData);
    Mat layerSizes=(Mat_<int>(1,5) << 5,2,2,2,5);
    const string filename = "./read.csv";
    mlp->save("out");
    return EXIT_SUCCESS;
}

void cv_print_parameter(int argc , char ** argv)
{
    for(int i = 0 ; i < argc ; i++)
    {
        cout << "argv[" << i << "] : " << argv[i] << endl;
    }
}

void data_read(string filename)
{
    cout << "Get file : " << filename << endl;
    std :: ifstream in;
    in.open(filename.c_str());
    long count = 0;
    double var;
    double temp = 1 ;
    while(!in.eof())
    {
        in >> var;
        temp = var;
        count ++;
    }
}
