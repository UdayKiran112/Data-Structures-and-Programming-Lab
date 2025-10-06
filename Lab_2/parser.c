#include "parser.h"

void parse_file(FILE *fp, Student **studentHead)
{
  if (fp == NULL)
  {
    fprintf(stderr, "Error opening file\n");
    return;
  }

  char line[256];
  enum
  {
    NONE,
    ADD_STUDENT,
    ADD_COURSE,
    MOD_STUDENT,
    MOD_COURSE,
    DEL_STUDENT,
    DEL_COURSE
  } mode = NONE;

  while (fgets(line, sizeof(line), fp))
  {
    // Trim newline at end if present
    line[strcspn(line, "\r\n")] = 0;

    if (line[0] == '#')
    {
      if (strstr(line, "add student"))
        mode = ADD_STUDENT;
      else if (strstr(line, "add course"))
        mode = ADD_COURSE;
      else if (strstr(line, "modify student"))
        mode = MOD_STUDENT;
      else if (strstr(line, "modify course"))
        mode = MOD_COURSE;
      else if (strstr(line, "delete student"))
        mode = DEL_STUDENT;
      else if (strstr(line, "delete course"))
        mode = DEL_COURSE;
      else
        mode = NONE; // reset if unknown directive
      continue;      // skip processing directive line
    }

    int rollNo, no_of_subs;
    char name[50], coursecode[50];
    float cgpa, marks;

    switch (mode)
    {
    case ADD_STUDENT:
      if (sscanf(line, "%d, %49[^,], %f, %d", &rollNo, name, &cgpa, &no_of_subs) == 4)
      {
        addStudent(studentHead, rollNo, name, cgpa, no_of_subs);
      }
      else
      {
        fprintf(stderr, "Invalid ADD_STUDENT line: %s\n", line);
      }
      break;

    case ADD_COURSE:
      if (sscanf(line, "%d, %49[^,], %f", &rollNo, coursecode, &marks) == 3)
      {
        addCourse(*studentHead, rollNo, coursecode, marks);
      }
      else
      {
        fprintf(stderr, "Invalid ADD_COURSE line: %s\n", line);
      }
      break;

    case MOD_STUDENT:
      if (sscanf(line, "%d, %f", &rollNo, &cgpa) == 2)
      {
        modifyStudent(*studentHead, rollNo, cgpa);
      }
      else
      {
        fprintf(stderr, "Invalid MOD_STUDENT line: %s\n", line);
      }
      break;

    case MOD_COURSE:
      if (sscanf(line, "%d, %49[^,], %f", &rollNo, coursecode, &marks) == 3)
      {
        modifyCourse(*studentHead, rollNo, coursecode, marks);
      }
      else
      {
        fprintf(stderr, "Invalid MOD_COURSE line: %s\n", line);
      }
      break;

    case DEL_STUDENT:
      if (sscanf(line, "%d", &rollNo) == 1)
      {
        deleteStudent(studentHead, rollNo);
      }
      else
      {
        fprintf(stderr, "Invalid DEL_STUDENT line: %s\n", line);
      }
      break;

    case DEL_COURSE:
      if (sscanf(line, "%d, %49[^\n]", &rollNo, coursecode) == 2)
      {
        deleteCourse(*studentHead, rollNo, coursecode);
      }
      else
      {
        fprintf(stderr, "Invalid DEL_COURSE line: %s\n", line);
      }
      break;

    default:
      // mode == NONE or unknown -> ignore
      break;
    }
  }
}

void print_students(Student *head)
{
  Student *temp = head;
  printf("\nSTUDENT DATA\n");
  while (temp != NULL)
  {
    printf("Roll No: %d, Name: %s, CGPA: %.2f, No of Subjects: %d\n",
           temp->roll_no, temp->name, temp->cgpa, temp->no_of_subjects);

    Course *c = temp->courseHead;
    while (c != NULL)
    {
      printf("   Course: %s, Marks: %.2f\n", c->course_code, c->marks);
      c = c->next;
    }

    temp = temp->next;
  }
}

// Write student and course data to a file in a neat readable format
void write_to_file(FILE *fp, Student *head)
{
  if (fp == NULL)
  {
    fprintf(stderr, "Error opening file for writing\n");
    return;
  }

  Student *temp = head;

  while (temp != NULL)
  {
    // Print student details
    fprintf(fp, "Roll No: %d, Name: %s, CGPA: %.2f, No of Subjects: %d\n",
            temp->roll_no, temp->name, temp->cgpa, temp->no_of_subjects);

    // Print all courses for that student
    Course *c = temp->courseHead;
    while (c != NULL)
    {
      fprintf(fp, "   Course: %s, Marks: %.2f\n",
              c->course_code, c->marks);
      c = c->next;
    }

    // Add a blank line after each student
    fprintf(fp, "\n");

    temp = temp->next;
  }
}
