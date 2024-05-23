#include "driver.h"

#include <QApplication>
#include <opencv.hpp>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<cv::Mat>("cv::Mat&");
    qRegisterMetaType<cv::Mat>("cv::Mat");
    qRegisterMetaType<int64_t>("int64_t");
    SqlMgr::getInstance()->init();
    Driver w;
    w.show();
    return a.exec();
}
