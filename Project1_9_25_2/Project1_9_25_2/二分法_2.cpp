#define _CRT_SECURE_NO_WARNINGS 1  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  

int find_num(int* arr, int n, int key) {
    int low = 0, high = n - 1, mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (key == arr[mid]) {
            return mid;
        }
        else if (arr[mid] < key) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return -1;
}

int main() {
    int* arr = NULL; // 使用指针来指向动态分配的数组  
    int n = 0; // 用于记录用户输入的数据量  
    char input[1024]; // 用于存储用户输入的字符串  
    char* token; // 用于strtok分割字符串  
    int num, result;

    // 提示用户输入一系列用逗号分隔的数字  
    printf("请输入一系列用','隔开的数字（输入完毕后按回车）: ");
    fgets(input, sizeof(input), stdin);

    // 去除fgets留下的换行符  
    input[strcspn(input, "\n")] = 0;

    // 使用strtok和atoi将字符串转换为整数数组，并动态分配内存  
    token = strtok(input, ",");
    while (token != NULL) {
        // 动态增加数组大小（这里为了简化，我们每次只分配一个整数的空间）  
        // 在实际应用中，你可能会想要一次性分配更大的空间以减少内存分配的次数  
        arr = (int*)realloc(arr, (n + 1) * sizeof(int));

        if (arr == NULL) {
            // 如果内存分配失败，则打印错误信息并退出  
            fprintf(stderr, "内存分配失败\n");
            exit(EXIT_FAILURE);
        }
        arr[n++] = atoi(token);
        token = strtok(NULL, ",");
    }

    // 读取查找数据  
    printf("请输入要查找的数字: ");
    scanf("%d", &num);

    // 二分查找  
    result = find_num(arr, n, num);
    if (result != -1) {
        printf("%d在数组中，下标为%d\n", num, result);
    }
    else {
        printf("%d不在数组中\n", num);
    }

    // 释放动态分配的内存  
    free(arr);

    return 0;
}