#include "course.h"
#include "student.h"

// Function to add a course for a student
void addCourse(Student *head, int roll, char *course_code, float marks)
{
    Student *student = findStudent(head, roll);
    if (!student)
    {
        fprintf(stderr, "Error: Cannot add course %s. Student with roll %d not found.\n",
                course_code, roll);
        return;
    }

    Course *newcourse = (Course *)malloc(sizeof(Course));
    if (!newcourse)
    {
        fprintf(stderr, "Error: Memory allocation failed in addCourse for student %d.\n", roll);
        return;
    }

    strcpy(newcourse->course_code, course_code);
    newcourse->marks = marks;
    newcourse->next = NULL;
    newcourse->prev = NULL;

    if (student->courseHead == NULL) // empty list
    {
        student->courseHead = newcourse;
    }
    else // non-empty list
    {
        newcourse->next = student->courseHead;
        student->courseHead->prev = newcourse;
        student->courseHead = newcourse;
    }

    student->no_of_subjects++;
    printf("Course %s (marks: %.2f) added for student %d (%s).\n",
           course_code, marks, student->roll_no, student->name);
}

// Function to modify a course for a student
void modifyCourse(Student *head, int roll, char *course_code, float marks)
{
    Student *student = findStudent(head, roll);
    if (!student)
    {
        fprintf(stderr, "Error: Cannot modify course %s. Student with roll %d not found.\n",
                course_code, roll);
        return;
    }

    Course *c = student->courseHead;
    while (c != NULL)
    {
        if (strcmp(c->course_code, course_code) == 0)
        {
            printf("Course %s for student %d updated from %.2f to %.2f.\n",
                   course_code, roll, c->marks, marks);
            c->marks = marks;
            return;
        }
        c = c->next;
    }

    fprintf(stderr, "Error: Course %s not found for student %d. Cannot modify.\n",
            course_code, roll);
}

// Function to delete a course for a student
void deleteCourse(Student *head, int roll, char *course_code)
{
    Student *student = findStudent(head, roll);
    if (!student)
    {
        fprintf(stderr, "Error: Cannot delete course %s. Student with roll %d not found.\n",
                course_code, roll);
        return;
    }

    Course *c = student->courseHead;

    while (c != NULL)
    {
        if (strcmp(c->course_code, course_code) == 0)
        {
            if (c->prev != NULL)
            {
                c->prev->next = c->next;
            }
            else
            {
                student->courseHead = c->next; // deleted head course
            }

            if (c->next != NULL)
            {
                c->next->prev = c->prev;
            }

            printf("Course %s deleted for student %d (%s).\n",
                   course_code, student->roll_no, student->name);

            free(c);
            student->no_of_subjects--;
            return;
        }
        c = c->next;
    }

    fprintf(stderr, "Error: Course %s not found for student %d. Cannot delete.\n",
            course_code, roll);
}
