#ifndef WORKERTHREAD_HPP
#define WORKERTHREAD_HPP

#include "Thread.hpp"
#include "ThreadPool.hpp"

class WorkerThread : public Thread{
public:
    WorkerThread(Threadpool &threadpool)
    :_threadpool(threadpool)
    {}

    ~WorkerThread() = default;

private:
    void run() override;

private:
    Threadpool &_threadpool;
};

#endif