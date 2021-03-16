#include <stdlib.h>
#include <stdio.h>

#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

int main(){
        
    pid_t id1 = fork();
    pid_t id2 = fork();
    
    //parent process
    if (id1> 0 && id2 > 0){
            wait(NULL);
            wait(NULL);
            printf("Parent Process\n");
    }else if(id1 == 0 && id2 >0){
            sleep(2);
            wait(NULL);
            printf("1st Child Process\n");
    }else if(id1>0 && id2 == 0){
            sleep(1);
            printf("2nd Child Process\n");
    }else{  
            printf("Grand Child Process\n");
    }       
    return 0;
}     
