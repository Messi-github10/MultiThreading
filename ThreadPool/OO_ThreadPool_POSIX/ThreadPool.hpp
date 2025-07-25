#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include "Thread.hpp"
#include "TaskQueue.hpp"
#include <vector>
#include <memory>
using namespace std;

class Task;
class Threadpool
{
    friend class WorkerThread;

public:
    Threadpool(int, int);
    void startThreadPool();
    void stopThreadPool();
    void addTask(Task *);
    void doTask();

private:
    vector<unique_ptr<Thread>> _threads;    // 线程池
    int _threadNum; // 线程数量
    TaskQueue _taskque; // 任务队列
    int _queSize;   // 队列长度
    bool _isExit;   // 退出线程池
};

#endif