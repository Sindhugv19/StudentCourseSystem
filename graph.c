#include <stdio.h>
#include "graph.h"

static int adj[MAX][MAX];
static int n = 0;

void initAdjMatrix() {
    int i, j;
    for (i = 0; i < MAX; i++)
        for (j = 0; j < MAX; j++)
            adj[i][j] = 0;
}

void addPrerequisite(int from, int to) {
    if (from < MAX && to < MAX) {
        adj[from][to] = 1;

        if (from > n) n = from;
        if (to > n) n = to;

        printf("Added\n");
    } else {
        printf("Invalid IDs\n");
    }
}

void showPrerequisites() {
    int i, j;
    printf("\nPrerequisite Matrix:\n");
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= n; j++)
            printf("%d ", adj[i][j]);
        printf("\n");
    }
}

