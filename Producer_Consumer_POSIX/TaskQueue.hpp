#ifndef TASKQUEUE_HPP
#define TASKQUEUE_HPP

#include "Condition_va.hpp"
#include "MutexLock.hpp"
#include "SmartMutex.hpp"
#include <queue>
using std::queue;

class TaskQueue
{
public:
    TaskQueue(int);
    bool empty() const;
    bool full() const;
    void push(int);
    int pop();

private:
    queue<int> _que;
    int _queSize;
    MutexLock _mutex;
    Condition_va _notFull;  // 满则阻塞
    Condition_va _notEmpty; // 空则阻塞
};

#endif