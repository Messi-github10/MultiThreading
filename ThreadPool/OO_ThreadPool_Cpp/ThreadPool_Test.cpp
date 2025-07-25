#include "Task.h"
#include "TaskQueue.h"
#include "ThreadPool.h"
#include <string>
#include <chrono>
using namespace std;

mutex cout_mutex;

class PrintTask : public Task{
public:
    PrintTask(const string & message, const int & index)
    :_message(message)
    ,_index(index)
    {}

    void execute() override{
        lock_guard<mutex> lock(cout_mutex);
        cout << "Thread" << this_thread::get_id() << ":" 
             << _message << _index << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }

private:
    string _message;
    int _index;
};

class MultiplyTask : public Task{
public:
    MultiplyTask(int x, int y)
    :_x(x)
    ,_y(y)
    {}

    void execute() override{
        int result = _x * _y;
        lock_guard<mutex> lock(cout_mutex);
        cout << "Thread" << this_thread::get_id() << ":" 
             << _x << " * " << _y << " = " << result << endl;
    }

private:
    int _x;
    int _y;
};

int main(){
    ThreadPool pool(2, 10);
    pool.start();

    // 打印任务
    for(int i = 0; i < 5; i++){
        auto task = make_unique<PrintTask>("Hello Linus", i);
        pool.addTask(std::move(task));
    }

    // 计算任务
    for (int i = 1; i < 3; i++){
        auto task = make_unique<MultiplyTask>(i, i + 1);
        pool.addTask(std::move(task));
    }

    this_thread::sleep_for(chrono::seconds(1));
    pool.stop();

    lock_guard<mutex> lock(cout_mutex);
    cout << "All task completed." << endl;

    return 0;
}