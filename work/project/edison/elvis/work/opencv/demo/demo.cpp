#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/photo/photo.hpp>
#include <cstring>
using namespace std;

int main()
{
	IplImage *frame = NULL;
	int num = 0;
	int key;
	CvCapture *input_camera = cvCaptureFromCAM(-1);
	frame = cvQueryFrame(input_camera);
	while(frame != NULL)
	{
		num++;
		cout << "get the num " << num << endl;
		frame = cvQueryFrame(input_camera);
		if(num % 10 == 0)
		{
			cout << "get the image " << endl;
			std::stringstream ss;
			std::string str;
			ss<<num;
			ss>>str;
			cvSaveImage(str.c_str(),frame);
		}
	}
	cvReleaseCapture(&input_camera);
	return 0;
}
