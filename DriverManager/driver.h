#ifndef DRIVER_H
#define DRIVER_H

#include <QMainWindow>
#include <QTableWidget>
#include "adduser.h"
#include <QTableWidget>
#include <QList>
#include "qchartview.h"
#include "qtimer.h"
#include "sqlmgr.h"
#include <QTcpSocket>
#include <QTcpServer>
#include "facedetect.h"
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
QT_BEGIN_NAMESPACE
namespace Ui { class Driver; }
QT_END_NAMESPACE

class Driver : public QMainWindow
{
    Q_OBJECT

public:
    Driver(QWidget *parent = nullptr);
    ~Driver();
    void setTableWidgetStyle(QTableWidget *tableWidget);

private slots:
    void on_add_driver_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_delete_driver_clicked();

    void show_data(QString condition = "");

    void on_btn_search_clicked();

    void accept_client();

    void recv_data();

    void recv_faceid(uint64_t faceid);

    void qChartHander();

signals:
    void query(cv::Mat& image);

private:
    Ui::Driver *ui;
    QTcpServer mserver;
    QTcpSocket *msocket;
    quint64 bsize;
    addUser *addUserPtr;
    FaceDetect faced;

    //绘制QChart
    QChart *chart;
    QValueAxis *axisX;
    QValueAxis *axisY;

    QSplineSeries *series;
    QTimer ctimer;
    QList<int> y_list;
public:

};
#endif // DRIVER_H
