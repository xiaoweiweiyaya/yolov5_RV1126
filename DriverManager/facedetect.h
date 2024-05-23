#ifndef FACEDETECT_H
#define FACEDETECT_H

#include <QObject>
#include <seeta/FaceEngine.h>
#include <opencv.hpp>
using namespace cv;
//人脸数据存储，人脸认证
class FaceDetect : public QObject
{
    Q_OBJECT
public:
    explicit FaceDetect(QObject *parent = nullptr);
    ~FaceDetect();

public slots:
    int64_t face_register(Mat& faceimage);
    int face_query(Mat& faceimage);
signals:
    void send_faceid(int64_t faceid);
private:
    seeta::FaceEngine *fenginerptr;

};

#endif // FACEDETECT_H
