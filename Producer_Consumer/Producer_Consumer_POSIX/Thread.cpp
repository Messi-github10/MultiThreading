#include "Thread.hpp"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Thread::Thread()
    : _pthread_id(0), _isRunning(false)
{
}

void Thread::start()
{
    if (!_isRunning)
    {
        int ret = pthread_create(&_pthread_id,
                                 NULL,
                                 start_routine,
                                 this);

        if (ret != 0)
        {
            fprintf(stderr, "%s", strerror(ret));
            exit(EXIT_FAILURE);
        }
        _isRunning = true;
    }
}

void *Thread::start_routine(void *arg)
{
    // 形成多态
    Thread *pthread = static_cast<Thread *>(arg);
    if(pthread){
        pthread->run();
    }
    return NULL;
}

void Thread::join()
{
    if (_isRunning)
    {
        pthread_join(_pthread_id, NULL);
        _isRunning = false;
    }
}