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
    QString account = ui->account_lineEdit->text();
    if(account.size()==0)
    {
        QMessageBox::information(this, "Error", "请输入账号！");
        return;
    }
    QString code = ui->code_lineEdit->text();
    if(code.size()==0)
    {
        QMessageBox::information(this, "Error", "请输入密码！");
        return;
    }
    if(!clientSocket->waitForConnected(30000))
    {
        QMessageBox::information(this, "Error", "连接服务端失败,请检查网络！");
        return;
    }
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
    QByteArray result = clientSocket->readAll();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(result, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug()<<"Json文件解析错误。";
        return;
    }

    if (jsonDoc.isObject()) {
        qDebug()<<1;
        QJsonObject jsonObject = jsonDoc.object();
        Instruction get_instruction(jsonObject);
        if(get_instruction.CommandType()==USER)
        {
            QMessageBox::information(this, "Login", "成功！");
            // TODO:处理用户信息并返回给主窗口
        }
        else if(get_instruction.CommandType() == CODE_ERROR)
        {
            QMessageBox::information(this, "Error", "密码错误！");
        }
        else if(get_instruction.CommandType() == ACCOUNT_ERROR)
        {
            QMessageBox::information(this, "Error", "账号错误！");
        }
        else
        {
            QMessageBox::information(this, "Error", "未知错误！");
        }

    }
    else if (jsonDoc.isArray()) {
        QJsonArray jsonArray = jsonDoc.array();
        qDebug()<<jsonArray;
    }
    else {
        qDebug()<<"Json文件解析为空。";
        return;
    }

}
