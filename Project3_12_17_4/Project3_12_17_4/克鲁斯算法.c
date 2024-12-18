#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

#define MAXV 100

typedef struct {
    int u, v, w;
} Edge;

int parent[MAXV];
int rank[MAXV];
Edge edges[MAXV * MAXV];
int n, m;

void makeSet(int v) {
    parent[v] = v;
    rank[v] = 0;
}

int findSet(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = findSet(parent[v]);
}

void unionSet(int a, int b) {
    a = findSet(a);
    b = findSet(b);
    if (a != b) {
        if (rank[a] < rank[b])
            parent[a] = b;
        else {
            parent[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
        }
    }
}

int cmp(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->w - edgeB->w;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &parent[i]);
        makeSet(i);
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d,%d,%d", &u, &v, &w);
        edges[i] = (Edge){ u - 1, v - 1, w };
    }

    qsort(edges, m, sizeof(Edge), cmp);

    int e = 0;
    for (int i = 0; i < m; i++) {
        Edge edge = edges[i];
        if (findSet(edge.u) != findSet(edge.v)) {
            unionSet(edge.u, edge.v);
            printf("%d,%d\n", edge.u + 1, edge.v + 1);
            e++;
            if (e == n - 1)
                break;
        }
    }

    return 0;
}