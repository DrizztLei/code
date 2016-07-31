#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

using namespace cv;
using namespace std;


void cv_show_rect( cv::Mat& src_gray , const string & threshold , const string & source , int * thresh , int max_thresh , RNG & rng );
void thresh_callback(cv::Mat&, int, int ,cv::RNG &);

void cv_show_image(Mat frame , string const & name);

int main(int, char** argv )
{
    Mat src;
    Mat src_gray;
    int thresh = 150;
    int max_thresh = 255;
    src = imread( argv[1], 1 );

    RNG rng(12345);
    const char* source_window = "Source";

    cvtColor( src, src_gray, COLOR_BGR2GRAY );
    blur( src_gray, src_gray, Size(3,3) );

    namedWindow( source_window, WINDOW_AUTOSIZE );
    imshow( source_window, src );

    cv_show_rect(src_gray , "source" , "thresh" , &thresh , max_thresh , rng);

    waitKey(0);
    return (0);
}

void cv_show_rect(Mat & src_gray , const string & threshold , const string & source , int * thresh , int max_thresh , cv::RNG & rng)
{
    createTrackbar(threshold, source , thresh, max_thresh);
    thresh_callback(src_gray, *thresh , max_thresh , rng);
}


void thresh_callback(cv::Mat & src_gray , int thresh , int max_thresh , cv::RNG & rng)
{

    Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    threshold(src_gray, threshold_output, thresh, max_thresh , THRESH_BINARY );
    findContours( threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

    vector<vector<Point> > contours_poly( contours.size() );
    vector<Rect> boundRect( contours.size() );

    for( size_t i = 0; i < contours.size(); i++ )
    {
        approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
        boundRect[i] = boundingRect( Mat(contours_poly[i]) );
    }

    Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
    int count = 0;

    for( size_t i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
    }
    cout << "Get the num : " << count << endl;
    namedWindow( "Contours", WINDOW_AUTOSIZE );
    imshow( "Contours", drawing );
}

void cv_show_image(Mat picture , string const & window)
{
    namedWindow(window , WINDOW_AUTOSIZE);
    while(true)
    {
        imshow(window, picture);
        if(waitKey(0))
        {
            break;
        }
    }
}
