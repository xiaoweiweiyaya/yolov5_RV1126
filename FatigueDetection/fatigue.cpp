#include "fatigue.h"
#include "./ui_fatigue.h"
#include "QtGui/QScreen"
#include "QDateTime"
#include "QRandomGenerator"
#include "QDebug"
#include <QDir>
#include <sys/select.h>
//#include <QCameraInfo>
#include <QList>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
Fatigue::Fatigue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Fatigue)
{
    ui->setupUi(this);
    timer = new QTimer();

    //获取当前目录
    QString currentDir = QDir::currentPath();
    //拼接photo文件夹路径
    QString photoDirPath = currentDir + "/photo";
    //创建QDir对象
    QDir photoDir(photoDirPath);
    if(!photoDir.exists()){
        //创建photo文件夹
        if(photoDir.mkdir(photoDirPath))
            printf("创建photo文件夹成功\n");
        else
            printf("创建photo文件夹失败\n");
    }
    else
        printf("photo文件夹存在\n");

    /*算法模型初始化*/
    yolov5_detect_init(&ctx, "best.rknn");

    /*QTimer更新时间*/
    QTimer *time = new QTimer();
    connect(time,&QTimer::timeout, [&](){
        QDateTime currentTime = QDateTime::currentDateTime();
        QString currentDateTime = currentTime.toString("mm:ss");
        ui->clock->setText(currentDateTime);
    });
    time->start(1000);

    /*获取摄像头信息*/
//    QList<QCameraInfo> infos = QCameraInfo::availableCameras();
//    foreach(QCameraInfo info, infos){
//        ui->vido_cbx->addItem(info.deviceName);
//    }
    /*分心程度*/
    connect(this, &Fatigue::attention,this,[&](int al){
        ui->fx_pB->setValue(al%100);
    });

    //认证实现
    cascade.load("./haarcascade_frontalface_alt2.xml");
    connect(&msocket,&QTcpSocket::disconnected,this,&Fatigue::start_connect);
    connect(&msocket,&QTcpSocket::connected,this,&Fatigue::stop_connect);  
    connect(&mtimer,&QTimer::timeout,this,&Fatigue::timer_connect);
    connect(&msocket,&QTcpSocket::readyRead,this,&Fatigue::recv_data);
    connect(&timeidifer,SIGNAL(timeout()),this,SLOT(FaceRecognition()));
    connect(this,&Fatigue::sendImageSignal,this,&Fatigue::sendImage);
    //启动定时器 5s连接一次，成功就不连接
    mtimer.start(5000);
    flag = 0;

}

Fatigue::~Fatigue()
{
    yolov5_detect_release(ctx);
    delete ui;
}

//进行驾驶员的人脸认证
void Fatigue::FaceRecognition()
{
    if(!m_video_open){
        return;
    }
    Mat driverImage;
    if(capture.grab()){
        capture.read(driverImage);
    }
    Mat grayImage;
    //转灰度图
    cvtColor(driverImage,grayImage,COLOR_BGR2GRAY);
    std::vector<Rect> faceRects;
    cascade.detectMultiScale(grayImage,faceRects);
    if(faceRects.size()>0 && flag >= 0)
    {

        Rect rect = faceRects.at(0);
        rectangle(driverImage, rect, Scalar(0,0,255));
        //移动人脸框
        // ui->video_zoom->setVisible(true);
        // ui->video_zoom->move(rect.x,rect.y);

        if(flag > 2){

            emit sendImageSignal(driverImage,rect);
        }
        flag++;
    }if(faceRects.size() == 0){
        // ui->video_zoom->setVisible(false);
        flag = 0;
    }
    if(driverImage.data == nullptr) return;
    //显示认证图像效果
    cvtColor(driverImage,driverImage,COLOR_BGR2RGB);
    QImage image(driverImage.data,driverImage.cols,driverImage.rows,driverImage.step1(),QImage::Format_RGB888);
    QPixmap mmp = QPixmap::fromImage(image);
    mmp = mmp.scaledToWidth(ui->video_zoom->width());
    ui->video_zoom->setPixmap(mmp.scaled(ui->video_zoom->size(),Qt::KeepAspectRatio));
}

void Fatigue::sendImage(cv::Mat &driverImage, Rect &rect)
{
    //将Mat数据压缩到jpg格式并转换为二进制格式,发送至server
    std::vector<uchar> buf;
    cv::imencode(".jpg",driverImage,buf);
    QByteArray byte((const char*)buf.data(),buf.size());

    quint64 backsize = byte.size();
    QByteArray sendData;
    QDataStream stream(&sendData, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_2);
    stream<<backsize<<byte;
    //发送数据
    msocket.write(sendData);
    flag = -2;

    faceMat = driverImage(rect);
    //保存
    imwrite("./photo/face.jpg",faceMat);
}

