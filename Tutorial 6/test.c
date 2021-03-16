#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int testint;

void printtest(){
    testint = 1;
    printf("%d",testint);
}

int main()
{
    testint = 0;
    printf("%d",testint);
    printtest();
    printf("%d",testint);

    return 0;
}
