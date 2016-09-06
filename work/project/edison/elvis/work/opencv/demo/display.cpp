#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <cstring>
#include <iostream>

using namespace std;
using namespace cv;

void cv_display(Mat frame);

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

	cv::Mat frame;

    while (cap.read(frame) )
    {
        if( frame.empty() )
        {
            printf(" --(!) No cpd frame -- Break!\n");
            break;
        }
        //-- 3. Apply the classifier to the frame
        //detectAndDisplay( frame );
        cv_display(frame);
        //-- bail out if escape was pressed
        int c = waitKey(10);
        if( (char)c == 27 ) { return 0; }
    }
	return 0;
}


void cv_display(Mat frame)
{
    String display = "CV_DISPLAY";
    //-- Show what you got
    imshow(display , frame);
}