void Fatigue::video_show()
{

    //打开摄像头
    if(m_video_open && identity){
//        Mat image;
        capture>>image;
        if(image.empty()){
            return;
        }

        ui->detect_status->setText(QString("欢迎你 %1").arg(name));
        /*算法运行*/
        yolov5_detect_result_group_t detect_result_group;
        cv::Mat rgb_img;
        cv::cvtColor(image, rgb_img, COLOR_BGR2RGB);

        // struct timeval start;
        // struct timeval end;
        // float time_use=0;

        // gettimeofday(&start,NULL);
        yolov5_detect_run(ctx, rgb_img, &detect_result_group);

        // gettimeofday(&end,NULL);
        // time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
        // printf("time_use is %f\n",time_use/1000);

        for(int i=0; i<detect_result_group.count; i++)
        {
            yolov5_detect_result_t *det_result = &(detect_result_group.results[i]);
            if( det_result->prop < 0.3 ){
                continue;
            }
            // printf("%s @ (%d %d %d %d) %f\n",
            //        det_result->name,
            //        det_result->box.left, det_result->box.top, det_result->box.right, det_result->box.bottom,
            //        det_result->prop);
            int x1 = det_result->box.left;
            int y1 = det_result->box.top;
            int x2 = det_result->box.right;
            int y2 = det_result->box.bottom;
            if(strcmp(det_result->name,"face")!=0)
            {
                emit attention(attentin_level+=2);
            }else{          
                attentin_level--;
                if(attentin_level < 0) attentin_level = 0;
            }

            char label_text[50];
            memset(label_text, 0 , sizeof(label_text));
            sprintf(label_text, "%s %0.2f",det_result->name, det_result->prop);
            plot_one_box(rgb_img, x1, x2, y1, y2, label_text, i%10);
        }
        //将opencv的Mat图像转为Qt的QImage
        QImage qimage(rgb_img.data, rgb_img.cols, rgb_img.rows, static_cast<int>(rgb_img.step), QImage::Format_RGB888);
        QPixmap pixmap = QPixmap::fromImage(qimage);

        //QLabel显示图像
        ui->video_zoom->setPixmap(pixmap.scaled(ui->video_zoom->size(),Qt::KeepAspectRatio));

    }


}

//接收到数据
void Fatigue::recv_data()
{
    // printf("recv_data\n");
    QByteArray array = msocket.readAll();
    //json解析
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(array, &err);
    if(err.error != QJsonParseError::NoError)
    {
        qDebug()<<"json data err";
        return;
    }
    QJsonObject obj = doc.object();
    int id = obj.value("faceid").toString().toInt();
    name = obj.value("name").toString();
    if(id == -1){
        //认证失败
        identity = 0;
        //开启定时器
        timeidifer.start(100);
        timer->stop();
        ui->detect_status->setText("认证失败");
        return;
    }
    //成功认证
    identity = 1;
    //关闭定时器
    timeidifer.stop();
    connect(timer, SIGNAL(timeout()), this, SLOT(video_show()));
    timer->start(80);
    ui->detect_status->setText("认证成功");


}

//连接服务器
void Fatigue::timer_connect()
{
    msocket.connectToHost("192.168.31.6",8888);
    printf("正在连接服务器\n");
}

//停止连接
void Fatigue::stop_connect()
{
    mtimer.stop();
    printf("成功连接服务器\n");
}

//启动连接
void Fatigue::start_connect()
{
    mtimer.start(5000);
    printf("断开服务器\n");
}



void Fatigue::on_open_close_video_clicked()
{
    identity = false;
    
    if(!m_video_open)
    {
        // ui->video_zoom->clear();
        ui->detect_status->setText("摄像头开启中...");
        //打开摄像头
        ui->open_close_video->setIcon(QIcon(":/pose.svg"));
        ui->open_close_video->setText("关闭摄像头");
        capture.open("/dev/video45");
        
        if (!capture.isOpened()) // check if we succeeded
        {
            m_video_open=false;
            ui->open_close_video->setIcon(QIcon(":/triangle-play.svg"));
            ui->open_close_video->setText("打开摄像头");
            return;
        }
        printf("打开摄像头\n");
        // timer->start(80);
        m_video_open=true;

        ui->detect_status->setText("摄像头开启成功...");
        //开启人脸认证的定时器
        timeidifer.start(100);
    }
    else
    {
        //关闭人脸认证的定时器
        timeidifer.stop();
        ui->detect_status->setText("摄像关闭中...");
        ui->open_close_video->setIcon(QIcon(":/triangle-play.svg"));
        ui->open_close_video->setText("打开摄像头");
        capture.release();
        // timer->stop();
        /* 算法模型空间释放 */
//        yolov5_detect_release(ctx);
        m_video_open=false;
        ui->detect_status->setText("摄像已关闭");
    }


}




