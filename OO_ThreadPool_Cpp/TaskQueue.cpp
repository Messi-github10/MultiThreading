#include "Task.h"
#include "TaskQueue.h"

TaskQueue::TaskQueue(size_t capacity)
:_capacity(capacity)
{
}

bool TaskQueue::push(unique_ptr<Task> task){
    unique_lock<mutex> lock(_mutex);
    _cond_not_full.wait(lock, [this]{
        return ((_queue.size() < _capacity) || _is_stopped); 
    });

    if(_is_stopped){
        return false;
    }

    _queue.push(std::move(task));
    _cond_not_empty.notify_one();
    return true;
}

unique_ptr<Task> TaskQueue::pop(){
    unique_lock<mutex> lock(_mutex);
    _cond_not_empty.wait(lock, [this]{ 
        return (!_queue.empty() || _is_stopped); 
    });

    if(_is_stopped){
        return nullptr;
    }

    auto task = std::move(_queue.front());
    _queue.pop();
    _cond_not_full.notify_one();
    return task;
}

void TaskQueue::stop(){
    unique_lock<mutex> lock(_mutex);
    _is_stopped = true;
    _cond_not_empty.notify_all();
    _cond_not_full.notify_all();
}

size_t TaskQueue::capacity() const{
    return _capacity;
}

bool TaskQueue::empty() const{
    return _queue.empty();
}