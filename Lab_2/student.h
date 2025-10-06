#ifndef STUDENT_H
#define STUDENT_H

#include "course.h"

// Structure of student
typedef struct Student
{
    int roll_no;
    char name[256];
    float cgpa;
    int no_of_subjects;
    Course *courseHead;
    struct Student *prev, *next;
} Student;

extern Student *studentHead;

// Methods
void addStudent(Student **head, int roll, char *student_name, float cgpa, int no_of_subs);
Student *findStudent(Student *head, int roll);
void modifyStudent(Student *head, int roll, float new_cgpa);
void deleteStudent(Student **head, int roll);
void freeStudentList(Student *head);

#endif