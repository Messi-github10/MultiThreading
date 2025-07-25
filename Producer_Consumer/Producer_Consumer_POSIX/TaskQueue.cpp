#include "TaskQueue.hpp"

TaskQueue::TaskQueue(int size)
    : _que(), _queSize(size), _mutex(), _notFull(), _notEmpty()
{
}

bool TaskQueue::empty() const
{
    return _que.empty();
}

bool TaskQueue::full() const
{
    return _que.size() == _queSize;
}

void TaskQueue::push(int value)
{
    SmartMutex smart_lock(_mutex);
    while (full())
    {
        _notFull.wait(_mutex);
    }
    _que.push(value);
    _notEmpty.notify_one();
}

int TaskQueue::pop()
{
    SmartMutex smart_lock(_mutex);
    while(empty())
    {
        _notEmpty.wait(_mutex);
    }
    int result = _que.front();
    _que.pop();
    _notFull.notify_one();
    return result;
}