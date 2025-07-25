#ifndef THREAD_HPP
#define THREAD_HPP

#include "Noncopyable.hpp"
#include <pthread.h>

class Thread : public Noncopyable
{
public:
    Thread();
    virtual ~Thread(){}

    void start();

    void join();

private:
    static void *start_routine(void *);
    virtual void run() = 0;

private:
    pthread_t _pthread_id;
    bool _isRunning;
};

#endif