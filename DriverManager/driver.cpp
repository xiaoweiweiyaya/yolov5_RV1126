#include "driver.h"
#include "./ui_driver.h"
#include "ui_adduser.h"
#include <QMessageBox>
#include <QThread>
Driver::Driver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Driver)
{
    ui->setupUi(this);

    connect(ui->manager, &QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentWidget(ui->managerUI);
        this->show_data();
    });
    connect(ui->status, &QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentWidget(ui->statusUI);
    });
    connect(ui->update, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentWidget(ui->updateUI);
    });
    this->show_data();
    //设置tableWidget样式
    setTableWidgetStyle(ui->tableWidget);

    //tcp通信
    connect(&mserver,&QTcpServer::newConnection,this,&Driver::accept_client);
    mserver.listen(QHostAddress::Any,8888); //开启监听
    bsize = 0;
    //创建一个线程
    QThread *thread = new QThread();
    faced.moveToThread(thread);
    //启动线程
    thread->start();
    connect(this,&Driver::query,&faced,&FaceDetect::face_query);
    //关联返回faceid结果
    connect(&faced,&FaceDetect::send_faceid,this,&Driver::recv_faceid);

    //绘制QChart图形
    chart = new QChart();
    chart->setTitle("驾驶员疲劳统计图");
    ui->graphicsView->setChart(chart);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->chart()->setTheme(QChart::ChartTheme(0));
    //创建曲线序列
    QLineSeries *driver0 = new QLineSeries();
    //创建坐标轴
    axisX = new QValueAxis;
    axisY = new QValueAxis;
    axisX->setRange(0,10);
    axisX->setTitleText("当前时间:");
    axisX->setLabelFormat("");
    axisX->setTickCount(5);
    axisY->setRange(0,100);
    axisY->setTitleText("异常度");
    axisY->setLabelFormat("%d");
    axisX->setLabelsVisible(false);

    chart->addAxis(axisX,Qt::AlignBottom);
    chart->addAxis(axisY,Qt::AlignLeft);
    ui->graphicsView->setChart(chart);
    series = new QSplineSeries(this);
    chart->addSeries(series);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    series->setName("驾驶员");

    connect(&ctimer,&QTimer::timeout,this,&Driver::qChartHander);
//    connect(&ctimer, &QTimer::timeout,this,[&](){
//        QDateTime currentDateTime =
//    });
    ctimer.setInterval(1000);
    ctimer.start();

}

Driver::~Driver()
{
    delete ui;
}

void Driver::setTableWidgetStyle(QTableWidget *tableWidget)
{
    // 设置表头字体样式
    QFont font;
    font.setBold(true);
    font.setPointSize(12);
    tableWidget->horizontalHeader()->setFont(font);

    // 设置单元格文字居中
    tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    tableWidget->verticalHeader()->setDefaultAlignment(Qt::AlignVCenter);

    //设置选择模式
    //    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //    tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

    // 设置单元格样式
    QString style = "QTableWidget {"
                    "border: 1px solid #d9d9d9;"
                    "background-color: #ffffff;"
                    "selection-background-color: #f5f5f5;"
                    "border:none;"
                    "}"
                    "QTableWidget::item {"
                    "border: none;"
                    "padding: 5px;"
                    "}";
    //    tableWidget->setStyleSheet(style);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->verticalHeader()->setHidden(true);
    // 设置表头拉伸不能超过 tableWidget 的大小
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->horizontalHeader()->setMaximumSectionSize(tableWidget->width() / tableWidget->columnCount());
}

/*添加驾驶员信息*/
void Driver::on_add_driver_clicked()
{
    addUserPtr = new addUser();
    addUserPtr->show();
}


void Driver::on_checkBox_stateChanged(int arg1)
{
    if(arg1){
        //全选
        QList<QTableWidgetItem*>selectedItem = ui->tableWidget->selectedItems();
        foreach(QTableWidgetItem *item, selectedItem){
            item->setCheckState(Qt::Checked);
        }
    }
    else{
        //取消全选
        QList<QTableWidgetItem *>selectedItem = ui->tableWidget->selectedItems();
        foreach(QTableWidgetItem *item, selectedItem){
            item->setCheckState(Qt::Unchecked);
        }
    }
}

