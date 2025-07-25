#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <iostream>
#include <vector>
#include <thread>
#include "TaskQueue.h"
#include "Task.h"
using namespace std;

class ThreadPool{
public:
    ThreadPool(size_t threadNum, size_t capacity);
    ~ThreadPool();
    void start();   // 线程池初始化
    void stop();

    bool addTask(unique_ptr<Task> task);
    unique_ptr<Task> getTask();

private:

    void execTask();    // 线程执行函数

    size_t _threadNum;  // 线程总数量
    vector<thread> _threads;    // 线程池
    size_t _capacity;   // 任务队列容量
    TaskQueue _taskQueue;   // 任务队列
    bool _isExit;   // 线程池退出标志
};

#endif