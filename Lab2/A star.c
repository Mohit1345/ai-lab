#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 2147483647

int min(int a, int b) {
    return (a < b) ? a : b;
}

int rows, columns;

int* minimum(int openlist[rows][columns], int closedlist[rows][columns], int maze[rows][columns]) {
    int Min = INT_MAX;
    int r = -1, c = -1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (Min > openlist[i][j] && closedlist[i][j] == 0) {
                Min = openlist[i][j];
                r = i;
                c = j;
            }
        }
    }
    printf("Current coordinates: %d %d\n", r, c);
    int* ans = (int*)malloc(2 * sizeof(int));
    ans[0] = r;
    ans[1] = c;
    return ans;
}

int abs(int i) {
    return (i < 0) ? -i : i;
}

int main() {
    int i, j;
    printf("Enter No. of rows: ");
    scanf("%d", &rows);

    printf("Enter No. of columns: ");
    scanf("%d", &columns);

    int maze[rows][columns];

    printf("Start Coordinates: ");
    int s_row;
    scanf("%d", &s_row);
    int s_col;
    scanf("%d", &s_col);

    printf("End Coordinates: ");
    int e_row;
    scanf("%d", &e_row);
    int e_col;
    scanf("%d", &e_col);

    printf("Enter Heuristic Matrix (Costs to reach the destination):\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            scanf("%d", &maze[i][j]);
            if (maze[i][j] == -1) {
                // Treat -1 in the heuristic matrix as a block by setting it to INT_MAX
                maze[i][j] = INT_MAX;
            }
        }
    }

    int openlist[rows][columns];
    int closedlist[rows][columns];

    printf("Heuristic Matrix : \n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            openlist[i][j] = INT_MAX;
            closedlist[i][j] = 0;
            printf("%d | ", maze[i][j]);
        }
        printf("\n-------------------------------\n");
    }

    openlist[s_row][s_col] = 0; // Initialize start node with cost 0
    int r_mat[] = {0, 0, 1, -1};
    int c_mat[] = {1, -1, 0, 0};

    int x = rows * columns;
    while (x--) {
        int* r_p = minimum(openlist, closedlist, maze);
        int r = r_p[0], c = r_p[1];

        if (r == e_row && c == e_col) {
            printf("Coordinates Found!!");
            break;
        }

        if (r == -1 || c == -1) {
            continue;
        }

        closedlist[r][c] = 1;

        for (int i = 0; i < 4; i++) {
            int n_r = r + r_mat[i];
            int n_c = c + c_mat[i];
            if (n_r >= 0 && n_r < rows && n_c >= 0 && n_c < columns && closedlist[n_r][n_c] == 0) {
                int new_cost = openlist[r][c] + 1; // Assuming a cost of 1 for each step
                if (new_cost < openlist[n_r][n_c]) {
                    openlist[n_r][n_c] = new_cost;
                }
            }
        }
    }

    return 0;
}
