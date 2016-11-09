#include <QCoreApplication>
#include <QDebug>
#include <cstring>
#include <iostream>

#include "http.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HTTP http;

    http.setSync(true);

    // http.setUrl("https://open.ys7.com/api/lapp/token/get"); // get the accesss token
    http.setUrl("https://open.ys7.com/api/lapp/device/capture"); // capture the device picture
    // http.setUrl("https://open.ys7.com/api/lapp/device/list"); // devices list

    // http.setUrl("https://open.ys7.com/api/lapp/device/info"); // singale device's info

    // http.setUrl("https://open.ys7.com/api/lapp/live/video/list"); // get the user live video

    http.addPostdata("appKey" , "c295e6dc623e4f03a0d915e43bdb0ae3");
    http.addPostdata("appSecret" , "ccb7eaa12d2b3f610e8c3bb4657bc92b1");
    http.addPostdata("accessToken" , "at.43m2pkm09gtb4xwmbbpzfa89casrsou8-7p0dv6y2n3-0svba0l-vutoxugka");
    http.addPostdata("deviceSerial" , "624233133");
    http.addPostdata("channelNo" , "1");

    http.postRequest("");

    // qDebug() << http.getInfo();

    std::string temp = http.getInfo().toStdString();

    std::cout << temp << std::endl;

    return a.exec();
}
