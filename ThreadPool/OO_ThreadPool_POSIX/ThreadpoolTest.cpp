#include "ThreadPool.hpp"
#include "MyTask.hpp"
#include <iostream>
#include <memory>
using namespace std;

void test(){
    // 创建线程池（4个线程，任务队列长度为10）
    Threadpool threadpool(4, 10);

    // 开启线程池
    threadpool.startThreadPool();

    // 给线程池添加任务
    unique_ptr<MyTask> ptask(new MyTask);
    int count = 20;
    while(count--){
        threadpool.addTask(ptask.get());
        printf("Main Thread count [%d].\n", count);
    }

    // 关闭线程池
    threadpool.stopThreadPool();
    printf("Main Thread is exiting.\n");
}

int main(){
    test();
    return 0;
}