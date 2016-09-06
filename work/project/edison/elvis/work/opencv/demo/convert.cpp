#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;
using namespace rp::util;
using namespace rp::deps::libuxbx_arap;
using namespace rp::drivers::display;

shared_ptr<RoboPeakUsbDisplayDevice> display;

/*
int main(int argc , char ** argv)
{
	int camera_id = 0;
	if(argc > 1) camera_id = atoi(argv[1]);
	cv::VideoCapture cap(camera_id);
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
*/

int main(int argc , char ** argv)
{
	int camera_id = 0;
	if(argc > 1) camera_id = atoi(argv[1]);
	cv::VideoCapture cap(camera_id);
	if(!cap.isOpened())
	{
		printf("Failed to open it\n");
		return -1;
	}
	cv::Mat frame;
	cv::Mat scaled_qvga;
	cv::Mat RGB565_Frame;
	RGB565_Frame.create(240 , 320 , CV_16UCl);
	scaled_qvga.create(240 , 320 , CV_8UC3);
	display = RoboPeakUsbDisplayDevice::openFirstDevice();
	display -> enable();
	while(1)
	{
		cap >> frame;
		cv::resize(frame , scaled_qvga,cv::Size(320,240));
		cv::cvtColor(scaled_qvga,RGB565_Frame , CV_RGB2BGR565);
		display -> bitblt(0,0,320,240,RoboPeakUsbDisplayBitOperationCopy,RGB565_Frame.ptr());
	}
	return 0;
}

