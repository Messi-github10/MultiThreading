#include "MyTask.hpp"
#include <stdio.h>
#include <unistd.h>

MyTask::MyTask(){
    srand(time(nullptr));
}

void MyTask::process(){
    int number = rand() % 100;
    printf("MyTask number is [%d].\n", number);
    sleep(1);
}