#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  

// 假设数组的最大大小为某个固定值（这里设置为100）  
#define MAX_SIZE 100  

// 二分查找函数  
int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1, mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (arr[mid] == key) {
            return mid;
        }
        else if (arr[mid] < key) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return -1; // 如果没有找到  
}

int main() {
    char input[1024];
    int arr[MAX_SIZE];
    int n = 0;
    int key, result;

    // 读取数据集合  
    fgets(input, sizeof(input), stdin);
    // 去除可能存在的换行符  
    input[strcspn(input, "\n")] = 0;

    // 使用逗号分割字符串，并将数字存储在数组中  
    char* token = strtok(input, ",");
    while (token != NULL && n < MAX_SIZE) {
        arr[n++] = atoi(token);
        token = strtok(NULL, ",");
    }

    // 读取待查找的数据（注意：这里假设已经读取了数据集合后的换行符）  
    fgets(input, sizeof(input), stdin);
    // 去除换行符并解析整数  
    input[strcspn(input, "\n")] = 0;
    key = atoi(input);

    // 执行二分查找  
    result = binarySearch(arr, n, key);

    // 输出结果  
    if (result != -1) {
        printf("%d在数组中，下标为%d\n", key, result);
    }
    else {
        printf("%d不在数组中\n", key);
    }

    return 0;
}