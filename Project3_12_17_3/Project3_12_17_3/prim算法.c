#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

int n; // ������
int e; // ����
int graph[MAX_VERTICES][MAX_VERTICES]; // �ڽӾ���
int parent[MAX_VERTICES]; // �洢��С�������ĸ��ڵ�
int mstSet[MAX_VERTICES]; // ����Ƿ�ѡ��

// �ҵ�δ��ѡ�е���С�ߵĶ���
int minKey(int key[], int mstSet[]) {
    int min = INF, min_index;
    for (int v = 0; v < n; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v], min_index = v;
        }
    }
    return min_index;
}

// ��ӡ��С�������ı�
void printMST() {
    // ���� Prim �㷨ѡ��ߵ�˳�����
    for (int i = 0; i < n; i++) {
        if (parent[i] != -1) {
            printf("%d,%d\n", parent[i], i);
        }
    }
}

int main() {
    scanf("%d %d", &n, &e); // ��ȡ�������ͱ���

    // ��ʼ���ڽӾ���
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = INF;
        }
    }

    // ��ȡ����
    for (int i = 0; i < n; i++) {
        int vertex;
        scanf("%d", &vertex);
    }

    // ��ȡ�ߺ�Ȩ��
    for (int i = 0; i < e; i++) {
        int u, v, w;
        char str[100];
        scanf("%s", str);
        sscanf(str, "%d,%d,%d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w; // ����ͼ����Ҫ���ԳƵ�Ȩ��
    }

    // ��ʼ��ѡ������͸��ڵ�����
    int key[MAX_VERTICES];
    for (int i = 0; i < n; i++) {
        key[i] = INF;
        mstSet[i] = 0;
    }
    key[0] = 0; // �Ӷ���0��ʼ����MST
    parent[0] = -1;

    // Prim�㷨
    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = 1;
        for (int v = 0; v < n; v++) {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u, key[v] = graph[u][v];
            }
        }
    }

    // ��ӡMST
    printMST();
    return 0;
}