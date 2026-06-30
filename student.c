#include <stdio.h>
#include <string.h>
#include "student.h"

static Student students[MAX_STUDENTS];
static int studentCount = 0;
static int studentCourseCount[MAX_STUDENTS] = {0};

void addStudent() {
    int id, i;
    char name[MAX_NAME];

    printf("Enter Student ID: ");
    scanf("%d", &id);
    getchar();

    for (i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Student already exists\n");
            return;
        }
    }

    printf("Enter Student Name: ");
    fgets(name, MAX_NAME, stdin);
    name[strcspn(name, "\n")] = 0;

    students[studentCount].id = id;
    strcpy(students[studentCount].name, name);
    studentCount++;

    printf("Student added\n");
}

void displayStudents() {
    int i;
    for (i = 0; i < studentCount; i++)
        printf("ID: %d  Name: %s\n", students[i].id, students[i].name);
}

int findStudentById(int id) {
    int i;
    for (i = 0; i < studentCount; i++)
        if (students[i].id == id)
            return i;
    return -1;
}

char* getStudentName(int id) {
    int i;
    for (i = 0; i < studentCount; i++)
        if (students[i].id == id)
            return students[i].name;
    return "Unknown";
}

int hasCourseLimitReached(int sid) {
    int i = findStudentById(sid);
    if (i == -1) return 1;
    return studentCourseCount[i] >= MAX_STUDENT_COURSES;
}

void incrementCourseCount(int sid) {
    int i = findStudentById(sid);
    if (i != -1)
        studentCourseCount[i]++;
}

