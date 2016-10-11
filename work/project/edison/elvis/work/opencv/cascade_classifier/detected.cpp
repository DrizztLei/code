#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include "./time.cpp"
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

/** Function Headers */
bool detectAndDisplay( Mat frame , bool flag);
void print_data(Rect *);
bool save_picture(Mat , Rect , string);
string int_to_string(int);

/** Global variables */
String face_cascade_name = "/home/elvis/work/opencv/cascade_classifier/haarcascade_frontalcatface.xml";
String eyes_cascade_name = "/home/elvis/work/opencv/cascade_classifier/haarcascade_eye_tree_eyeglasses.xml";
String ip_camera = "rtsp://admin:123456@192.168.1.10:554/h264/ch1/main/av_stream";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Face Detection";

string int_to_string(int n)
{
    int const max = 100;
    int m = n;
    int i=0,j=0;
    char s[max];
    char ss[max];
    while(m > 0)
    {
        s[i++]=  m % 10 + '0';
        m /= 10;
    }
    s[i] = '\0';

    i = i-1;
    while(i >= 0)
    {
        ss[j++] = s[i--];
    }
    ss[j] = '\0';
    return ss;
}

bool save_picture(Mat target , Rect rect , string name )
{
    //Mat store;
    //frame(rect).copyTo(store);
    if(imwrite(name , target(rect))){
        cout << "Save picture for : " << name << " successed ." << endl;
        return true;
    }else{
        cout << "Save picture for : " << name << " failed." << endl;
        return false;
    }
}
void print_data(Rect * obj)
{
    cout << obj->x << " for x." << endl;
    cout << obj->y << " for y." << endl;
    cout << obj->width << " for width." << endl;
    cout << obj->height << " for height." << endl;
}
/**
 * @function main
 */
int main(int argc , char ** argv)
{
    VideoCapture capture(ip_camera);
    Mat frame;
    int id = 1;
    //-- 1. Load the cascade
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade.\n"); return -1; };
    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade.\n"); return -1; };

    //-- 2. Read the video stream
    // 0 for camera in computer
    // 1 for camera in extra

    //capture.open(id);

    if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }
    cout << "Open the video successed" << endl;
    int count = 0;

    while ( true )
    {
        if(capture.read(frame))
        {
            cout << "get the frame from capture to frame error " << endl; 
        }
        if( frame.empty())
        {
            printf(" --(!) No captured frame -- Break!\n");
            break;
        }

        //-- 3. Apply the classifier to the frame
        count = count % 10;
        count ++;
        if(count != 10)
        {
            if(detectAndDisplay(frame , true))
            {
                return 0;
            }
        }
        else
        {
            if(detectAndDisplay(frame , false))
            {
                return 0;
            }
        }
        //-- bail out if escape was pressed
        int c = waitKey(10);
        if( (char)c == 27 ) { return 0; }
    }
    printf("Error for not show the image.\n");
    return -1;
}

bool detectAndDisplay( Mat frame , bool flag )
{
    if(flag)
    {
        //imshow( window_name, frame );
        return false;
    }
    else
    {
        bool flag = false;
        std::vector<Rect> faces;
        Mat frame_gray;
        cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
        equalizeHist( frame_gray, frame_gray );
        //-- Detect faces
        face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0, Size(80, 80));
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
                print_data(&faces[i]);
                string name = "picture-" + get_format_time() + ".png";
                save_picture(frame , faces[i] , name);
                flag = true;
                //-- Draw the face
                Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
                ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );
                for( size_t j = 0; j < eyes.size(); j++ )
                { //-- Draw the eyes
                    Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
                    int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
                    circle( frame, eye_center, radius, Scalar( 255, 0, 255 ), 3, 8, 0 );
                }
            }
        }
        //-- Show what you got
        //imshow( window_name, frame );
        return flag;
        //imshow( window_name + " For Gray", frame_gray);
    }
}
