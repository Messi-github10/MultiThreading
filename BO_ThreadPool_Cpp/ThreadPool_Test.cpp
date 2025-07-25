#include "TaskQueue.h"
#include "ThreadPool.h"
#include <iostream>
#include <chrono>
#include <mutex>
using namespace std;

mutex cout_mutex;

void printMessage(const string& message){
    lock_guard<mutex> lock(cout_mutex);
    cout << "Thread" << this_thread::get_id() << ":" << message << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
}   

int Mymultiply(int a, int b){
    int result = a * b;
    lock_guard<mutex> lock(cout_mutex);
    cout << "Thread" << this_thread::get_id() << ":" 
        << a << " * " << b << " = " << result << endl;
    return result;
}

int main(){
    // 2个工作线程，任务队列容量为10
    ThreadPool pool(2, 10);

    // 启动线程池
    pool.start();

    // 添加打印任务
    for (int i = 0; i < 5; i++){
        auto task = make_unique<SafeTask>(
            [i](const string &msg)
            {
                printMessage(msg + to_string(i));
            },
            make_unique<tuple<string>>("Hello Linus")
        );
        pool.addTask(std::move(task));
    }

    // 添加计算任务
    for(int i = 1; i < 3; i++){
        auto task = make_unique<SafeTask>(
            [](int x, int y)
            {
                Mymultiply(x, y);
            },
        make_unique<tuple<int, int>>(i, i+1)
        );
        pool.addTask(std::move(task));
    }

    this_thread::sleep_for(chrono::seconds(1));

    pool.stop();

    lock_guard<mutex> lock(cout_mutex);
    cout << "All tasks completed." << endl;

    return 0;
}

