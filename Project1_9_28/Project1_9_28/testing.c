#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  

// �������������СΪĳ���̶�ֵ����������Ϊ100��  
#define MAX_SIZE 100  

// ���ֲ��Һ���  
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
    return -1; // ���û���ҵ�  
}

int main() {
    char input[1024];
    int arr[MAX_SIZE];
    int n = 0;
    int key, result;

    // ��ȡ���ݼ���  
    fgets(input, sizeof(input), stdin);
    // ȥ�����ܴ��ڵĻ��з�  
    input[strcspn(input, "\n")] = 0;

    // ʹ�ö��ŷָ��ַ������������ִ洢��������  
    char* token = strtok(input, ",");
    while (token != NULL && n < MAX_SIZE) {
        arr[n++] = atoi(token);
        token = strtok(NULL, ",");
    }

    // ��ȡ�����ҵ����ݣ�ע�⣺��������Ѿ���ȡ�����ݼ��Ϻ�Ļ��з���  
    fgets(input, sizeof(input), stdin);
    // ȥ�����з�����������  
    input[strcspn(input, "\n")] = 0;
    key = atoi(input);

    // ִ�ж��ֲ���  
    result = binarySearch(arr, n, key);

    // ������  
    if (result != -1) {
        printf("%d�������У��±�Ϊ%d\n", key, result);
    }
    else {
        printf("%d����������\n", key);
    }

    return 0;
}