#include "Condition_va.hpp"

void Conditon_va::wait(){
    pthread_cond_wait(&_cond, _mutex.getMutexLockPtr());
}

void Conditon_va::notify_one(){
    pthread_cond_signal(&_cond);
}

void Conditon_va::notify_all(){
    pthread_cond_broadcast(&_cond);
}