//选中删除人员
void Driver::on_delete_driver_clicked()
{
    if(ui->tableWidget->selectedItems().count()>0){
        QList<QTableWidgetItem *> selectedItems = ui->tableWidget->selectedItems();
        QList<QString> columnData;
        foreach(QTableWidgetItem* item, selectedItems){
            int colunm = item->column();
            if(ui->tableWidget->horizontalHeaderItem(colunm)->text()=="id"){
                QString data = item->text();
                columnData.append(data);
            }
        }
        foreach(QString data, columnData){
            SqlMgr::getInstance()->delUser(data);
        }
        QMessageBox::information(this,"成功",QString("成功删除%1位成员").arg(columnData.size()),QMessageBox::Ok);
        this->show_data();
    }
    else{
        QMessageBox::information(nullptr, tr("失败"), tr("请选择需要删除的人员信息！"));
    }
}

//显示人员信息
void Driver::show_data(QString condition)
{
    const QVector<QStringList> Userdata = SqlMgr::getInstance()->getUser(condition);
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    QStringList header = {"id","姓名","性别","生日","公司","电话号码"};
    ui->tableWidget->setColumnCount(header.count());
    ui->tableWidget->setHorizontalHeaderLabels(header);

    ui->tableWidget->setRowCount(Userdata.count());
    for(int i = 0;i<Userdata.count();i++){
        QStringList row = Userdata.at(i);
        for(int j=0;j<row.count();j++){
            QTableWidgetItem *item = new QTableWidgetItem(row.at(j));
            ui->tableWidget->setItem(i,j,item);
        }
    }
}

//搜索人员
void Driver::on_btn_search_clicked()
{
    this->show_data(ui->condition->text());
}

//接收终端连接
void Driver::accept_client()
{
    //获取套接字
    msocket = mserver.nextPendingConnection();
    connect(msocket,&QTcpSocket::readyRead,this,&Driver::recv_data);
}
//获取终端认证数据帧
void Driver::recv_data()
{
    QDataStream stream(msocket); //绑定数据流
    stream.setVersion(QDataStream::Qt_6_2);
    if(bsize == 0){
        if(msocket->bytesAvailable()<(quint64)sizeof(bsize)) return;
        //采集数据长度
        stream>>bsize;
    }
    if(msocket->bytesAvailable() < bsize) return;
    QByteArray data;
    stream>>data;
    bsize = 0;
    if(data.size() == 0) return;
    //正确获取到图像数据
//    QPixmap mmp;
//    mmp.loadFromData(data,".jpg");
//    mmp = mmp.scaled(addUserPtr->ui->picLb->size());
//    addUserPtr->ui->picLb->setPixmap(mmp);

    //识别人脸
    cv::Mat faceImage;
    std::vector<uchar> decode;
    decode.resize(data.size());
    memcpy(decode.data(),data.data(),data.size());
    //解码数据
    faceImage = cv::imdecode(decode, cv::IMREAD_COLOR);
//    int faceid = faced.face_query(faceImage) //消耗资源较多
    emit query(faceImage);


}

void Driver::recv_faceid(uint64_t faceid)
{
    //从数据库中查询faceid对应的个人信息
    //将结果通过socket返回至客户端msocket->write()
    if(faceid < 0) return;
    //根据faceid查询人脸信息库
    qDebug()<<faceid;
    const QStringList Userinfo = SqlMgr::getInstance()->getInfoToDevice((int)faceid);
    if(Userinfo.size() >= 2){
        QString faceID = Userinfo.at(0);
        QString name = Userinfo.at(1);
        QString sdmsg = QString("{\"faceid\":\"%1\",\"name\":\"%2\"}").arg(faceID).arg(name);
        msocket->write(sdmsg.toUtf8());
    }

}

//接收客户端传送来的数据，解析并显示
void Driver::qChartHander()
{
    if(msocket){
        QDateTime dt;
        QString current_dt = dt.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        axisX->setTitleText("当前时间:"+current_dt);
            int y = rand() % 100 - 1;
        y_list.append(y);
        if(y_list.length()>11)
        y_list.removeFirst();
        QList<QPointF> points;
        points.clear();
        for(int i=0;i<y_list.length();i++)
        {

            points.append(QPointF(i,y_list.at(i)));
        }
        series->replace(points);
    }


}

