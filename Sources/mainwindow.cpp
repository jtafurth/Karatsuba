#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <about.h>
#include <kthread.h>
#include <stdio.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->imageFrame->setStyleSheet("background-image: url(E:/Entrevista/pattern2.jpg);");
    KM = new KThread(this);
    connect(KM,SIGNAL(sendRes(uint)),this,SLOT(receiveTest(uint)));
    connect(this,SIGNAL(textChanged()),this,SLOT(callKarutsaba()));
    connect(KM,SIGNAL(sendString(QString)),this,SLOT(paintConsole(QString)));
    addSign= false;
    clearCounter=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_num1Edit_textChanged(const QString &arg1)
{
    if(!ui->num2Edit->text().isEmpty()){
        emit textChanged();
    }
}


void MainWindow::on_num2Edit_textChanged(const QString &arg1)
{
    if(!ui->num1Edit->text().isEmpty()){
        emit textChanged();
    }
}

void MainWindow::callKarutsaba(){

    if(ui->num1Edit->text().startsWith("-")==true && ui->num2Edit->text().startsWith("-")==true){
        addSign = false;

    }
    else if(ui->num1Edit->text().startsWith("-")==true && ui->num2Edit->text().startsWith("-")==false){
        addSign = true;
    }
    else if(ui->num1Edit->text().startsWith("-")==false && ui->num2Edit->text().startsWith("-")==true){
        addSign = true;
    }
    else addSign = false;


    num1 = ui->num1Edit->text().remove("-");
    num2 = ui->num2Edit->text().remove("-");
    KM->num1 = num1.toUInt(&ok,10);
    KM->num2 = num2.toUInt(&ok,10);

    toConsole.append("Get numbers (true/false): ");
    toConsole.append(QString::number(ok));

    ui->consoleOutput->appendPlainText(toConsole);

    toConsole.clear();

    if(ok==true){
        KM->run();
    }
}

void MainWindow::receiveTest(uint res){
    num1 = QString::number(res,10);
    if(addSign==true){
        num1.insert(0,"-");
    }
    ui->resEdit->setText(num1);
}

void MainWindow::paintConsole(QString toConsole){
    ui->consoleOutput->appendPlainText(toConsole);
    clearCounter++;
    if(clearCounter==1000){
        ui->consoleOutput->clear();
        clearCounter=0;
    }
}

void MainWindow::on_actionAbout_triggered()
{
    About About1;
    About1.exec();
}
