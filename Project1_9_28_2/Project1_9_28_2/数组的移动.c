#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>  
#include <stdlib.h> 
/*本题要求实现一个对数组进行左移：一个数组a中存有n(>0)个整数，在不允许使用另外数组的前提下，将每个整数循环向左移
m（>0)个位置，即将a中的数组由（a0,a1...an-1)变换为（am...an-1,a0,a1...am-1）(最前面的m个数循环移至最后面的m个位置)。
如果还需要考虑程序移动数据的次数尽量最少，要如何设计移动的方法。
输入（input）:
输入两行，第1行给出正整数n（≤100）和正整数m（≥0）；第2行给出n个数，其间以空格分隔。
输出（output）：
在一行中输出循环左移m位以后的整数序列，之间用空格分隔，序列结尾不能有多余空格。
========================
测试用例如下：
输入
8 3
1 2 3 4 5 6 7 8
输出
4 5 6 7 8 1 2 3*/

void reverse(int* a, int start, int end) {
    while (start < end) {
        int temp = a[start];
        a[start] = a[end];
        a[end] = temp;
        start++;
        end--;
    }
}

void leftRotate(int* a, int n, int m) {
    m = m % n;
    if (m == 0) return;

    reverse(a, 0, n - 1);
    reverse(a, 0, m - 1);
    reverse(a, m, n - 1);
}

void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // 使用动态内存分配创建数组  
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // 读取数组元素  
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // 执行循环左移  
    leftRotate(arr, n, m);

    // 打印结果  
    printArray(arr, n);

    // 释放内存  
    free(arr);

    return 0;
}