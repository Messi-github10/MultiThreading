#include "Producer.hpp"

Producer::Producer(TaskQueue &taskque)
:_taskque(taskque)
{
    srand(time(nullptr));
}

void Producer::run(){
    int count = 20;
    while(count--){
        int number = rand() % 100;
        _taskque.push(number);
        printf("Producer produce [%d]\n", number);
        sleep(3);
    }
}