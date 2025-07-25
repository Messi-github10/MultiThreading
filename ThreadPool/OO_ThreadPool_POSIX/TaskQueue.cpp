#include "TaskQueue.hpp"
#include "SmartMutexLock.hpp"

bool TaskQueue::empty() const{
    return _que.empty();
}

bool TaskQueue::full() const{
    return (_que.size() == _queSize);
}

void TaskQueue::push(ElemType elem){
    SmartMutexLock smartMutex(_mutex);
    while (full())
    {
        _notFull.wait();
    }
    _que.push(elem);
    _notEmpty.notify_one();
}

ElemType TaskQueue::pop(){
    SmartMutexLock smartMutex(_mutex);
    ElemType result = nullptr;
    while(empty() && !_isStop){
        _notEmpty.wait();
    }

    if(!_isStop){
        result = _que.front();
        _que.pop();
        _notFull.notify_one();
    }
    return result;
}

void TaskQueue::wakeup_all_thread(){
    _isStop = true;
    _notEmpty.notify_all();
}