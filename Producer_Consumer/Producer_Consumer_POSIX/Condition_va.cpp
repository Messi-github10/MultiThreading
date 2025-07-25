#include "Condition_va.hpp"
#include "MutexLock.hpp"

Condition_va::Condition_va()
{
    pthread_cond_init(&_cond, NULL);
}
Condition_va::~Condition_va()
{
    pthread_cond_destroy(&_cond);
}

void Condition_va::wait(MutexLock &mutex)
{
    pthread_cond_wait(&_cond, mutex.getMutexLockPtr());
}

void Condition_va::notify_one()
{
    pthread_cond_signal(&_cond);
}

void Condition_va::notify_all()
{
    pthread_cond_broadcast(&_cond);
}
