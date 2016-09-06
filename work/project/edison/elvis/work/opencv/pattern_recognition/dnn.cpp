#ifndef _DNN_CPP
#define _DNN_CPP
#include <opencv2/dnn.hpp>
#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;
using namespace cv;
using namespace cv::dnn;

int main(int argc , char ** argv)
{
    Net * net = new Net();
    net->addLayer("input" , "" , );
    delete net;
    return EXIT_SUCCESS;
}
#endif
