#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;

int total_sum;

void factorial(int num){

    // Calculate the factorial
    int fact = 1;
    for(int i = num; i > 0; i++){
        fact *= i;
    }

    // wait
    sem_wait(&mutex);

    // add fact to the total sum
    total_sum += fact;

    // Print the factorial
    printf("Calculated factorial for %d: %d\n", num, fact);

    // signal
    sem_post(&mutex);

}

int main(void){

    // initialize file pointer and open numbers.txt
    FILE *fp;
    fp = fopen("numbers.txt", "w");

    // Prompt user for 5 numbers and print to the file
    printf("Please enter 5 numbers:\n");
    int num;
    for (int i = 0; i < 5; i++){
        scanf("%d", &num);
        fprintf(fp, "%d\n", num);
    }

    // close numbers.txt
    fclose(fp);
    
    int pid = fork();

    printf("%d\n", pid);
    
    if(pid == 0){ // child process

        printf("working");
        
        // open numbers.txt and read
        fp = fopen("numbers.txt", "r");
        int i = 0;
        int nums[5];
        while (fscanf(fp, "%d\n", &num))
        {
            // add the scanned number into nums
            nums[i] = num;
            i++;
        }

        // close the file
        fclose(fp);

        // initialize semaphore
        sem_init(&mutex, 0, 1);

        pthread_t tid;

        // Make 5 threads
        for (int i = 0; i < 5; i++){
            pthread_create(&tid, NULL,(void *) factorial, &nums[i]);
            printf("working");
        }
        pthread_join(tid, NULL);
        sem_destroy(&mutex);

        // open and write to sum.txt
        fp = fopen("sum.txt", "w");
        fprintf(fp, "%d", total_sum);
        fclose(fp);

        
    } else{ //parent process

        // wait for child to finish
        wait(NULL);

        // open sum .txt and read
        fp = fopen("sum.txt", "r");
        int total;
        fscanf(fp, "%d", &total);

        // close the file
        fclose(fp);

        // print the total sum
        printf("The total sum is %d\n", total);
    }
    
    return 0;
} 