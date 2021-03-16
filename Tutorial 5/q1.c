#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void hello_world(){
    printf("hello world\n");
}

void goodbye(){
    printf("goodbye\n");
}

int main(void){
    pthread_t ptid;

    // Create the two threads
    pthread_create(&ptid, NULL, (void *) hello_world, NULL);
    pthread_create(&ptid, NULL, (void *) goodbye, NULL);

    pthread_exit(NULL);
    return 0;

}