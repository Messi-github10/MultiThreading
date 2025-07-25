#include "Consumer.hpp"

void Consumer::run(){
    int count = 20;
    while(count--){
        int number = _taskque.pop();
        printf("Consumer spend [%d]\n", number);
    }
    sleep(1);
}