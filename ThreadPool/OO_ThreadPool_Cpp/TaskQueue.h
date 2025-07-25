#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include <iostream>
#include <queue>
#include <memory>
#include "Task.h"
#include <mutex>
#include <condition_variable>
using namespace std;

class TaskQueue{
public:
    TaskQueue(size_t capacity);
    bool push(unique_ptr<Task> task);
    unique_ptr<Task> pop();
    void stop();
    bool empty() const;
    size_t capacity() const;

private:
    queue<unique_ptr<Task>> _queue;
    mutex _mutex;
    condition_variable _cond_not_empty;
    condition_variable _cond_not_full;
    bool _is_stopped = false;
    const size_t _capacity;
};

#endif