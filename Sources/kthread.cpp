#include "kthread.h"
#include <stdio.h>
#include <complex>

using namespace std;

KThread::KThread(QObject *parent) :
    QThread(parent)
{
}

void KThread::run(){

    toConsole.append("Thread started. Operands: ");
    toConsole.append(QString::number(num1));
    toConsole.append(" / ");
    toConsole.append(QString::number(num2));
    emit sendString(toConsole);
    toConsole.clear();

    result = Karatsuba(num1,num2);
    emit sendRes(result);
    exit();
}

uint KThread::Karatsuba(uint num1, uint num2){
    if( (num1 <= 15) | (num2 <= 15) ){

        uint res;
        res = multiply(num1,num2);

        toConsole.append("Direct multiplication computed between: ");
        toConsole.append(QString::number(num1));
        toConsole.append(" / ");
        toConsole.append(QString::number(num2));
        emit sendString(toConsole);
        toConsole.clear();
        toConsole.append("Result: ");
        toConsole.append(QString::number(res));
        emit sendString(toConsole);
        toConsole.clear();

        return res;
    }
    else{

        toConsole.append("Karatsuba Iteration started between: ");
        toConsole.append(QString::number(num1));
        toConsole.append(" / ");
        toConsole.append(QString::number(num2));
        emit sendString(toConsole);
        toConsole.clear();

        uint high1;
        uint high2;
        uint low1;
        uint low2;
        int z0;
        uint z1;
        uint z2;
        uint c1;
        uint c2;
        int c3;
        uint m1;
        uint m2;
        int m3;
        uint n;
        uint res;
        uint digits1=0;
        uint digits2=0;
        uint temp;

        temp = num1;
        vector<int> vec1;
        while(temp!=1){
                vec1.push_back(div(temp,2).rem);
                temp = div(temp,2).quot;
                digits1++;
            }
        vec1.push_back(1);
        digits1++;
        temp = num2;
        while(temp!=1){
                temp = div(temp,2).quot;
                digits2++;
            }
        digits2++;

        if(digits1%2==1){
            digits1++;
        }
        if(digits2%2==1){
            digits2++;
        }
        if(digits1!=digits2){
            if(digits1<digits2){
                while(digits1<digits2){
                    digits1++;
                }
            }
            else if(digits2<digits1){
                while(digits2<digits1){
                    digits2++;
                }
            }
        }

        toConsole.append("Detected odd number or diferent bit sizes, fixed.");
        emit sendString(toConsole);
        toConsole.clear();

        n = digits1;

        toConsole.append("Digits (n): ");
        toConsole.append(QString::number(n));
        emit sendString(toConsole);
        toConsole.clear();

        uint lowMask1 = pow(2,digits1/2);
        uint lowMask2 = pow(2,digits2/2);

        lowMask1 = lowMask1-1;
        lowMask2 = lowMask2-1;

        low1 = (num1 & lowMask1);
        num1 >>= digits1/2;
        high1 = (num1 & lowMask1);
        low2 = (num2 & lowMask2);
        num2 >>= digits2/2;
        high2 = (num2 & lowMask2);

        toConsole.append("Lower half of numbers: ");
        toConsole.append(QString::number(low1));
        toConsole.append(" / ");
        toConsole.append(QString::number(low2));
        emit sendString(toConsole);
        toConsole.clear();
        toConsole.append("Higher half of numbers: ");
        toConsole.append(QString::number(high1));
        toConsole.append(" / ");
        toConsole.append(QString::number(high2));
        emit sendString(toConsole);
        toConsole.clear();

        z0 = Karatsuba(low1,low2);
        z1 = Karatsuba(low1+high1,low2+high2);
        z2 = Karatsuba(high1,high2);

        c1 = pow(2,n)-pow(2,n/2);
        c2 = pow(2,n/2);
        c3 = 1-pow(2,n/2);

        m1 = multiply(c1,z2);
        m2 = multiply(c2,z1);
        m3 = (c3)*z0;

        res = m1+m2+m3;

        toConsole.append("Karatsuba computation(c1*z1+c2*z2+c3*z3): ");
        toConsole.append(QString::number(m1));
        toConsole.append(" / ");
        toConsole.append(QString::number(m2));
        toConsole.append(" / ");
        toConsole.append(QString::number((int)m3));
        emit sendString(toConsole);
        toConsole.clear();

        toConsole.append("Result: ");
        toConsole.append(QString::number(res));
        emit sendString(toConsole);
        toConsole.clear();

        return res;
    }
    return 0;
}

//Thanks to user aStranger of Stack Overflow for this method.
uint KThread::multiply(unsigned int left, unsigned int right)
{
    unsigned long long result = 0;

    unsigned int R = right;
    unsigned int M = left;

    while (R > 0)
    {
        if (R & 1)
        {
            result += M;
        }
        R >>= 1;
        M <<= 1;
    }

//-- if you want to check for multiplication overflow: --
    if ((result >> 32) != 0)
    {
        return -1;
    }

    return (uint)result;
}
