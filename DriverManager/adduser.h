#ifndef ADDUSER_H
#define ADDUSER_H

#include <QWidget>
#include "sqlmgr.h"
#include <opencv.hpp>
namespace Ui {
class addUser;
}

class addUser : public QWidget
{
    Q_OBJECT

public:
    explicit addUser(QWidget *parent = nullptr);
    ~addUser();
    void timerEvent(QTimerEvent *e);

private slots:
    void recv_data();

    void on_resetBt_clicked();

    void on_addphoto_clicked();

    void on_registerBt_clicked();

    void on_cameraBt_clicked();

    void on_photoBt_clicked();

public:
    Ui::addUser *ui;
    int timerid;
    cv::VideoCapture cap;
    cv::Mat image;

};

#endif // ADDUSER_H
