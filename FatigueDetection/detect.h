#ifndef DETECT_H
#define DETECT_H

#include "detect_postprocess.h"
#include "rknn_api.h"
#include <opencv2/opencv.hpp>

/*
 * yolov5检测初始化函数
 * ctx:输入参数,rknn_context句柄
 * path:输入参数,算法模型路径
 */
int yolov5_detect_init(rknn_context *ctx, const char *path);
/*
 * yolov5检测执行函数
 * ctx:输入参数,rknn_context句柄
 * input_image:输入参数,图像数据输入(cv::Mat是Opencv的类型)
 * output_dets:输出参数，目标检测框输出
 */
int yolov5_detect_run(rknn_context ctx, cv::Mat input_image, yolov5_detect_result_group_t *detect_result_group);
/*
 * yolov5检测释放函数
 * ctx:输入参数,rknn_context句柄
 */
int yolov5_detect_release(rknn_context ctx);
static void printRKNNTensor(rknn_tensor_attr *attr);
static int letter_box(cv::Mat input_image, cv::Mat *output_image, int model_input_size);


#endif // DETECT_H
