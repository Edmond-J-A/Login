#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->hide();
    loginUI=new Login;
    loginUI->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
