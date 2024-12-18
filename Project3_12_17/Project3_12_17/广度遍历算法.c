#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

// 定义图的邻接矩阵表示
int graph[MAX_NODES][MAX_NODES];
int visited[MAX_NODES] = { 0 }; // 访问标记数组
int n, e; // 节点数和边数

// 队列用于BFS
int queue[MAX_NODES];
int front = 0, rear = 0;

// 队列是否为空
int isEmpty() {
    return front == rear;
}

// 入队
void enqueue(int value) {
    queue[rear++] = value;
}

// 出队
int dequeue() {
    return queue[front++];
}

// BFS算法
void BFS(int start) {
    enqueue(start); // 将起始节点入队
    visited[start] = 1; // 标记为已访问

    while (!isEmpty()) {
        int current = dequeue(); // 出队
        printf("%d", current); // 打印当前节点

        // 检查是否还有未处理的节点
        int hasUnvisited = 0;
        for (int i = 0; i < n; i++) {
            if (graph[current][i] && !visited[i]) {
                visited[i] = 1; // 标记为已访问
                enqueue(i); // 入队
                hasUnvisited = 1; // 标记还有未处理的节点
            }
        }

        // 如果还有未处理的节点，打印逗号
        if (hasUnvisited) {
            printf(",");
        }
    }
}

int main() {
    scanf("%d %d", &n, &e);

    // 初始化图的邻接矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    // 读取节点编号
    for (int i = 0; i < n; i++) {
        int node;
        scanf("%d", &node);
    }

    // 读取边
    for (int i = 0; i < e; i++) {
        int u, v;
        char comma;
        scanf("%d,%d", &u, &v);
        graph[u][v] = 1; // 无向图，所以需要添加两个方向的边
        graph[v][u] = 1;
    }

    // 执行BFS
    BFS(0); // 假设从节点0开始BFS

    return 0;
}