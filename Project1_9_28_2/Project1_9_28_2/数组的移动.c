#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>  
#include <stdlib.h> 
/*����Ҫ��ʵ��һ��������������ƣ�һ������a�д���n(>0)���������ڲ�����ʹ�����������ǰ���£���ÿ������ѭ��������
m��>0)��λ�ã�����a�е������ɣ�a0,a1...an-1)�任Ϊ��am...an-1,a0,a1...am-1��(��ǰ���m����ѭ������������m��λ��)��
�������Ҫ���ǳ����ƶ����ݵĴ����������٣�Ҫ�������ƶ��ķ�����
���루input��:
�������У���1�и���������n����100����������m����0������2�и���n����������Կո�ָ���
�����output����
��һ�������ѭ������mλ�Ժ���������У�֮���ÿո�ָ������н�β�����ж���ո�
========================
�����������£�
����
8 3
1 2 3 4 5 6 7 8
���
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

    // ʹ�ö�̬�ڴ���䴴������  
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // ��ȡ����Ԫ��  
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // ִ��ѭ������  
    leftRotate(arr, n, m);

    // ��ӡ���  
    printArray(arr, n);

    // �ͷ��ڴ�  
    free(arr);

    return 0;
}