#include "RealTask.hpp"
#include "Threadpool.hpp"
#include <iostream>
#include <functional>
using namespace std;

int main(){

    Threadpool threadpool(4, 10);
    threadpool.startThreadPool();

    int count = 20;
    while(count--){
        threadpool.addTask(bind(&RealTask::process, RealTask()));
        printf("Main Thread count is [%d].\n", count);
    }

    threadpool.stopThreadPool();
    printf("Main Thread is exiting.\n");

    return 0;
}