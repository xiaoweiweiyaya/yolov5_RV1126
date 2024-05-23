#ifndef DETECT_POSTPROCESS_H
#define DETECT_POSTPROCESS_H

#include <stdint.h>
#include <vector>
#define YOLOV5_NAME_MAX_SIZE 16
#define YOLOV5_NUMB_MAX_SIZE 200
#define YOLOV5_CLASS_NUM     4
#define YOLOV5_PROP_BOX_SIZE     (5+YOLOV5_CLASS_NUM)

typedef struct
{
    int left;
    int right;
    int top;
    int bottom;
} YOLOV5_BOX_RECT;

typedef struct
{
    char name[YOLOV5_NAME_MAX_SIZE];
    int class_index;
    YOLOV5_BOX_RECT box;
    float prop;
} yolov5_detect_result_t;

typedef struct
{
    int id;
    int count;
    yolov5_detect_result_t results[YOLOV5_NUMB_MAX_SIZE];
} yolov5_detect_result_group_t;

int yolov5_post_process_u8(uint8_t *input0, uint8_t *input1, uint8_t *input2, int model_in_h, int model_in_w,
                           float conf_threshold, float nms_threshold,
                           std::vector<uint8_t> &qnt_zps, std::vector<float> &qnt_scales,
                           yolov5_detect_result_group_t *group);

int yolov5_post_process_fp(float *input0, float *input1, float *input2, int model_in_h, int model_in_w,
                           float conf_threshold, float nms_threshold,
                           yolov5_detect_result_group_t *group);
#endif // DETECT_POSTPROCESS_H
