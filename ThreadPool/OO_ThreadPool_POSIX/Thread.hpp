#ifndef THREAD_HPP
#define THREAD_HPP

#include "Noncopyable.hpp"
#include <pthread.h>

class Thread : public Noncopyable{
public:
    Thread();
    virtual ~Thread() = default;
    void startThread();
    void joinThread();

private:
    virtual void run() = 0;
    static void *start_routine(void *);

private:
    pthread_t _pthread_id;
    bool _isRunning;
};

#endif