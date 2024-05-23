#include "detect.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>
#include <opencv2/opencv.hpp>
#include "rknn_api.h"

#include <sys/time.h>

using namespace std;
using namespace cv;

static void printRKNNTensor(rknn_tensor_attr *attr)
{
    printf("index=%d name=%s n_dims=%d dims=[%d %d %d %d] n_elems=%d size=%d "
           "fmt=%d type=%d qnt_type=%d fl=%d zp=%d scale=%f\n",
           attr->index, attr->name, attr->n_dims, attr->dims[3], attr->dims[2],
           attr->dims[1], attr->dims[0], attr->n_elems, attr->size, 0, attr->type,
           attr->qnt_type, attr->fl, attr->zp, attr->scale);
}

static int letter_box(cv::Mat input_image, cv::Mat *output_image, int model_input_size)
{
    int input_width, input_height;

    input_width = input_image.cols;
    input_height = input_image.rows;
    float ratio;
    ratio = min((float)model_input_size / input_width, (float)model_input_size / input_height);

    int new_width, new_height;
    new_width = round(ratio * input_width );
    new_height = round(ratio * input_height);


    int height_padding = 0;
    int width_padding = 0;
    int top = 0;
    int bottom = 0;
    int left = 0;
    int right = 0;
    if( new_width >= new_height)
    {
        height_padding = new_width - new_height;
        if( (height_padding % 2) == 0 )
        {
            top = (int)((float)(height_padding/2));
            bottom = (int)((float)(height_padding/2));
        }
        else
        {
            top = (int)((float)(height_padding/2));
            bottom = (int)((float)(height_padding/2))+1;
        }
    }
    else
    {
        width_padding = new_height - new_width;
        if( (width_padding % 2) == 0 )
        {
            left = (int)((float)(width_padding/2));
            right = (int)((float)(width_padding/2));
        }
        else
        {
            left = (int)((float)(width_padding/2));
            right = (int)((float)(width_padding/2))+1;
        }

    }

    cv::Mat resize_img;

    cv::resize(input_image, resize_img, cv::Size(new_width, new_height));
    cv::copyMakeBorder(resize_img, *output_image, top, bottom, left, right, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));

    return 0;
}


int yolov5_detect_init(rknn_context *ctx, const char *path)
{
    int ret;

    // Load model
    FILE *fp = fopen(path, "rb");
    if(fp == NULL)
    {
        printf("fopen %s fail!\n", path);
        return -1;
    }
    fseek(fp, 0, SEEK_END);   //fp指向end,fseek(FILE *stream, long offset, int fromwhere);
    int model_len = ftell(fp);   //相对文件首偏移
    unsigned char *model_data = (unsigned char*)malloc(model_len);

    fseek(fp, 0, SEEK_SET);   //SEEK_SET为文件头
    if(model_len != fread(model_data, 1, model_len, fp))
    {
        printf("fread %s fail!\n", path);
        free(model_data);
        return -1;
    }
    fclose(fp);

    //init
    ret = rknn_init(ctx, model_data, model_len, RKNN_FLAG_PRIOR_MEDIUM);
    if(ret < 0)
    {
        printf("rknn_init fail! ret=%d\n", ret);
        return -1;
    }

    free(model_data);

    return 0;
}

static int scale_coords(yolov5_detect_result_group_t *detect_result_group, int img_width, int img_height, int model_size)
{
    for (int i = 0; i < detect_result_group->count; i++)
    {
        yolov5_detect_result_t *det_result = &(detect_result_group->results[i]);


        int x1 = det_result->box.left;
        int y1 = det_result->box.top;
        int x2 = det_result->box.right;
        int y2 = det_result->box.bottom;


        if( img_width >= img_height )
        {
            int image_max_len = img_width;
            float gain;
            gain = (float)model_size / image_max_len;
            int resized_height = img_height * gain;
            int height_pading = (model_size - resized_height)/2;
            y1 = (y1 - height_pading);
            y2 = (y2 - height_pading);
            x1 = int(x1 / gain);
            y1 = int(y1 / gain);
            x2 = int(x2 / gain);
            y2 = int(y2 / gain);

            det_result->box.left = x1;
            det_result->box.top = y1;
            det_result->box.right = x2;
            det_result->box.bottom = y2;
        }
        else
        {
            int image_max_len = img_height;
            float gain;
            gain = (float)model_size / image_max_len;
            int resized_width = img_width * gain;
            int width_pading = (model_size - resized_width)/2;
            x1 = (x1 - width_pading);
            x2 = (x2 - width_pading);
            x1 = int(x1 / gain);
            y1 = int(y1 / gain);
            x2 = int(x2 / gain);
            y2 = int(y2 / gain);

            det_result->box.left = x1;
            det_result->box.top = y1;
            det_result->box.right = x2;
            det_result->box.bottom = y2;
        }

    }

    return 0;
}

