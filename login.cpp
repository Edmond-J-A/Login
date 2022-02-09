#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    clientSocket=new QTcpSocket();
    clientSocket->connectToHost("localhost",23334);//1.15.140.139
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginPushB_clicked()
{
    if(!clientSocket->waitForConnected(30000))
    {
        QMessageBox::information(this, "Error", "连接服务端失败,请检查网络！");
        return;
    }
    QString account = ui->account_lineEdit->text();
    QString code = ui->code_lineEdit->text();
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(ClientRecvData()));
    QString sendMsg = "login "+account+" "+code+"\n";
    char sendMsgChar[1024] = {0};
    strcpy_s(sendMsgChar, sendMsg.toStdString().c_str());
    int sendRe = clientSocket->write(sendMsgChar, strlen(sendMsgChar));
    if(sendRe == -1)
    {
         QMessageBox::information(this, "Error", "连接失败，请检查网络！");
         return;
    }
}

void Login::on_registerPushB_clicked()
{
    QString URL = "www.example.com";
    QDesktopServices::openUrl(QUrl(URL.toLatin1()));
}

void Login::ClientRecvData()
{
    char recvMsg[1024] = {0};
    int recvRe = clientSocket->read(recvMsg, 1024);
    if(recvRe == -1)
    {
       return;
    }
    QString result = recvMsg;
    result.replace(QRegExp("\n$"), "");
    if(result == "OK")
    {
        QMessageBox::information(this, "Login", "成功！");
        //获取用户信息

    }
    else
    {
        QMessageBox::information(this, "Error", "密码错误！");
    }
}
