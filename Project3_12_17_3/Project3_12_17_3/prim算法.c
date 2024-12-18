#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

int n; // 顶点数
int e; // 边数
int graph[MAX_VERTICES][MAX_VERTICES]; // 邻接矩阵
int parent[MAX_VERTICES]; // 存储最小生成树的父节点
int mstSet[MAX_VERTICES]; // 标记是否被选中

// 找到未被选中的最小边的顶点
int minKey(int key[], int mstSet[]) {
    int min = INF, min_index;
    for (int v = 0; v < n; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v], min_index = v;
        }
    }
    return min_index;
}

// 打印最小生成树的边
void printMST() {
    // 按照 Prim 算法选择边的顺序输出
    for (int i = 0; i < n; i++) {
        if (parent[i] != -1) {
            printf("%d,%d\n", parent[i], i);
        }
    }
}

int main() {
    scanf("%d %d", &n, &e); // 读取顶点数和边数

    // 初始化邻接矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = INF;
        }
    }

    // 读取顶点
    for (int i = 0; i < n; i++) {
        int vertex;
        scanf("%d", &vertex);
    }

    // 读取边和权重
    for (int i = 0; i < e; i++) {
        int u, v, w;
        char str[100];
        scanf("%s", str);
        sscanf(str, "%d,%d,%d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w; // 无向图，需要填充对称的权重
    }

    // 初始化选中数组和父节点数组
    int key[MAX_VERTICES];
    for (int i = 0; i < n; i++) {
        key[i] = INF;
        mstSet[i] = 0;
    }
    key[0] = 0; // 从顶点0开始构建MST
    parent[0] = -1;

    // Prim算法
    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = 1;
        for (int v = 0; v < n; v++) {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u, key[v] = graph[u][v];
            }
        }
    }

    // 打印MST
    printMST();
    return 0;
}