int yolov5_detect_run(rknn_context ctx, cv::Mat input_image, yolov5_detect_result_group_t *detect_result_group)
{
    int img_width = 0;
    int img_height = 0;
    int img_channel = 0;

    size_t actual_size = 0;
    const float vis_threshold = 0.1;
    const float nms_threshold = 0.5;
    const float conf_threshold = 0.2;
    int ret;

    img_width = input_image.cols;
    img_height = input_image.rows;

    rknn_sdk_version version;
    ret = rknn_query(ctx, RKNN_QUERY_SDK_VERSION, &version,
                     sizeof(rknn_sdk_version));
    if (ret < 0)
    {
        printf("rknn_init error ret=%d\n", ret);
        return -1;
    }
    /*
    printf("sdk version: %s driver version: %s\n", version.api_version,
           version.drv_version);
    */

    rknn_input_output_num io_num;
    ret = rknn_query(ctx, RKNN_QUERY_IN_OUT_NUM, &io_num, sizeof(io_num));
    if (ret < 0)
    {
        printf("rknn_init error ret=%d\n", ret);
        return -1;
    }
    /*
    printf("model input num: %d, output num: %d\n", io_num.n_input,
           io_num.n_output);
    */

    rknn_tensor_attr input_attrs[io_num.n_input];
    memset(input_attrs, 0, sizeof(input_attrs));
    for (int i = 0; i < io_num.n_input; i++)
    {
        input_attrs[i].index = i;
        ret = rknn_query(ctx, RKNN_QUERY_INPUT_ATTR, &(input_attrs[i]),
                         sizeof(rknn_tensor_attr));
        if (ret < 0)
        {
            printf("rknn_init error ret=%d\n", ret);
            return -1;
        }
        //printRKNNTensor(&(input_attrs[i]));
    }

    rknn_tensor_attr output_attrs[io_num.n_output];
    memset(output_attrs, 0, sizeof(output_attrs));
    for (int i = 0; i < io_num.n_output; i++)
    {
        output_attrs[i].index = i;
        ret = rknn_query(ctx, RKNN_QUERY_OUTPUT_ATTR, &(output_attrs[i]),
                         sizeof(rknn_tensor_attr));
        //printRKNNTensor(&(output_attrs[i]));
    }

    int input_channel = 3;
    int input_width = 0;
    int input_height = 0;
    if (input_attrs[0].fmt == RKNN_TENSOR_NCHW)
    {
        //printf("model is NCHW input fmt\n");
        input_width = input_attrs[0].dims[0];
        input_height = input_attrs[0].dims[1];
    }
    else
    {
        //printf("model is NHWC input fmt\n");
        input_width = input_attrs[0].dims[1];
        input_height = input_attrs[0].dims[2];
    }

    /*
    printf("model input height=%d, width=%d, channel=%d\n", height, width,
           channel);
    */

    /* Init input tensor */
    rknn_input inputs[1];
    memset(inputs, 0, sizeof(inputs));
    inputs[0].index = 0;
    inputs[0].type = RKNN_TENSOR_UINT8;
    inputs[0].size = input_width * input_height * input_channel;
    inputs[0].fmt = RKNN_TENSOR_NHWC;
    inputs[0].pass_through = 0;

    /* Init output tensor */
    rknn_output outputs[io_num.n_output];
    memset(outputs, 0, sizeof(outputs));

    for (int i = 0; i < io_num.n_output; i++)
    {
        outputs[i].want_float = 0;
    }

    cv::Mat letter_image;
    letter_box(input_image, &letter_image, input_width);
    inputs[0].buf = letter_image.data;

    rknn_inputs_set(ctx, io_num.n_input, inputs);
    ret = rknn_run(ctx, NULL);
    ret = rknn_outputs_get(ctx, io_num.n_output, outputs, NULL);

    // Post process
    std::vector<float> out_scales;
    std::vector<uint8_t> out_zps;
    for (int i = 0; i < io_num.n_output; ++i)
    {
        out_scales.push_back(output_attrs[i].scale);
        out_zps.push_back(output_attrs[i].zp);
    }


    yolov5_post_process_u8((uint8_t *)outputs[0].buf, (uint8_t *)outputs[1].buf, (uint8_t *)outputs[2].buf, input_height, input_width,
                           conf_threshold, nms_threshold, out_zps, out_scales, detect_result_group);


    /*
    yolov5_post_process_fp((float *)outputs[0].buf, (float *)outputs[1].buf, (float *)outputs[2].buf, input_height, input_width,
                        conf_threshold, nms_threshold, &detect_result_group);
    */

    rknn_outputs_release(ctx, io_num.n_output, outputs);

    scale_coords(detect_result_group, img_width, img_height, input_width);

    return 0;
}


int yolov5_detect_release(rknn_context ctx)
{
    rknn_destroy(ctx);
    return 0;
}
