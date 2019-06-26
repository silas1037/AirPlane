#include <QThread>
#ifndef MYTHREAD_H
#define MYTHREAD_H


class MyThread : public QThread
{
public:
    MyThread();
    ~MyThread();
    void run();
};

#endif // MYTHREAD_H
