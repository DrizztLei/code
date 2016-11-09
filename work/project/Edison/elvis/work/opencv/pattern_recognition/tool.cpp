#ifndef TOOL_CPP
#define TOOL_CPP

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/face.hpp>
#include <opencv/cv.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;
using namespace cv;
using namespace cv::face;

/** Function Headers */
void cv_detectAndDisplay (Mat frame );
void cv_print_data(Rect * face);
bool cv_save_picture(Mat frame , Rect face , string picture_name);
string cv_int_to_string(int num);
void cv_resize(Mat & frame , int x , int y , Mat & out);
void cv_display(Mat frame);
int cv_demo_main(int argc , char ** argv);
string cv_get_format_time();
void cv_read_csv(const string & filename , vector<Mat> & images , vector<int> & labels , char separator = ';');

/** Global variables */
String face_cascade_name = "haarcascade_frontalcatface.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "OPENCV";
stringstream stream;

/**Function Body */
void cv_read_csv(const string & filename , vector<Mat> & images , vector<int> & labels , char separator)
{
    std::ifstream file(filename.c_str(), ifstream::in);
    if(!file)
    {
        string error_message = "No valid input file was given.";
        CV_Error(CV_StsBadArg, error_message);
    }

    string line, path, classlabel;
    while(getline(file, line))
    {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty())
        {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }

}

string cv_get_format_time()
{
    time_t timel;
    time(&timel);
    string time =  (asctime(gmtime(&timel)));
    return time;
}

void cv_display(Mat frame)
{
    String display = "CV_DISPLAY";
    //-- Show what you got
    imshow(display , frame);
}

void cv_resize(Mat & frame , int x , int y , Mat & out)
{
    resize(frame , out ,Size(x , y) , 0 , 0 , CV_INTER_LINEAR);
}

void cv_integrate_automic_detect()
{
    int argc = 1;
    char test [9] = "tool.cpp";
    char ** argv = (char**) (&test);
}

string cv_int_to_string(int data)
{
    stream << data;
    string result = stream.str();
    stream.clear();
    stream.str("");
    return result;
}

bool cv_save_picture(Mat target , Rect rect , string name )
{
    if(imwrite(name , target(rect)))
    {
        cout << "Save picture for : " << name << " successed ." << endl;
        return true;
    }
    else
    {
        cout << "Save picture for : " << name << " failed." << endl;
        return false;
    }
}

void cv_print_data(Rect * obj)
{
    cout << obj->x << " for x." << endl;
    cout << obj->y << " for y." << endl;
    cout << obj->width << " for width." << endl;
    cout << obj->height << " for height." << endl;
}

int cv_demo_main(int argc , char ** argv)
{
    VideoCapture capture;
    Mat frame;
    if(argc > 1)
    {
        for(int i = 1 ; i < argc ; i++)
        {
            printf("Get the image info for : %s\n" , argv[i]);
        }
    }
    else
    {
        printf ("No image found. Using the uvc camera.\n");
    }
    //-- 1. Load the cascade
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade.\n"); return -1; };
    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade.\n"); return -1; };

    //-- 2. Read the video stream
    // 0 for camera in computer
    // 1 for camera in extra
    capture.open(0);
    if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }
    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!\n");
            break;
        }
        //-- 3. Apply the classifier to the frame
        //detectAndDisplay( frame );
        cv_display(frame);
        //-- bail out if escape was pressed
        int c = waitKey(10);
        if( (char)c == 27 ) { return 0; }
    }
    printf("Error for not show the image.\n");
    return -1;
}

void detectAndDisplay( Mat frame )
{
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0, Size(80, 80) );

    for( size_t i = 0; i < faces.size(); i++ )
    {
        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;
        //-- In each face, detect eyes

        //eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
        eyes_cascade.detectMultiScale(frame_gray(faces[i]), eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30));
        if( eyes.size() == 2)
        {
            cout << "catch the face for id : " << i + 1 << " in size : " << faces.size() << endl;
            cv_print_data(&faces[i]);
            //string name = "picture-" + int_to_string(i) + ".png";
            string name = "picture-" + cv_get_format_time() + ".png";
            cv_save_picture(frame , faces[i] , name);
            //-- Draw the face
            Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
            ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );
            for( size_t j = 0; j < eyes.size(); j++ )
            {
                //-- Draw the eyes
                Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
                int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
                circle( frame, eye_center, radius, Scalar( 255, 0, 255 ), 3, 8, 0 );
            }
        }
    }
    //-- Show what you got
    imshow( window_name, frame );
    //imshow( window_name + " For Gray", frame_gray);
}
#endif
