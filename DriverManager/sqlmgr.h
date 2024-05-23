#ifndef SQLMGR_H
#define SQLMGR_H

#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
/*数据库管理类  采用单例模式实现全局数据访问控制*/
class SqlMgr
{
public:
    ~SqlMgr();
    static SqlMgr* getInstance(){
        if(nullptr == instance){
            instance = new SqlMgr();
        }
        return instance;
    }
    bool init();
    //获取该id号

    //添加驾驶员信息
    void addUser(unsigned int faceid,QString name, bool gender, QDate birthday, QString company, QString phone,QString headfile);

    //删除驾驶员信息
    void delUser(QString strId);
    //TODO:修改驾驶员信息
    void modUser(int id);
    //获取所有驾驶员信息
    QVector<QStringList> getUser(QString strCondition = "");
    //查询id对应的信息
    QStringList getInfoToDevice(int faceid);
private:
    SqlMgr();
    static SqlMgr* instance;
    QSqlDatabase db;
};

#endif // SQLMGR_H
