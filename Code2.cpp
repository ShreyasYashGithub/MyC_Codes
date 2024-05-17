#include <stdio.h>
#include <limits.h>

#define MAX_MATRICES 100

void printOptimalParenthesis(int s[MAX_MATRICES][MAX_MATRICES], int i, int j);

int main() {
    int n, i, j, k;
    printf("Enter number of matrices: ");
    scanf("%d", &n);

    int dimensions[MAX_MATRICES];
    for (i = 0; i <= n; i++) {
        printf("Enter row and col size of A%d: ", i + 1);
        scanf("%d %d", &dimensions[i], &dimensions[i + 1]);
    }

    int m[MAX_MATRICES][MAX_MATRICES];
    int s[MAX_MATRICES][MAX_MATRICES];

    for (i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    for (int len = 2; len <= n; len++) {
        for (i = 1; i <= n - len + 1; i++) {
            j = i + len - 1;
            m[i][j] = INT_MAX;

            for (k = i; k <= j - 1; k++) {
                int cost = m[i][k] + m[k + 1][j] + dimensions[i - 1] * dimensions[k] * dimensions[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("M Table:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (j < i) {
                printf("0 ");
            } else {
                printf("%d ", m[i][j]);
            }
        }
        printf("\n");
    }

    printf("S Table:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (j <= i) {
                printf("0 ");
            } else {
                printf("%d ", s[i][j]);
            }
        }
        printf("\n");
    }

    printf("Optimal parenthesization: ");
    printOptimalParenthesis(s, 1, n);
    printf("\n");
    
    printf("The optimal ordering of the given matrices requires %d scalar multiplications.\n", m[1][n]);

    return 0;
}

void printOptimalParenthesis(int s[MAX_MATRICES][MAX_MATRICES], int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalParenthesis(s, i, s[i][j]);
        printOptimalParenthesis(s, s[i][j] + 1, j);
        printf(")");
    }
}

