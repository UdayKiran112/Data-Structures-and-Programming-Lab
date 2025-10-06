#ifndef COURSE_H
#define COURSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward declare Student (don’t include student.h here)
struct Student;

// Structure of course
typedef struct Course
{
    char course_code[128];
    float marks;
    struct Course *next;
    struct Course *prev;
} Course;

// Functions
void addCourse(struct Student *head, int roll, char *course_code, float marks);
void modifyCourse(struct Student *head, int roll, char *course_code, float marks);
void deleteCourse(struct Student *head, int roll, char *course_code);

#endif // COURSE_H
