#include "sqlmgr.h"
#include "qdatetime.h"
#include <QMessageBox>
SqlMgr* SqlMgr::instance = nullptr;
bool SqlMgr::init()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("driver");
    db.setUserName("root");
    db.setPassword("Chenwei00");
    if(!db.open()){
        qDebug()<<"Failed to open database:";
        return false;
    }
    return true;
}

void SqlMgr::addUser(unsigned int faceid,QString name, bool gender, QDate birthday, QString company, QString phone,QString headfile)
{
    QSqlQuery q(db);
    const QString queryString = QString("insert into drivermanager (id,name,gender,birthday,company,phone,headfile) values (?,?,?,?,?,?,?);");
    q.prepare(queryString);
    q.addBindValue(faceid);
    q.addBindValue(name);
    q.addBindValue(gender);
    q.addBindValue(birthday);
    q.addBindValue(company);
    q.addBindValue(phone);
    q.addBindValue(headfile);
    if(!q.exec()){
        QMessageBox::warning(nullptr, QMessageBox::tr("Error"), QMessageBox::tr("人员添加失败"));
        return;
    }

}

void SqlMgr::delUser(QString strId)
{
    QSqlQuery q(db);
    const QString queryString = QString("DELETE FROM drivermanager WHERE id = (?);");
    q.prepare(queryString);
    q.addBindValue(strId);
    if(!q.exec()){
        QMessageBox::warning(nullptr, QMessageBox::tr("Error"), QMessageBox::tr("删除数据失败"));
        return;
    }
}

QVector<QStringList> SqlMgr::getUser(QString strCondition)
{
    QVector<QStringList> userList;
    QSqlQuery q(db);
    QString queryString = QString("select * from drivermanager where name like ?;");
    q.prepare(queryString);
    q.addBindValue("%"+strCondition+"%");
    if(!q.exec()){
        QMessageBox::warning(nullptr, QMessageBox::tr("Error"), QMessageBox::tr("获取用户失败"));
        return userList;
    }
    while(q.next()){
        QStringList row;
        row.append(q.value(0).toString());
        row.append(q.value(1).toString());
        row.append(q.value(2).toString().toInt()?"男":"女");
        row.append(q.value(3).toString());
        row.append(q.value(4).toString());
        row.append(q.value(5).toString());
        userList.append(row);
    }
    return userList;
}

QStringList SqlMgr::getInfoToDevice(int faceid)
{
    QStringList info;
    QSqlQuery q(db);
    QString queryString = QString("select id, name from drivermanager where id = (?);");
    q.prepare(queryString);
    q.addBindValue(faceid);
    if(!q.exec()){
        QMessageBox::warning(nullptr, QMessageBox::tr("Error"), QMessageBox::tr("获取用户失败"));
        return info;
    }
    while(q.next()){
        info.append(q.value(0).toString());
        info.append(q.value(1).toString());

    }
    return info;
}

SqlMgr::SqlMgr()
{

}
