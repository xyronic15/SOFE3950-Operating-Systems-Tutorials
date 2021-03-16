#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_STUDENTS 2

// Struct for student
struct Student{
    char name[256];
    int student_id;
    float grade;
};

void bellcurved(struct Student *student){

    // Mulitply grade by 1.5
    (*student).grade *= 1.5;
    
    printf("%s\t%d\t%.2f\n", (*student).name, (*student).student_id, (*student).grade);
}

int main()
{
    // make an array of students
    struct Student students[NUM_STUDENTS];

    // Prompt user for names, ids and grades
    for (int i = 0; i < NUM_STUDENTS; i++)
    {
        printf("Enter student name: ");
        scanf("%s", students[i].name);
        printf("Enter student id: ");
        scanf("%d", &students[i].student_id);
        printf("Enter student grade: ");
        scanf("%f", &students[i].grade);
    }

    printf("\n");

    printf("Name\tID\tMarks\n");

    pthread_t tid;

    // Create 5 threads and run bellcurved
    for (int i = 0; i < NUM_STUDENTS; i++)
    {
        pthread_create(&tid, NULL, (void *) bellcurved, &students[i]);
    }

    // Exit the threads
    pthread_exit(NULL);
    

    return 0;
}
