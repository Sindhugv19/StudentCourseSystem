#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "course.h"
#include "graph.h"
#include "fancy.h"

int main() {

    initAdjMatrix();

    int choice;

    while (1) {
        fancyMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: addCourse(); break;
            case 3: registerCourse(); break;
            case 4: dropCourse(); break;
            case 5: displayStudents(); break;
            case 6: displayCourses(); break;
            case 7: showCourseWithWaitlist(); break;
            case 8: {
                int f, t;
                printf("FROM TO: ");
                scanf("%d %d", &f, &t);
                addPrerequisite(f, t);
                break;
            }
            case 9: showPrerequisites(); break;
            case 10: autoEnrollFromWaitlist(); break;
            case 11: generateStudentTranscript(); break;
            case 0: exit(0);
        }
    }

    return 0;
}

