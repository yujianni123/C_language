#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100

int graph[MAX_NODES][MAX_NODES];
int visited[MAX_NODES];
int n, e;
int nodeOrder[MAX_NODES]; // �洢�ڵ������˳��

void dfs(int node) {
    visited[node] = 1;
    printf("%d ", nodeOrder[node]); // ����ڵ��ԭʼ����˳��
    for (int i = 0; i < n; i++) {
        if (graph[node][i] && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    scanf("%d %d", &n, &e);
    memset(visited, 0, sizeof(visited));

    // ��ʼ��ͼ
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    // ��ȡ�ڵ��Ų���¼˳��
    for (int i = 0; i < n; i++) {
        int node;
        scanf("%d", &node);
        nodeOrder[i] = node; // ��¼�ڵ������˳��
    }

    // ��ȡ��
    for (int i = 0; i < e; i++) {
        int u, v;
        char comma;
        scanf("%d%c%d", &u, &comma, &v); // ��ȡ�ߣ�ע��%c���ڶ�ȡ����
        graph[u][v] = 1; // ��Ϊ������ͼ��������Ҫ�����������
        graph[v][u] = 1;
    }

    // ִ��DFS
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    printf("\n");
    return 0;
}