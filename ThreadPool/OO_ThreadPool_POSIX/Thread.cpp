#include "Thread.hpp"
#include <stdio.h>
#include <string.h>

Thread::Thread()
:_pthread_id(0)
,_isRunning(false)
{}

void Thread::startThread(){
    if(!_isRunning){
        int ret = pthread_create(&_pthread_id, nullptr, start_routine, this);

        if(ret != 0){
            fprintf(stderr, "%s", strerror(ret));
            return;
        }

        _isRunning = true;
    }
}

void Thread::joinThread(){
    if(_isRunning){
        pthread_join(_pthread_id, nullptr);
    }
    _isRunning = false;
}

void *Thread::start_routine(void *arg){
    // Thread类是抽象类无法实例化，所以本质上这个函数是为了给WorkerThread用的
    // 这就形成了基类指针指向派生类对象
    Thread *pth = static_cast<Thread *>(arg);
    if(pth != nullptr){
        pth->run(); // 触发多态
    }
    return nullptr;
}