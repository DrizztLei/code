#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;
int main(int argc , char ** argv)
{
	int camera_id = -1;
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
