#include "mythread.h"
#include <qprocess>
MyThread::MyThread()
{

}

MyThread::~MyThread()
{

}

void MyThread::run()
{
    QProcess::execute("notepad.exe conf.ini");
}
