#ifndef PRODUCER_HPP
#define PRODUCER_HPP

#include "Thread.hpp"
#include "TaskQueue.hpp"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

class Producer : public Thread
{
public:
    Producer(TaskQueue &taskque);
    void run() override;

private:
    TaskQueue &_taskque;
};

#endif