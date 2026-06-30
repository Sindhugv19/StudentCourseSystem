#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME 50
#define MAX_STUDENTS 50
#define MAX_STUDENT_COURSES 5

typedef struct {
    int id;
    char name[MAX_NAME];
} Student;

void addStudent();
void displayStudents();
int findStudentById(int id);
char* getStudentName(int id);
int hasCourseLimitReached(int sid);
void incrementCourseCount(int sid);

#endif

