#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct{
    	char name[256];
    	int priority;
    	int pid;
    	int runtime;
}proc;
 
struct queue{
	proc process;
	struct queue* next;
};

struct queue* list;

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

void printlist(){
    if(list == NULL){
        printf("Queue is empty\n");
    }else{
        struct queue* curr = list;
        while(curr->next != NULL){
            printf("Name: %s, Priority: %d, Pid: %d, Runtime: %d\n\n", curr->process.name, curr->process.priority, curr->process.pid, curr->process.runtime);
            curr = curr->next;
            printf("\n");
        }
        printf("Name: %s, Priority: %d, Pid: %d, Runtime: %d\n\n", curr->process.name, curr->process.priority, curr->process.pid, curr->process.runtime);
        printf("\n");

    }
    
}

int main() {
	list = NULL;
	FILE * filePointer;
    proc temp_proc;
	filePointer = fopen("processes.txt", "r");
	if ( filePointer == NULL ){
    	printf( "process.txt failed to open" );
    	return 0;
	}
	
    for (int i = 0; i < 10; i++){
        fscanf(filePointer, "%[^,], %d, %d, %d\n", temp_proc.name, &temp_proc.priority, &temp_proc.pid, &temp_proc.runtime);
        temp_proc.pid = 0;
        // push it to the queue
        push(temp_proc);
    }
    printlist();
    return 0;
}
