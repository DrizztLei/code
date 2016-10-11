#ifndef READ_CPP
#define READ_CPP                                                \

#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;
using namespace cv;

void cv_show_rgb(Mat frame)
{
    cout << frame << endl;
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

int main(int argc , char ** argv)
{
    const string window = "HRQR";
    if(argc < 2)
    {
        cout << "Error for picture not found . " << endl;
        return EXIT_FAILURE;
    }

    Mat picture = imread(argv[1] , IMREAD_COLOR);



    return EXIT_SUCCESS;
}
#endif
