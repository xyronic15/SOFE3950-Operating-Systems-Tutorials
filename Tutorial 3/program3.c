#include <stdio.h>
#include <stdlib.h>

struct Student{
           	int student_id;
           	int age;
           	int year;
};

void save_student(struct Student student){
    FILE *fp = fopen("students.txt", "r");
    fprintf(fp, "%d" , student.student_id, ", %d", student.age, ", %d", student.year);
    fclose(fp);
}

int main(void){
    struct Student Student;

    printf("What is your student ID?\n");
    scanf("%i", Student.student_id);
    printf("What is your age?\n");
    scanf("%i", Student.age);
    printf("What is year did you start at UOIT?\n");
    scanf("%i", Student.year);
    
    save_student(Student);
}