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

// proc struct
typedef struct{
    char name[256];
    int priority;
    pid_t pid;
    int runtime;
} proc;

// queue struct
struct queue{
    proc process;
    struct queue *next;
};

void push(proc process);
proc *pop();
proc *delete_name(char *name);

struct queue *list = NULL;

int main(void){
    // Open file
    FILE *fp;
    fp = fopen("processes_q5.txt", "r");

    // Initialize vars
    proc temp_proc, *rem_proc;
    struct queue *temp;
    int status;
    pid_t pid;

    // Read through the processes file
    for (int i = 0; i < 10; i++){
        fscanf(fp, "%[^,], %d, %d\n", temp_proc.name, &temp_proc.priority, &temp_proc.runtime);
        temp_proc.pid = 0;
        // push it to the queue
        push(temp_proc);
    }

    // close the file
    fclose(fp);

    // Iterate and execute proc based on priority
    temp = list;
    while(temp != NULL){
        if(temp->process.priority == 0){
            pid = fork();
            if(pid < 0){
                return 1;
            } else if(pid == 0){
                // Execute process
                execl("process", NULL);
            } else{
                // Assign pid and remove from queue
                temp->process.pid = pid;
                sleep(temp->process.runtime);
                kill(pid, SIGINT);
                waitpid(pid, &status, 0);
                rem_proc = delete_name(temp->process.name);
                printf("Name: %s, Priority: %d, Pid: %d, Runtime: %d\n\n", rem_proc->name, rem_proc->priority, rem_proc->pid, rem_proc->runtime);
            }
        }
        temp = temp->next;
    }

    temp = list;
    while(temp != NULL){
        pid = fork();
        if(pid < 0){
                return 1;
        } else if(pid == 0){
            // Execute process
            execl("process", NULL);
        } else{
            // Assign pid and pop queue
            temp->process.pid = pid;
            sleep(temp->process.runtime);
            kill(pid, SIGINT);
            waitpid(pid, &status, 0);
            rem_proc = pop();
            printf("Name: %s, Priority: %d, Pid: %d, Runtime: %d\n\n", rem_proc->name, rem_proc->priority, rem_proc->pid, rem_proc->runtime);
        }
        temp = temp->next;
    }

}

// push function
void push(proc process){
    struct queue *new_node, *temp_node;
    new_node = (struct queue *) malloc(sizeof(struct queue));
    new_node->process = process;
    new_node->next = NULL;
    temp_node = list;

    if (list == NULL){
        list = (struct queue *) malloc(sizeof(struct queue));
        list->process = process;
        list->next = NULL;
    } else{
        while (temp_node->next != NULL){
            temp_node = temp_node->next;
        }
        temp_node->next = new_node;
    }
    
}

// pop function
proc *pop(){
    proc *popped;
    struct queue *next;

    if(list == NULL){
        return NULL;
    }

    next = list;
    popped = &list->process;
    list = next->next;
    return popped;
}

// delete_name function
proc *delete_name(char *name){
    proc *del;
    struct queue *temp, *prev;

    if(strcmp(list->process.name, name) == 0){
        return pop();
    }

    temp = list;
    while(temp != NULL){
        if(strcmp(temp->process.name, name) == 0){
            prev->next = temp->next;
            del = &temp->process;
            return del;
        }
        prev = temp;
        temp = temp->next;
    }
    return NULL;
}