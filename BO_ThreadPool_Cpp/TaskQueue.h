#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include <iostream>
#include <queue>
#include <mutex>
#include <memory>
#include <functional>
#include <condition_variable>
using namespace std;

// 定义任务结构体
struct SafeTask{
    // 数据成员
    function<void()> func;  // 无参的统一执行接口

    // 构造函数
    template<typename Func, typename... Args>
    SafeTask(Func&& callback, unique_ptr<tuple<Args...>> args){
        // 将参数绑定到Lambda中
        auto shared_args = std::make_shared<tuple<Args...>>(move(*args));
        func = [callback = std::forward<Func>(callback), shared_args]()
        {
            std::apply(callback, *shared_args);
        };
    }

    void execute(){
        func();
    }
};

// 任务队列
class TaskQueue{
public:
    TaskQueue(size_t capacity);
    bool push(unique_ptr<SafeTask> task);
    unique_ptr<SafeTask> pop();
    void stop();
    bool empty() const;
    size_t capacity() const;

private:
    queue<unique_ptr<SafeTask>> _queue;
    mutex _mutex;
    condition_variable _cond_not_empty;
    condition_variable _cond_not_full;
    bool _is_stopped = false;
    const size_t _capacity;
};

#endif