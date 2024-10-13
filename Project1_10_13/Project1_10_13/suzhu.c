#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>  
int main()
{
    int a[3][3] = { 0 };
    int b[3][3] = { 0 };
    int result[3][3] = { 0 };
    int i, j, k;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            scanf("%d", &b[i][j]);
        }
    }
    printf("A+B=:\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%5d", a[i][j] + b[i][j]);
        }
        printf("\n");
    }
    printf("A*B=:\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            result[i][j] = 0;
            for (k = 0; k < 3; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%5d", result[i][j]);
        }
        printf("\n");
    }
    return 0;
}