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

#include "tool.cpp"

using namespace cv::dnn;
using namespace cv::ml;
using namespace cv;
using namespace std;


/*
  function head
*/
int const control = 775;
int const aim = 4;
int const input = 256;
float set[control][input];
float label[control][aim];

void cv_print_parameter(int argc , char ** argv);
void cv_read(string filename);
int main(int argc , char ** argv);

/*
  main function
*/
int main(int argc, char ** argv)
{
    cv_print_parameter(argc , argv);
    cv_read("sample.data");
    //Setup the BPNetwork

    Ptr<ANN_MLP> mlp = ANN_MLP::create();
    mlp->empty();

    ANN_MLP::TrainFlags weight_flag = ANN_MLP::UPDATE_WEIGHTS;
    ANN_MLP::ActivationFunctions fx = ANN_MLP::SIGMOID_SYM;
    ANN_MLP::TrainingMethods method = ANN_MLP::BACKPROP;
    Mat layerSizes=(Mat_<int>(1,5) << input,128,64,32,aim);

    mlp->setLayerSizes(layerSizes);
    mlp->setTrainMethod(method, 0, 0);
    mlp->setActivationFunction(fx, 0, 0);
    mlp->setTrainMethod(weight_flag, 0, 0);
    mlp->setBackpropMomentumScale(0.1); // 0.1 is enough

    //float trainingData[3][5] = { {1,2,3,4,5},{111,112,113,114,115}, {21,22,23,24,25} };
    Mat trainingDataMat(control, input, CV_32FC1, set);

    while(true)
    {
        imshow("out" , trainingDataMat);
        if(waitKey(0) == '27')
        {
            break;
        }
    }

    Mat respoonse(control, aim , CV_32FC1, label);

    mlp->train(trainingDataMat, ANN_MLP::BACKPROP , respoonse);

    //Mat sampleMat = (Mat_<float>(1,5) << input,,0,0,0);
    Mat responseMat;
    //cout << mlp->predict(sampleMat, respoonse ) << endl;

    //mlp->save("result.cv");
    //cout << mlp->predict(preData) << endl;

    return EXIT_SUCCESS;

}

/*
  function body
*/

void cv_print_parameter(int argc , char ** argv)
{
    for(int i = 0 ; i < argc ; i++)
    {
        cout << "argv[" << i << "] : " << argv[i] << endl;
    }
}

void cv_read(string filename)
{
    std :: ifstream in;
    in.open(filename.c_str());
    if(!in.is_open())
    {
        cout << "Error for file busy or not found . " << endl;
        throw "Resources busy . ";
        exit(EXIT_FAILURE);
    }
    int control = 0;
    string temp , part , data;
    int count = 0 , out;
    while(!in.eof())
    {
        in >> temp ;
        if(count % 257 == 0)
        {
            if(temp.length() == 1)
            {
                control ++;
                out = cv_string_to_double(temp);
                for(int i = 0 ; i < aim ; i++)
                {
                    if(i == out)
                    {
                        label[control][i] = 1;
                    }
                    else
                    {
                        label[control][i] = 0;
                    }
                }
            }
        }
        else
        {
            //cout << "temp : " << temp << endl;
            int position = temp.find_first_of(':');
            part = temp.substr(0 , position);
            data = temp.substr(position+1);
            //cout << "control - 1 : " << control - 1 << endl;
            //cout << "count - 1 : " << count % (input + 1) - 1 << endl;
            set[control-1][(count %(input + 1))-1] = cv_string_to_double(data);
        }
        count ++;
    }
    in.close();
    cout << "count : " << control << endl;
}
