#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
 
 
sem_t semaphore;
int mov_sum[5] = {0,0,0,0,0};
 
int main(){
    printf("please enter 5 numbers:\n");
    int num1, num2, num3, num4, num5;
    scanf("%d", &num1);
    scanf("%d", &num2);
    scanf("%d", &num3);
    scanf("%d", &num4);
    scanf("%d", &num5);

    mov_sum[0] = num1;
    mov_sum[1] = num2;
    mov_sum[2] = num3;
    mov_sum[3] = num4;
    mov_sum[4] = num5;

    //initializing threads
    pthread_t id[5];
    pthread_create(id[0], NULL, Calculate, (void*) num1);
    pthread_create(id[1], NULL, Calculate, (void*) num2);
    pthread_create(id[2], NULL, Calculate, (void*) num3);
    pthread_create(id[3], NULL, Calculate, (void*) num4);
    pthread_create(id[4], NULL, Calculate, (void*) num5);
    
    //joining threads
    thrd_join(id[0], NULL);
    thrd_join(id[1], NULL);
    thrd_join(id[2], NULL);
    thrd_join(id[3], NULL);
    thrd_join(id[4], NULL);

    printf("Moving Sums:\n");
    for(int i=0; i<5;i++){
            printf("%d \n", mov_sum[i]);
    }
}
 
    	int factorial(int num){
            	if(num >= 1){
            	    return num * factorial(num-1);
            	}else{
            	    return 1;
        	    }
    	}
    	void Calculate(int index){

            //initialize semaphore
            sem_init(&semaphore, 0, 1);


            int fact = fatorial(index);
            sem_wait(&semaphore);

            if(index -1>=0){
                if(mov_sum[index -1] >0){
                    mov_sum[index] = mov_sum[index-1] + fact;
                }
            sem_destroy(&semaphore);
 
    	}
}
