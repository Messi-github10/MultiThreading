#ifndef TASK_H
#define TASK_H

class Task{
public:
    Task() = default;
    virtual ~Task() = default;
    virtual void execute() = 0;
};

#endif