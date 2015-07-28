#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCryptographicHash>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    connect_mysql();
}

void MainWindow::connect_mysql()
{
    QString hostUrl = ui->le_serverip->text().trimmed();
    qint32 port = 3306;
    QString dbName ="cms";
    QString userName = "cms";
    QString pwd = "xy";
    QString newPwd = ui->le_newpwd->text().trimmed();

    if(hostUrl.isEmpty())
    {
        hostUrl = "192.168.0.99";
    }
    if(! ui->le_port->text().trimmed().isEmpty())
    {
        port = ui->le_port->text().trimmed().toInt();;
    }
    QSqlDatabase dbSQL=QSqlDatabase::addDatabase("QMYSQL");
    dbSQL.setHostName(hostUrl);
    dbSQL.setPort(port);
    dbSQL.setDatabaseName(dbName);
    dbSQL.setUserName(userName);
    dbSQL.setPassword(pwd);

    if( !dbSQL.open() )
    {
        //qDebug()<<"this,warning,failure";
        QMessageBox::about(NULL,"提示","连接数据库失败"+dbSQL.lastError().text());
    }
    else
    {
        qDebug()<<"this,ok,success";
        newPwd = getSHA1(newPwd);
        qDebug()<<newPwd;
        updatePwd(newPwd);

    }

}

void MainWindow::updatePwd(QString pwd)
{
    QSqlQuery query;
    query.prepare("update person set Password_Hash = '"+pwd+"' where User ='cms'");
    //query.addBindValue(pwd);
    bool flag = query.exec();
    if(flag == true)
    {
        QMessageBox::about(NULL,"提示","密码修改成功");
    }
    else
    {
        QMessageBox::about(NULL,"提示","密码修改失败");
    }
}

QString MainWindow::getSHA1(QString str)
{
    //sha1 hash
    QByteArray string=str.toLatin1().data();
    QCryptographicHash *hash=new QCryptographicHash(QCryptographicHash::Sha1);
    hash->addData(string);
    QByteArray sha1=hash->result();
    return QString(sha1.toHex());
}
