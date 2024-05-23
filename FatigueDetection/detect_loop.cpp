#include "detect_loop.h"


void *detect_thread_entry(void *para)
{
//    int ret;
//    Result_t *pResult = (Result_t *)para;
//    //yolov5模型初始化
//    rknn_context ctx;
//    yolov5_detect_init(&ctx, "best.rknn");

//    while(1)
//    {
//        if(algorithm_image.empty()){
//            usleep(5);
//            continue;
//        }
//        pthread_mutex_lock(&img_lock);
//        image = algorithm_image.clone();
//        pthread_mutex_unlock(&img_lock);
//        //算法推理
//        ret = yolov5_detect_run(ctx, image, &pResult->result_group);
//        pResult->number = pResult->result_group.count;
//        if(pResult->number <= 0){
//            usleep(1000);
//            continue;
//        }
//        printf("\n>>>>>>>>>>>>>>>>>>>>>>\n");
//        printf("number: %d\n", pResult->number);
//        usleep(16*1000);
//    }
//    /*yolov5检测模型释放*/
//    yolov5_detect_release(ctx);
}

//video识别算法
void dect_loop()
{

}

int plot_one_box(Mat src, int x1, int x2, int y1, int y2, char *label, char colour)
{
    int tl = round(0.002 * (src.rows + src.cols) / 2) + 1;
    rectangle(src, cv::Point(x1, y1), cv::Point(x2, y2), colorArray[(unsigned char)colour], 3);

    int tf = max(tl -1, 1);

    int base_line = 0;
    cv::Size t_size = getTextSize(label, FONT_HERSHEY_SIMPLEX, (float)tl/3, tf, &base_line);
    int x3 = x1 + t_size.width;
    int y3 = y1 - t_size.height - 3;

    rectangle(src, cv::Point(x1, y1), cv::Point(x3, y3), colorArray[(unsigned char)colour], -1);
    putText(src, label, cv::Point(x1, y1 - 2), FONT_HERSHEY_SIMPLEX, (float)tl/3, cv::Scalar(255, 255, 255, 255), tf, 8);
    return 0;
}
