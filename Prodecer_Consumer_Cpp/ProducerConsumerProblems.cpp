#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <chrono>
#include <condition_variable>
using namespace std;

class TaskQueue{
public:
    TaskQueue(size_t capacity)
    :_capacity(capacity)
    {}

    ~TaskQueue(){}

    void push(const int &value){
        unique_lock<mutex> lock(_mutex);
        if(full()){
            _not_full.wait(lock);
        }
        _queue.push(value);
        cout << "push number is [" << value << "]" << endl;
        _not_empty.notify_one();
    }

    int pop(){
        unique_lock<mutex> lock(_mutex);
        if(empty()){
            _not_empty.wait(lock);
        }
        int result = _queue.front();
        cout << "pop number is [" << result << "]" << endl;
        _queue.pop();
        _not_full.notify_one();
        return result;
    }

    bool empty(){
        return _queue.empty();
    }

    bool full(){
        return _queue.size() == _capacity;
    }

private:
    queue<int> _queue;
    size_t _capacity;
    mutex _mutex;
    condition_variable _not_full;
    condition_variable _not_empty;
};

class Producer{
public:
    void produce(TaskQueue &taskQueue){
        srand(clock());
        int count = 20;
        while(count--){
            int number = rand() % 100;
            taskQueue.push(number);
        }
    }
};

class Consumer{
public:
    void consume(TaskQueue &taskQueue){
        int count = 20;
        while(count--){
            int number = taskQueue.pop();
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
};

void test(){
    Producer producer;
    Consumer consumer;
    TaskQueue taskQueue(5);

    thread producer_thread(&Producer::produce, producer, ref(taskQueue));
    thread consumer_thread(&Consumer::consume, consumer,ref(taskQueue));
    producer_thread.join();
    consumer_thread.join();
}

int main(){
    test();
    return 0;
}