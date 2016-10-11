#include <opencv2/ml.hpp>
#include <opencv2/dnn.hpp>
#include <stdio.h>
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>

enum temp
{
    red,
    black,
    whitel
};

int main(int argc , char ** argv)
{

    using namespace std;
    using namespace cv;
    using namespace cv::ml;

    ANN_MLP::ActivationFunctions sigmod  = ANN_MLP::SIGMOID_SYM;
    ANN_MLP::TrainFlags train_flag = ANN_MLP::UPDATE_WEIGHTS;
    ANN_MLP::TrainingMethods train_method = ANN_MLP::BACKPROP;


    //StaModel::train(const Ptr<cv::ml::TrainData> &trainData, int flags)

    Ptr<ANN_MLP> model = ANN_MLP::create();

    //model->train(InputArray samples, int layout, InputArray responses);

    cout << "Get the size of : " << model->getLayerSizes() << endl;
    cout << "Get the method of : " << model->getTrainMethod() << endl;


    return 0;
}
