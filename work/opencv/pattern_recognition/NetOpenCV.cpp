#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include "tool.cpp"

using namespace std;
int main(int argc , char ** argv)
{
	int camera_id = -1;
	if(argc > 1) camera_id = atoi(argv[1]);
    //cv::VideoCapture cap(camera_id);
    cv::VideoCapture cap("http://www.bilibilijj.com/Files/DownLoad/9452537.mp4/www.bilibilijj.com.mp4?mp3=true");
	if(!cap.isOpened())
	{
		printf("failed to open the camera with id %d.\n" , camera_id);
		return -1;
	}
	cv::Mat frame;
    while(true)
    {
        cap >> frame;
        cv_display(frame);
        if(waitKey(10) == 27)
        {
            break;
        }
    }
	return 0;
}
