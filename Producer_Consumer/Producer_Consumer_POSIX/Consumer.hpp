#ifndef CONSUMER_HPP
#define CONSUMER_HPP

#include "Thread.hpp"
#include "TaskQueue.hpp"
#include <unistd.h>
#include <stdio.h>

class Consumer : public Thread
{
public:
    Consumer(TaskQueue &taskque)
        : _taskque(taskque)
    {
    }
    void run() override;

private:
    TaskQueue &_taskque;
};

#endif