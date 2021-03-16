#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define STUDENTS 10

//Make a barrier
pthread_barrier_t barrier;

// global total grade, before and after grades array
float total_grade;

// Make a lock
pthread_mutex_t lock;

void read_grades(float *arr){
    // Read the file
    FILE *fp = fopen("grades.txt", "r");

    float num;
    int i = 0;
    int r = fscanf(fp, "%f\n", &num);

    // Add each grade to the array
    while (r != EOF){
        arr[i] = num;
        i++;
    }

    // close the file
    fclose(fp);

    // call barrier wait
    pthread_barrier_wait(&barrier);
}

void save_bellcurve(float *grade){
    // mutex lock
    pthread_mutex_lock(&lock);

    // Add to total grade
    total_grade += *grade;

    // write grade to file
    FILE *fp = fopen("bellcurve.txt", "w");
    fprintf(fp, "%f\n", grade);

    // mutex unlock
    pthread_mutex_unlock(&lock);

    // call barrier wait
    pthread_barrier_wait(&barrier);
    
}

int main(){

    // Make an array of grades
    float grades[STUDENTS];

    pthread_t ptid;

    // initialize barrier
    pthread_barrier_init(&barrier, NULL, 1);

    // Call read thread
    pthread_create(&ptid, NULL, (void *) read_grades, (float *) grades);

    // initialize another barrier
    pthread_barrier_init(&barrier, NULL, STUDENTS);

    // Make 10 threads to call bellcurve
    for (int i = 0; i < STUDENTS; i++)
    {
        pthread_create(&ptid, NULL, (void *) save_bellcurve, &grades[i]);
    }
    
    // call pthread join
    pthread_join(&ptid, NULL);

}