#define _CRT_SECURE_NO_WARNINGS 1  
#include <stdio.h>    
#include <stdlib.h>    

void reverse(int* a, int start, int end) {
    while (start < end) {
        int temp = a[start];
        a[start] = a[end];
        a[end] = temp;
        start++;
        end--;
    }
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Failed to read n and m\n");
        return EXIT_FAILURE;
    }

    int* a = (int*)malloc(n * sizeof(int)); // 显式类型转换，但在C中通常是可选的  
    if (a == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            fprintf(stderr, "Failed to read input at position %d\n", i);
            free(a);
            return EXIT_FAILURE;
        }
    }

    m %= n;

    reverse(a, 0, m - 1);
    reverse(a, m, n - 1);
    reverse(a, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) printf(" ");
    }
    printf("\n");

    free(a);

    return 0;
}