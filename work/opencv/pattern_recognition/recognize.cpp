#ifndef CV_TRAIN_CPP
#define CV_TRAIN_CPP

#include "tool.cpp"

const string image_path = "/home/elvis/work/opencv/pattern_recognition/orl_faces/";
const string model_file = "/home/elvis/work/opencv/pattern_recognition/LBPHF.cv.model";

int num_components = 4000;
int const rows = 92;
int const cols = 112;
double value = 10;

// Then if you want to have a cv::FaceRecognizer with a confidence threshold,
// create the concrete implementation with the appropiate parameters:

//createEigenFaceRecognizer
//createFisherFaceRecognizer
//createLBPHFaceRecognizer

//Ptr<FaceRecognizer> model = createEigenFaceRecognizer(num_components, value);
//Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
//Ptr<FaceRecognizer> model = createFisherFaceRecognizer();

Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();

void predict(const Ptr<FaceRecognizer> & model , const vector<Mat>  & images , const vector<int>  & labels);

void predict(Ptr<FaceRecognizer> & model , vector<Mat>& images , vector<int>& labels)
{
    int count = 0;
    int size = images.size();
    for(int i = 0 ; i < size ; i++)
    {
        int value = model->predict(images[i]);
        double confidence = 0;
        model->predict(images[i] , value , confidence);

        cout << "predict for : " << value << endl;
        cout << "value for : " << labels[i] << endl;
        cout << "confidence for : " << confidence << endl;

        if(value != labels[i])
        {
            count ++;
        }
    }
    cout << "Get the error rate for : " << (double) count / size << endl;
}

int main(int argc , char ** argv)
{
    /*
    vector<Mat> images;
    vector<Mat> check;
    vector<int> labels;
    vector<int> verify;
    int size = 40 , sub_size = 10;
    double rate = 0.7;
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

    cout << "TRAINING . " << endl;
    model->train(images , labels);
    cout << "DONE . " << endl;

    predict(model , check , verify);
    */

    /*
    model->save(model_file);
    */
    /*
    if(argc != 3)
    {
        cerr << "Error for argc not availiable ." << endl;
        return EXIT_FAILURE;
    }
    Mat target = imread(argv[2]);
    while(true)
    {
        cv_display(target);
        if(waitKey() == 'a')
        {
            break;
        }
        }
    */

    if(argc != 3)
    {
        cerr << "Error for argc != 3" << endl;
    }

    Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();

    model->load(argv[1]);

    Mat unsure = imread( argv[2] , CV_LOAD_IMAGE_GRAYSCALE);

    cv_resize(unsure, cols , rows , unsure);

    //cout << "resize over" << endl;
    //cout << "Get the predict for : " << model->predict(unsure) << endl;

    int target = model->predict(unsure);
    double confidence = 0;
    model->predict(unsure, target , confidence);
    if(confidence >= 60 && confidence <= 99)
    {
        cout << target << endl;
    }
    else
    {
        cout << -1 << endl;
    }
    //cout << "Get the confidence : " << confidence << endl;
    return EXIT_SUCCESS;
}
#endif
