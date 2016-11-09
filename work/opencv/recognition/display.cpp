/*************************************************************************
	> File Name: display.cpp
	> Author: Elvis Lei
	> Mail: elvis.linuxer@gmail.com
	> Created Time: Fri 08 Jul 2016 09:27:51 PM CST
************************************************************************/

#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 2  )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    Mat image;
    image = imread( argv[1], 1  );

    if ( !image.data  )
    {
        printf("No image data \n");
        return -1;
    }

    namedWindow("Display Image", WINDOW_AUTOSIZE );
    while(true)
    {
        imshow("Display Image" , image);
        char c = waitKey(100);
        if(c == 'a')
        {
            break;
        }
    }
    return 0;

}
