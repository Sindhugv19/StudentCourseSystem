#include <stdio.h>
#include <string.h>
#include "course.h"
#include "student.h"

static Course courses[MAX_COURSES];
static int courseCount = 0;

void initQueue(Course *c) {
    c->front = c->rear = -1;
}

int isFull(Course *c) {
    return c->rear == MAX_WAIT - 1;
}

int isEmpty(Course *c) {
    return c->front == -1 || c->front > c->rear;
}

void enqueue(Course *c, int id) {
    if (isFull(c)) {
        printf("Waitlist full\n");
        return;
    }
    if (c->front == -1)
        c->front = 0;
    c->rear++;
    c->waitingQueue[c->rear] = id;
}

int dequeue(Course *c) {
    if (isEmpty(c))
        return -1;
    return c->waitingQueue[c->front++];
}

void addCourse() {
    int id, capacity;
    char title[MAX_TITLE];

    printf("Enter Course ID: ");
    scanf("%d", &id);
    getchar();

    printf("Enter Course Title: ");
    fgets(title, MAX_TITLE, stdin);
    title[strcspn(title, "\n")] = 0;

    printf("Enter Course Capacity: ");
    scanf("%d", &capacity);

    courses[courseCount].id = id;
    strcpy(courses[courseCount].title, title);
    courses[courseCount].capacity = capacity;
    courses[courseCount].enrolledCount = 0;

    initQueue(&courses[courseCount]);
    courseCount++;

    printf("Course added\n");
}

void displayCourses() {
    int i, j;
    for (i = 0; i < courseCount; i++) {
        printf("%s (ID %d) Cap %d Enrolled %d\n",
               courses[i].title, courses[i].id,
               courses[i].capacity, courses[i].enrolledCount);

        printf("Enrolled: ");
        for (j = 0; j < courses[i].enrolledCount; j++)
            printf("%d ", courses[i].enrolledStudents[j]);
        printf("\n");
    }
}

void registerCourse() {
    int sid, cid, sIndex, cIndex = -1, i;

    printf("Enter Student ID: ");
    scanf("%d", &sid);

    sIndex = findStudentById(sid);
    if (sIndex == -1) {
        printf("Student not found\n");
        return;
    }

    if (hasCourseLimitReached(sid)) {
        printf("Course limit reached\n");
        return;
    }

    printf("Enter Course ID: ");
    scanf("%d", &cid);

    for (i = 0; i < courseCount; i++)
        if (courses[i].id == cid)
            cIndex = i;

    if (cIndex == -1) {
        printf("Course not found\n");
        return;
    }

    for (i = 0; i < courses[cIndex].enrolledCount; i++) {
        if (courses[cIndex].enrolledStudents[i] == sid) {
            printf("Already enrolled\n");
            return;
        }
    }

    if (courses[cIndex].enrolledCount < courses[cIndex].capacity) {
        courses[cIndex].enrolledStudents[courses[cIndex].enrolledCount] = sid;
        courses[cIndex].enrolledCount++;
        incrementCourseCount(sid);
        printf("Registered\n");
    } else {
        enqueue(&courses[cIndex], sid);
        printf("Added to waitlist\n");
    }
}



void showCourseWithWaitlist() {
    int i, j;
    for (i = 0; i < courseCount; i++) {
        printf("%s (ID %d)\n", courses[i].title, courses[i].id);
        if (isEmpty(&courses[i])) {
            printf("Waitlist empty\n");
        } else {
            printf("Waitlist: ");
            for (j = courses[i].front; j <= courses[i].rear; j++)
                printf("%d ", courses[i].waitingQueue[j]);
            printf("\n");
        }
    }
}
void dropCourse() {
    int sid, cid, cIndex = -1, i, j, pos = -1;

    printf("Enter Student ID: ");
    scanf("%d", &sid);

    printf("Enter Course ID: ");
    scanf("%d", &cid);

    for (i = 0; i < courseCount; i++)
        if (courses[i].id == cid)
            cIndex = i;

    if (cIndex == -1) {
        printf("Course not found\n");
        return;
    }

    for (i = 0; i < courses[cIndex].enrolledCount; i++)
        if (courses[cIndex].enrolledStudents[i] == sid)
            pos = i;

    if (pos == -1) {
        printf("Not enrolled\n");
        return;
    }

    for (j = pos; j < courses[cIndex].enrolledCount - 1; j++)
        courses[cIndex].enrolledStudents[j] =
            courses[cIndex].enrolledStudents[j + 1];

    courses[cIndex].enrolledCount--;

    printf("Dropped\n");
}

void autoEnrollFromWaitlist() {
    int i;

    for (i = 0; i < courseCount; i++) {

        while (courses[i].enrolledCount < courses[i].capacity 
               && !isEmpty(&courses[i])) {

            int sid = dequeue(&courses[i]);
            if (sid == -1)
                break;

            courses[i].enrolledStudents[courses[i].enrolledCount] = sid;
            courses[i].enrolledCount++;
            incrementCourseCount(sid);

            printf("Auto-enrolled %d in course %d\n", sid, courses[i].id);
        }
    }
}

void generateStudentTranscript() {
    int sid, i, j, found = 0;
    printf("Enter Student ID: ");
    scanf("%d", &sid);

    if (findStudentById(sid) == -1) {
        printf("Student not found\n");
        return;
    }

    printf("Transcript for %d\n", sid);

    for (i = 0; i < courseCount; i++) {
        for (j = 0; j < courses[i].enrolledCount; j++) {
            if (courses[i].enrolledStudents[j] == sid) {
                printf("%s (ID %d)\n", courses[i].title, courses[i].id);
                found = 1;
            }
        }
    }

    if (!found)
        printf("No courses\n");
}

