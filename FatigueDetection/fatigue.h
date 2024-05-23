#ifndef FATIGUE_H
#define FATIGUE_H

#include <QMainWindow>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <string.h>
#include <sys/mman.h>
#include <poll.h>
#include <linux/fb.h>
#include <stdlib.h>
#include <QTimer>
#include "utils.h"
#include "detect_postprocess.h"
#include "detect.h"
#include "detect_loop.h"
#include <time.h>
#include <QTcpSocket>
#include <opencv2/objdetect.hpp>


QT_BEGIN_NAMESPACE
namespace Ui { class Fatigue; }
QT_END_NAMESPACE

class Fatigue : public QMainWindow
{
    Q_OBJECT

public:
    Fatigue(QWidget *parent = nullptr);
    ~Fatigue();
    void* detectloop(void *para);
    //定时器事件 实现人脸认证
    void FaceRecognition(QTimerEvent *e);
signals:
    void attention(unsigned int al);
    void sendImageSignal(cv::Mat &driverImage, Rect &rect);
private:
    Ui::Fatigue *ui;
    int video_fd;
    VideoCapture capture;
    bool m_video_open;
    Mat image;
    rknn_context ctx;
    int output_nboxes_left = 0;

    Result_t Result;
    pthread_t mTid;

    int start = 0;

    unsigned int attentin_level = 0; //分心程度值

    QTimer *timer;

    //haar--级联分类器
    cv::CascadeClassifier cascade;
    //创建网络套接字，定时器
    QTcpSocket msocket;
    QTimer mtimer;
    //是否是同一个人
    int flag;
    QTimer timeidifer;
    //保存人脸数据
    cv::Mat faceMat;

    bool identity = 0;

    QString name = "";

//    int plot_one_box(Mat src,int x1,int x2,int y1,int y2,char *label, char color);

public slots:
    void video_show();
    void timer_connect();
    void stop_connect();
    void start_connect();
    void recv_data();
    void FaceRecognition();
    void sendImage(cv::Mat &driverImage,Rect &rect);
private slots:
    void on_open_close_video_clicked();
    
};
#endif // FATIGUE_H
