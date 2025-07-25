#include "WorkerThread.hpp"

void WorkerThread::run(){
    _threadpool.doTask();
}