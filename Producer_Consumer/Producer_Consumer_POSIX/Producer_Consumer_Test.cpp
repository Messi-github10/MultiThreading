#include "TaskQueue.hpp"
#include "Consumer.hpp"
#include "Producer.hpp"
#include "Noncopyable.hpp"
#include <iostream>
#include <memory>
using namespace std;

void test()
{
    TaskQueue que(10);
    unique_ptr<Producer> producer(new Producer(que));
    unique_ptr<Consumer> consumer(new Consumer(que));
    producer->start();
    consumer->start();
    producer->join();
    consumer->join();
    printf("Main Thread is exiting.\n");
}

int main()
{
    test();
    return 0;
}
