#ifndef MUTEXLOCK_HPP
#define MUTEXLOCK_HPP

#include "Noncopyable.hpp"
#include <pthread.h>

class MutexLock : public Noncopyable
{
public:
    MutexLock();
    ~MutexLock();
    void lock();
    void unlock();
    pthread_mutex_t *getMutexLockPtr();

private:
    pthread_mutex_t _mutex;
};

#endif