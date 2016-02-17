#ifndef MYTHREAD_H
#define MYTHREAD_H

class MyThread : public QThread
{
public:
    MyThread();
    void stop();

protected:
    void run();
};

#endif // MYTHREAD_H
