#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;
using namespace cv;

/** Function Headers */
bool detectAndDisplay( Mat frame );
int online_detect(char ** , int);

/** Global variables */

String face_cascade_name = "/home/elvis/work/opencv/cascade_classifier/haarcascade_frontalface_alt2.xml";
String eyes_cascade_name = "/home/elvis/work/opencv/cascade_classifier/haarcascade_eye.xml";

CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

String window_name = "Capture - Face detection";

/** @function main */
int main(int argc , char ** argv)
{
    return online_detect(argv , argc);
}

int online_detect(char ** argv , int argc)
{

    // VideoCapture capture("rtsp://admin:123456@192.168.1.10:554:h264/ch1/main/av_stream");
    VideoCapture capture(0);
    Mat frame;

    //-- 1. Load the cascades

    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };
    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade\n"); return -1; };

    //-- 2. Read the video stream

    if(argc > 1)
    {
        Mat temp = imread(argv[1]);

        resize( temp , frame , Size(128 , 128) , 0 , 0 ,CV_INTER_LINEAR);

        while(true)
        {
            detectAndDisplay(frame);
            int c = waitKey(10);
            if(((char)c == 27))
            {
                break;
            }
        }
    }
    else
    {
        // capture.open(0);
        if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }
        cout << "open the camera done ." << endl;
        while ( capture.read(frame) )
        {
            if( frame.empty() )
            {
                printf(" --(!) No captured frame -- Break!");
                break;
            }
            //-- 3. Apply the classifier to the frame
            bool flag = detectAndDisplay( frame );
            if(flag) return 0;
            int c = waitKey(10);
            if( (char)c == 27 ) { break; } // escape
        }
    }
    return 0;
}

/** @function detectAndDisplay */
bool detectAndDisplay( Mat frame )
{
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30));

    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );

        // ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;

        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );

        if(eyes.size() == 2)
        {
            /*

              for ( size_t j = 0; j < eyes.size(); j++ )
              {
              Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
              int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
              circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
              }
            */


            rectangle(frame, Point(faces[i].x , faces[i].y), Point(faces[i].x + faces[i].width , faces[i].y + faces[i].height) , Scalar(0,255,0), 4, 8, 0);

            // imwrite(const cv::String &filename, InputArray img, const std::vector<int> &params)
            int x = faces[i].x - 10 >= 0 ? faces[i].x - 10 : 0;
            int y = faces[i].y - 10 >= 0 ? faces[i].y - 10 : 0;
            int width = faces[i].width + 10 ;
            int height = faces[i].height + 10;
            // imwrite("out.png" , frame(Rect (faces[i].x , faces[i].y , faces[i].width , faces[i].height)));
            imwrite("/home/elvis/work/opencv/cascade_classifier/out.png" , frame(Rect (x , y , width , height)));
            cout << "true" << endl;
            return true;
        }
    }
    //-- Show what you got
    imshow( window_name, frame );
    return false;
}
