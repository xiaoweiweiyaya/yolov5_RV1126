#ifndef YOLOV5_DECT_H
#define YOLOV5_DECT_H

#include <opencv2/opencv.hpp>
#include <pthread.h>
#include "detect.h"
#include <unistd.h>
using namespace cv;

#define video_width 640
#define video_height 480
typedef struct{
    yolov5_detect_result_group_t result_group;
    int number;
}Result_t;

static Mat algorithm_image;
static pthread_mutex_t img_lock;


// fmt: BGRA8888
static Scalar colorArray[10] = {
    Scalar(0,   0,   255, 255),
    Scalar(0,   255, 0,   255),
    Scalar(139, 0,   0,   255),
    Scalar(0,   100, 0,   255),
    Scalar(0,   139, 139, 255),
    Scalar(0,   206, 209, 255),
    Scalar(255, 127, 0,   255),
    Scalar(72,  61,  139, 255),
    Scalar(0,   255, 0,   255),
    Scalar(255, 0,   0,   255),
};

int plot_one_box(Mat src, int x1, int x2, int y1, int y2, char *label, char colour);
void *detect_thread_entry(void *para);
void dect_loop();
#endif // YOLOV5_DECT_H
