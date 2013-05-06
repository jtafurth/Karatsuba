#ifndef KTHREAD_H
#define KTHREAD_H

#include <QThread>
#include <stdio.h>
#include <vector>

using namespace std;

class KThread : public QThread
{
    Q_OBJECT
public:
    explicit KThread(QObject *parent = 0);
    void run();
    uint Karatsuba(uint,uint);
    uint multiply(uint,uint);

    uint num1;
    uint num2;

signals:

    void sendRes(uint);
    void sendString(QString);

private:
    uint result;
    QString toConsole;
};

#endif // KTHREAD_H
