#ifndef COURSE_H
#define COURSE_H

#define MAX_TITLE 50
#define MAX_COURSES 20
#define MAX_CAPACITY 10
#define MAX_WAIT 10

typedef struct {
    int id;
    char title[MAX_TITLE];
    int capacity;

    int enrolledCount;
    int enrolledStudents[MAX_CAPACITY];

    int waitingQueue[MAX_WAIT];
    int front, rear;

} Course;

void addCourse();
void displayCourses();
void registerCourse();
void dropCourse();
void showCourseWithWaitlist();
void autoEnrollFromWaitlist();
void generateStudentTranscript();

#endif

