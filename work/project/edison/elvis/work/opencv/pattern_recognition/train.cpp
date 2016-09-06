#ifndef CV_TRAIN_CPP
#define CV_TRAIN_CPP

#include "tool.cpp"

const string image_path = "/home/elvis/work/opencv/pattern_recognition/orl_faces/";

int num_components = 4000;
double value = 10;

// Then if you want to have a cv::FaceRecognizer with a confidence threshold,
// create the concrete implementation with the appropiate parameters:

//createEigenFaceRecognizer
//createFisherFaceRecognizer
//createLBPHFaceRecognizer

//Ptr<FaceRecognizer> model = createEigenFaceRecognizer(num_components, value);
Ptr<FaceRecognizer> model = createEigenFaceRecognizer();

void predict(const Ptr<FaceRecognizer> & model , const vector<Mat>  & images , const vector<int>  & labels);

void predict(Ptr<FaceRecognizer> & model , vector<Mat>& images , vector<int>& labels)
{
    int count = 0;
    int size = images.size();
    for(int i = 0 ; i < size ; i++)
    {
        double value = model->predict(images[i]);
        cout << "predict for : " << value << endl;
        cout << "value for : " << labels[i] << endl;
        if(value != labels[i])
        {
            count ++;
        }
    }
    cout << "Get the error rate for : " << (double) count / size << endl;
}

void cv_train_demo();
void cv_train_demo()
{
    vector<Mat> images;
    vector<Mat> check;
    vector<int> labels;
    vector<int> verify;
    int size = 40 , sub_size = 10;
    double rate = 0.9;
    string name = "";
    for(int i = 1 ; i <= size ; i++)
    {
        for(int j = 1 ; j <= sub_size ; j++)
        {
            name = image_path + 's' + cv_int_to_string(i) +"/"
                + cv_int_to_string(j) + ".pgm";
            if(j < sub_size * rate)
            {
                cout << "Add to train" << endl;
                images.push_back(imread(name , CV_LOAD_IMAGE_GRAYSCALE));
                labels.push_back(i);
            }
            else
            {
                cout << "Add to predict" << endl;
                check.push_back(imread(name , CV_LOAD_IMAGE_GRAYSCALE));
                verify.push_back(i);
            }
        }
    }

    cout << "Get the train size for : " << images.size() << endl;
    cout << "Get the check size for : " << check.size() << endl;

    cout << "TRAINING . " << endl;
    model->train(images , labels);
    cout << "DONE . " << endl;

    predict(model , check , verify);
}

int main(int argc , char ** argv)
{
    /*
    Mat picture = imread(argv[1] , 0);
    while(true)
    {
        cv_display(picture);
        char c = waitKey(0);
        if(c == 27)
        {
            break;
        }
        }
    */
    cv_train_demo();
    return EXIT_SUCCESS;
}
#endif
