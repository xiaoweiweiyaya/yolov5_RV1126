#include "adduser.h"
#include "ui_adduser.h"
#include <QFileDialog>
#include "facedetect.h"
#include <QDir>
#include <QMessageBox>
addUser::addUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addUser)
{
    ui->setupUi(this);
    QString currentDir = QDir::currentPath();
    QString imagesDirPath = currentDir + "/data";
    QDir imagesDir(imagesDirPath);
    if(!imagesDir.exists()){
        imagesDir.mkdir(imagesDirPath);
    }
}

addUser::~addUser()
{
    delete ui;
}

void addUser::timerEvent(QTimerEvent *e)
{
    //获取摄像头数据，并显示在界面中

    if(cap.isOpened())
    {
        cap>>image;
        if(image.data == nullptr) return;
    }
    //显示视频数据
    cv::Mat rgbImage;
    cv::cvtColor(image, rgbImage,cv::COLOR_BGR2RGB);
    QImage qImg(rgbImage.data, rgbImage.cols, rgbImage.rows, rgbImage.step1(), QImage::Format_RGB888);

    QPixmap mmp = QPixmap::fromImage(qImg);
    mmp = mmp.scaledToWidth(ui->picLb->width());
    ui->picLb->setPixmap(mmp);

}

void addUser::recv_data()
{

}


void addUser::on_resetBt_clicked()
{
    ui->nameEdit->clear();
    ui->birthEdit->setDate(QDate::currentDate());
    ui->compy->clear();
    ui->phone->clear();
}


void addUser::on_addphoto_clicked()
{
    //打开文件对话框，选中图片路径
    QString filepath = QFileDialog::getOpenFileName(this);
    ui->picfilepath->setText(filepath);
    //显示图片
    QPixmap mmp(filepath);
    mmp = mmp.scaledToWidth(ui->picLb->width());
    ui->picLb->setPixmap(mmp);
}

//注册人脸
void addUser::on_registerBt_clicked()
{
    if(ui->nameEdit->text().isEmpty())
    {
        QMessageBox::information(nullptr, tr("失败"), tr("请先填写信息"));
        return;
    }
    //1.调用注册模块，获取faceID
    //2.将信息存储在数据库中
    FaceDetect facedet;
    cv::Mat image = cv::imread(ui->picfilepath->text().toUtf8().data());
    int faceID = facedet.face_register(image);
    qDebug()<<faceID;
    QString headfile = QString("./data/%1.jpg").arg(ui->nameEdit->text().toUtf8().toBase64());
    cv::imwrite(headfile.toUtf8().data(),image);

    QString name = ui->nameEdit->text();
    bool gender = ui->man->isChecked()?1:0;
    QDate birthday = ui->birthEdit->date();
    QString company = ui->compy->text();
    QString phone = ui->phone->text();
    SqlMgr::getInstance()->addUser(faceID,name,gender,birthday,company,phone,headfile);
    QMessageBox::information(this,"成功",QString("注册信息成功"),QMessageBox::Ok);


}

//打开摄像头
void addUser::on_cameraBt_clicked()
{
    if(ui->cameraBt->text() == "打开摄像头") {
        if(cap.open(0))
        {
            ui->cameraBt->setText("关闭摄像头");
            //启动定时器事件
            timerid = startTimer(100);
        }

    }else{
        killTimer(timerid);
        ui->cameraBt->setText("打开摄像头");
        cap.release();
    }
}

//拍照
void addUser::on_photoBt_clicked()
{
    QString headfile = QString("./data/%1.jpg").arg(QString(ui->nameEdit->text().toUtf8().toBase64()));
    ui->picfilepath->setText(headfile);
    cv::imwrite(headfile.toUtf8().data(), image);
    //关闭摄像头显示的定时器
    killTimer(timerid);
    ui->cameraBt->setText("打开摄像头");
    //关闭摄像头
    cap.release();
    //停止接收数据
}

