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
    int* arr = NULL; // ʹ��ָ����ָ��̬���������  
    int n = 0; // ���ڼ�¼�û������������  
    char input[1024]; // ���ڴ洢�û�������ַ���  
    char* token; // ����strtok�ָ��ַ���  
    int num, result;

    // ��ʾ�û�����һϵ���ö��ŷָ�������  
    printf("������һϵ����','���������֣�������Ϻ󰴻س���: ");
    fgets(input, sizeof(input), stdin);

    // ȥ��fgets���µĻ��з�  
    input[strcspn(input, "\n")] = 0;

    // ʹ��strtok��atoi���ַ���ת��Ϊ�������飬����̬�����ڴ�  
    token = strtok(input, ",");
    while (token != NULL) {
        // ��̬���������С������Ϊ�˼򻯣�����ÿ��ֻ����һ�������Ŀռ䣩  
        // ��ʵ��Ӧ���У�����ܻ���Ҫһ���Է������Ŀռ��Լ����ڴ����Ĵ���  
        arr = (int*)realloc(arr, (n + 1) * sizeof(int));

        if (arr == NULL) {
            // ����ڴ����ʧ�ܣ����ӡ������Ϣ���˳�  
            fprintf(stderr, "�ڴ����ʧ��\n");
            exit(EXIT_FAILURE);
        }
        arr[n++] = atoi(token);
        token = strtok(NULL, ",");
    }

    // ��ȡ��������  
    printf("������Ҫ���ҵ�����: ");
    scanf("%d", &num);

    // ���ֲ���  
    result = find_num(arr, n, num);
    if (result != -1) {
        printf("%d�������У��±�Ϊ%d\n", num, result);
    }
    else {
        printf("%d����������\n", num);
    }

    // �ͷŶ�̬������ڴ�  
    free(arr);

    return 0;
}