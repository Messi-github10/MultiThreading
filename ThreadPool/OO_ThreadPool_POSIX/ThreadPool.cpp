#include "ThreadPool.hpp"
#include "WorkerThread.hpp"
#include <unistd.h>

Threadpool::Threadpool(int threadNum, int queSize)
:_threads()
,_threadNum(threadNum)
,_taskque(queSize)
,_queSize(queSize)
,_isExit(false)
{
    _threads.reserve(_threadNum);
}

void Threadpool::startThreadPool(){
    // 创建线程
    for (int i = 0; i < _threadNum; i++){
        unique_ptr<Thread> pTh(new WorkerThread(*this));
        _threads.push_back(std::move(pTh));
    }

    // 让每一个线程运行起来
    for(auto & elem : _threads){
        elem->startThread();
    }
}

void Threadpool::stopThreadPool(){
    // 等待任务队列当中的任务执行完
    while(!_taskque.empty()){
        sleep(1);
    }

    _isExit = true;
    _taskque.wakeup_all_thread();

    // 回收每个线程
    for(auto & elem : _threads){
        elem->joinThread();
    }
}

void Threadpool::addTask(Task *ptask){
    if(ptask != nullptr){
        _taskque.push(ptask);
    }
}

void Threadpool::doTask(){
    while(!_isExit){
        Task* ptask = _taskque.pop();
        if(ptask != nullptr){
            ptask->process();   // 触发多态
        }
    }
}