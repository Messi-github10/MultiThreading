#include "RealTask.hpp"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

RealTask::RealTask(){
    srand(time(nullptr));
}

void RealTask::process(){
    int number = rand() % 100;
    printf("RealTask process number is [%d].\n", number);
    sleep(1);
}