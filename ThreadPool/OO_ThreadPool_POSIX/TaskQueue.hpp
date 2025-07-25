#ifndef TASKQUEUE_HPP
#define TASKQUEUE_HPP

#include "MutexLock.hpp"
#include "Condition_va.hpp"
#include "Task.hpp"
#include <queue>
using namespace std;

using ElemType = Task *;
class TaskQueue
{
public:
    TaskQueue(int size)
    :_queSize(size)
    ,_isStop(false)
    ,_notFull(_mutex)
    ,_notEmpty(_mutex)
    {}

    bool empty() const;
    bool full() const;
    void push(ElemType);
    ElemType pop();
    void wakeup_all_thread();

private:
    queue<ElemType> _que;
    int _queSize;
    bool _isStop;
    MutexLock _mutex;
    Conditon_va _notFull;
    Conditon_va _notEmpty;
};

#endif