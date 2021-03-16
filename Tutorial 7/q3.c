#define _POSIX_SOURCE
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){

    // Initialize pid
    pid_t pid;
    
    // Fork the processes
    pid = fork();
    if(pid < 0){
        printf("ERROR");
    } else if(pid == 0){
        // Run execl in child process
        execl("process", NULL);
    } else{
        // sleep then kill
        sleep(5);
        kill(pid, SIGINT);
    }
}