#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <cstring>
#include <iostream>

using namespace std;
int main(int argc , char ** argv)
{
	int camera_id = -1;
	if(argc > 1) camera_id = atoi(argv[1]);
    //cv::VideoCapture cap(camera_id);
    //cv::VideoCapture cap("http://www.bilibilijj.com/Files/DownLoad/9452537.mp4/www.bilibilijj.com.mp4?mp3=true");
    //cv::VideoCapture cap("rtsp://admin:123456@192.168.1.10:554:h264/ch1/main/av_stream");
    cv::VideoCapture cap("rtsp://admin:123456@192.168.1.10:554/h264/ch1/main/av_stream");
	if(!cap.isOpened())
	{
		printf("failed to open the camera with id %d.\n" , camera_id);
		return -1;
	}
	int num = 0;
	cv::Mat frame;
	stringstream ss;
	string str;
	for(int i = 0 ; i < 1000 ; i++)
	{
		if(i % 10 == 0)
		{
			cout << "get the sequence for : " << (i+1)/10 << endl;
			cap >> frame;
			ss << (i+1)/10;
			ss >> str; 
			ss.clear();
			imwrite("picture-"+str+".png" , frame);
		}
	}
	return 0;
}
