#ifndef UTILS_H
#define UTILS_H
#include <opencv2/opencv.hpp>
#include <QImage>

using namespace cv;
QImage cvMat2QImage(const cv::Mat& mat);

Mat QImage2cvMat(QImage image);

#endif // UTILS_H
