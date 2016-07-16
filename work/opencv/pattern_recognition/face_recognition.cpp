#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace cv;

static Mat norm_0_255(InputArray _src) {
    Mat src = _src.getMat();
    Mat dst;
    switch(src.channels()) {
    case 1:
        cv::normalize(_src, dst, 0,255, NORM_MINMAX, CV_8UC1);
        break;
    case 3:
        cv::normalize(_src, dst, 0,255, NORM_MINMAX, CV_8UC3);
        break;
    default:
        src.copyTo(dst);
        break;
    }
    return dst;
}

int main(int argc, char ** argv)
{

    return 0;
}
