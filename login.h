#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include<QUrl>
#include <qdesktopservices.h>
#include<QTcpSocket>
#include<QDebug>
#include<QMessageBox>
namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_loginPushB_clicked();

    void on_registerPushB_clicked();

    void ClientRecvData();
private:
    Ui::Login *ui;
    QTcpSocket * clientSocket;
};

#endif // LOGIN_H
