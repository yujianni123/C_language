#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

// ����ͼ���ڽӾ����ʾ
int graph[MAX_NODES][MAX_NODES];
int visited[MAX_NODES] = { 0 }; // ���ʱ������
int n, e; // �ڵ����ͱ���

// ��������BFS
int queue[MAX_NODES];
int front = 0, rear = 0;

// �����Ƿ�Ϊ��
int isEmpty() {
    return front == rear;
}

// ���
void enqueue(int value) {
    queue[rear++] = value;
}

// ����
int dequeue() {
    return queue[front++];
}

// BFS�㷨
void BFS(int start) {
    enqueue(start); // ����ʼ�ڵ����
    visited[start] = 1; // ���Ϊ�ѷ���

    while (!isEmpty()) {
        int current = dequeue(); // ����
        printf("%d", current); // ��ӡ��ǰ�ڵ�

        // ����Ƿ���δ����Ľڵ�
        int hasUnvisited = 0;
        for (int i = 0; i < n; i++) {
            if (graph[current][i] && !visited[i]) {
                visited[i] = 1; // ���Ϊ�ѷ���
                enqueue(i); // ���
                hasUnvisited = 1; // ��ǻ���δ����Ľڵ�
            }
        }

        // �������δ����Ľڵ㣬��ӡ����
        if (hasUnvisited) {
            printf(",");
        }
    }
}

int main() {
    scanf("%d %d", &n, &e);

    // ��ʼ��ͼ���ڽӾ���
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    // ��ȡ�ڵ���
    for (int i = 0; i < n; i++) {
        int node;
        scanf("%d", &node);
    }

    // ��ȡ��
    for (int i = 0; i < e; i++) {
        int u, v;
        char comma;
        scanf("%d,%d", &u, &v);
        graph[u][v] = 1; // ����ͼ��������Ҫ�����������ı�
        graph[v][u] = 1;
    }

    // ִ��BFS
    BFS(0); // ����ӽڵ�0��ʼBFS

    return 0;
}