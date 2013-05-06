#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <kthread.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    KThread *KM;

signals:

    void textChanged();

public slots:

    void callKarutsaba();
    void receiveTest(uint res);

private slots:

    void on_num1Edit_textChanged(const QString &arg1);
    void on_num2Edit_textChanged(const QString &arg1);
    void paintConsole(QString);

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    QString toConsole;
    QString num1;
    QString num2;
    bool ok;
    bool addSign;
    int clearCounter;
};

#endif // MAINWINDOW_H
