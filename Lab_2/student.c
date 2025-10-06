#include "student.h"

// Function to add a student
void addStudent(Student **head, int roll, char *student_name, float cgpa, int no_of_subs)
{
    if (!head)
    {
        fprintf(stderr, "Error: head pointer is NULL in addStudent.\n");
        return;
    }

    Student *newstudent = (Student *)malloc(sizeof(Student));
    if (!newstudent)
    {
        fprintf(stderr, "Error: Memory allocation failed in addStudent.\n");
        return;
    }

    newstudent->roll_no = roll;
    strcpy(newstudent->name, student_name);
    newstudent->cgpa = cgpa;
    newstudent->no_of_subjects = no_of_subs;
    newstudent->courseHead = NULL;
    newstudent->prev = NULL;
    newstudent->next = NULL;

    if (*head == NULL)
    {
        *head = newstudent;
        printf("Student %d (%s) added as head.\n", roll, student_name);
        return;
    }

    Student *temp = *head;
    while (temp->next != NULL)
    {
        if (temp->roll_no == roll)
        {
            fprintf(stderr, "Warning: Duplicate roll number %d found in addStudent. Skipping.\n", roll);
            free(newstudent);
            return;
        }
        temp = temp->next;
    }

    temp->next = newstudent;
    newstudent->prev = temp;
    printf("Student %d (%s) added successfully.\n", roll, student_name);
}

// Function to find a student in the DLL
Student *findStudent(Student *head, int roll)
{
    if (!head)
    {
        fprintf(stderr, "Error: Student list is empty in findStudent.\n");
        return NULL;
    }

    Student *temp = head;
    while (temp != NULL)
    {
        if (temp->roll_no == roll)
        {
            return temp;
        }
        temp = temp->next;
    }

    fprintf(stderr, "Error: Student with roll number %d not found.\n", roll);
    return NULL;
}

void modifyStudent(Student *head, int roll, float new_cgpa)
{
    Student *student = findStudent(head, roll);
    if (student != NULL)
    {
        printf("Student %d CGPA changed from %.2f to %.2f.\n",
               roll, student->cgpa, new_cgpa);
        student->cgpa = new_cgpa;
    }
    else
    {
        fprintf(stderr, "Error: Cannot modify CGPA. Student with roll %d not found.\n", roll);
    }
}

// Function to delete a student
void deleteStudent(Student **head, int roll)
{
    if (!head || !*head)
    {
        fprintf(stderr, "Error: Student list is empty in deleteStudent.\n");
        return;
    }

    Student *student = findStudent(*head, roll);
    if (student == NULL)
    {
        fprintf(stderr, "Error: Student with roll %d not found. Cannot delete.\n", roll);
        return;
    }

    // free all the courses of student
    Course *c = student->courseHead;
    while (c != NULL)
    {
        Course *temp = c;
        c = c->next;
        free(temp);
    }

    if (student->prev != NULL)
    {
        student->prev->next = student->next;
    }
    else
    {
        *head = student->next; // student was head
    }

    if (student->next != NULL)
    {
        student->next->prev = student->prev;
    }

    printf("Student %d (%s) deleted successfully.\n", student->roll_no, student->name);
    free(student);
}

// Function which free the entire student list
void freeStudentList(Student *head)
{
    Student *temp = head;
    while (temp != NULL)
    {
        Student *next = temp->next;
        free(temp);
        temp = next;
    }
}
