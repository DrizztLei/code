#include "tool.cpp"

#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <opencv2/face.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace cv;
using namespace cv::face;
using namespace cv::ml;


#ifndef TARGET_CPP
#define TARGET_CPP

CvMemStorage* storage = 0;
CvHaarClassifierCascade* cascade = 0;
CvHaarClassifierCascade* nested_cascade = 0;
int use_nested_cascade = 0;
const char* cascade_name = "./haarcascade_frontalface_alt.xml";//别人已经训练好的人脸检测xml数据
const char* nested_cascade_name ="./haarcascade_eye_tree_eyeglasses.xml";
const string image_path = "./orl_faces/";
CvCapture* capture = 0;
IplImage *frame, *frame_copy = 0;
IplImage *image = 0;
const char* scale_opt = "--scale="; // 分类器选项指示符号
int scale_opt_len = (int)strlen(scale_opt);
const char* cascade_opt = "--cascade=";
int cascade_opt_len = (int)strlen(cascade_opt);
const char* nested_cascade_opt = "--nested-cascade";
int nested_cascade_opt_len = (int)strlen(nested_cascade_opt);
double scale = 1;
int num_components = 9;
double facethreshold = 9.0;

//opencv的FaceRecogizer目前有三个类实现了他，特征脸和fisherface方法最少训练图像为两张，而LBP可以单张图像训练
//cv::Ptr<cv::FaceRecognizer> model = cv::createEigenFaceRecognizer();
//cv::Ptr<cv::FaceRecognizer> model = cv::createFisherFaceRecognizer();
//Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
Ptr<BasicFaceRecognizer> model = createLBPHFaceRecognizer();
//LBP的这个方法在单个人脸验证方面效果最好

vector<Mat> images;//两个容器images,labels来存放图像数据和对应的标签
vector<int> labels;

int main( int argc, char** argv)
{

    cascade = (CvHaarClassifierCascade*)cvLoad(cascade_name, 0, 0, 0); //加载分类器
    if(!cascade)
    {
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
        getchar();
        return EXIT_FAILURE;
    }

    //model->set("threshold", 2100.0);
    string output_folder;
    output_folder = string("./einfacedata");

    //读取你的CSV文件路径
    string fn_csv = string("./read.csv");
    try
    {
        //通过./einfacedata/at.txt这个文件读取里面的训练图像和类别标签
        /*
          int size = 40 , sub_size = 10;
          string name = "";
          for(int i = 0 ; i < size ; i++)
          {
          for(int j = 0 ; j < sub_size ; j++)
          {
          name = image_path + 's' + cv_int_to_string(i) +"/"
          + cv_int_to_string(j) + ".pgm";
          //cout << "Get the image name for : " << name << endl;
          //cout << "Get the labels for : " << i << endl;
          images.push_back(imread(name , CV_LOAD_IMAGE_GRAYSCALE));
          labels.push_back(i);
          }
          }
        */
        cv_read_csv(fn_csv , images , labels);
    }

    catch(cv::Exception &e)
    {
        cerr<<"Error opening file "<<fn_csv<<". Reason: "<<e.msg<<endl;
        return EXIT_FAILURE;
    }

    /*
    //read_img这个函数直接从einfacedata/trainingdata目录下读取图像数据并默认将图像置为0
    //所以如果用这个函数只能用来单个人脸验证
    if(!read_img(images, labels))
    {
    cout<< "Error in reading images!";
    images.clear();
    labels.clear();
    return 0;
    }
    */

    cout << images.size() << ":" << labels.size()<<endl;
    //如果没有读到足够的图片，就退出
    if(images.size() <= 2)
    {
        string error_message = "This demo needs at least 2 images to work.";
        CV_Error(CV_StsError, error_message);
        return EXIT_FAILURE;
    }

    //得到第一张照片的高度，在下面对图像变形到他们原始大小时需要
    //int height = images[0].rows;
    //移除最后一张图片，用于做测试
    //Mat testSample = images[images.size() - 1];
    //cv::imshow("testSample", testSample);
    //int testLabel = labels[labels.size() - 1];
    //images.pop_back();
    //labels.pop_back();

    //下面创建一个特征脸模型用于人脸识别，
    // 通过CSV文件读取的图像和标签训练它。

    //进行训练

    cout << " TRAINING " << endl;
    model->train(images, labels);
    cout << " TRAIN DONE " << endl;

    storage = cvCreateMemStorage(0); // 创建内存存储器
    capture = cvCaptureFromCAM(0); // 创建视频读取结构

    string const ExperimentName = "OPENCV_FACE";

    //cvNamedWindow( ExperimentName , 1 );

    int count = 0;

    if( capture ) // 如过是视频或摄像头采集图像，则循环处理每一帧
    {
        while(true)
        {
            if( (count=((count++)%10)) == 0){
                continue ;
            }
            if( !cvGrabFrame( capture ))
            {
                break;
            }
            frame = cvRetrieveFrame( capture );
            if( !frame )
                break;
            if( !frame_copy )
            {
                frame_copy = cvCreateImage( cvSize(640,480),IPL_DEPTH_8U, frame->nChannels );
            }
            if( frame->origin == IPL_ORIGIN_TL )
            {
                cvCopy( frame, frame_copy, 0 );
            }
            else
            {
                cvFlip( frame, frame_copy, 0 );
            }
            //detect_and_draw( frame_copy ); // 如果调用这个函数，只是实现人脸检测
            //cout << frame_copy->width << "x" << frame_copy->height << endl;
            //recog_and_draw( frame_copy );//该函数实现人脸检测和识别
            if( cvWaitKey( 100 ) >= 0 )//esc键值好像是100
            {
                goto _cleanup_;
            }
        }
        cvWaitKey(0);
    _cleanup_: // 标记使用，在汇编里用过，C语言，我还没见用过
        cvReleaseImage( &frame_copy );
        cvReleaseCapture( &capture );
    }
    //cvDestroyWindow(ExperimentName);
    return 0;
}
#endif
