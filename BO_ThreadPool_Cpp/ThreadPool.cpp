#include "ThreadPool.h"
#include <thread>
#include <chrono>

ThreadPool::ThreadPool(size_t threadNum, size_t capacity)
:_threadNum(threadNum)
,_capacity(capacity)
,_taskQueue(capacity)
,_isExit(false)
{
}

ThreadPool::~ThreadPool(){
    if(!_isExit){
        stop();
    }
}

void ThreadPool::start(){
    for (size_t i = 0; i < _threadNum; i++){
        _threads.emplace_back(&ThreadPool::execTask, this);
    }
}

void ThreadPool::stop(){
    while(!_taskQueue.empty()){
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    _isExit = true;
    _taskQueue.stop();
    for(auto & thread : _threads){
        if(thread.joinable()){
            thread.join();
        }
    }
}

bool ThreadPool::addTask(unique_ptr<SafeTask> task){
    return _taskQueue.push(std::move(task));
}

unique_ptr<SafeTask> ThreadPool::getTask(){
    return _taskQueue.pop();
}

void ThreadPool::execTask(){
    while(!_isExit){
        auto task = getTask();
        if(!task){
            break;
        }
        task->execute();
    }
}

