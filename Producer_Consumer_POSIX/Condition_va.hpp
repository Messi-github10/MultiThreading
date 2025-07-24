#ifndef CONDITION_VA_HPP
#define CONDITION_VA_HPP

#include "Noncopyable.hpp"
#include <pthread.h>

class MutexLock;
class Condition_va : public Noncopyable
{
public:
    Condition_va();
    ~Condition_va();
    void wait(MutexLock &);
    void notify_one();
    void notify_all();

private:
    pthread_cond_t _cond;
};

#endif