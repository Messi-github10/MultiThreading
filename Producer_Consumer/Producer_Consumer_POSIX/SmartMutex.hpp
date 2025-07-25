#ifndef SMARTMUTEX_HPP
#define SMARTMUTEX_HPP

#include "MutexLock.hpp"

class SmartMutex
{
public:
    // 遵循RAII思想（资源获取即初始化）
    SmartMutex(MutexLock &mutex_lock)
    :_mutex_lock(mutex_lock)
    {
        _mutex_lock.lock();
    }

    ~SmartMutex(){
        _mutex_lock.unlock();
    }

private:
    MutexLock &_mutex_lock;
};

#endif