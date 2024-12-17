#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100

int graph[MAX_NODES][MAX_NODES];
int visited[MAX_NODES];
int n, e;
int nodeOrder[MAX_NODES]; // 存储节点输入的顺序

void dfs(int node) {
    visited[node] = 1;
    printf("%d ", nodeOrder[node]); // 输出节点的原始输入顺序
    for (int i = 0; i < n; i++) {
        if (graph[node][i] && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    scanf("%d %d", &n, &e);
    memset(visited, 0, sizeof(visited));

    // 初始化图
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    // 读取节点编号并记录顺序
    for (int i = 0; i < n; i++) {
        int node;
        scanf("%d", &node);
        nodeOrder[i] = node; // 记录节点的输入顺序
    }

    // 读取边
    for (int i = 0; i < e; i++) {
        int u, v;
        char comma;
        scanf("%d%c%d", &u, &comma, &v); // 读取边，注意%c用于读取逗号
        graph[u][v] = 1; // 因为是无向图，所以需要添加两个方向
        graph[v][u] = 1;
    }

    // 执行DFS
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    printf("\n");
    return 0;
}