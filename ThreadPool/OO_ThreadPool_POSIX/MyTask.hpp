#ifndef MYTASK_HPP
#define MYTASK_HPP

#include "Task.hpp"
#include <time.h>
#include <stdlib.h>

class MyTask : public Task{
public:
    MyTask();

    ~MyTask() = default;

    void process() override;
};

#endif