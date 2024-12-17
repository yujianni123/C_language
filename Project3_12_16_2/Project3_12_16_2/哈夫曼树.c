#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 霍夫曼树节点结构体
struct MinHeapNode {
    unsigned freq;
    int data;
    struct MinHeapNode* left, * right;
};

// 霍夫曼树结构体
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

// 创建一个新的霍夫曼树节点
struct MinHeapNode* newNode(int data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// 创建一个霍夫曼树
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// 交换两个最小堆节点
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// 最小堆的最小化函数
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// 检查大小是否为1
int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// 提取最小值节点
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// 插入一个新节点到最小堆
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// 构建最小堆
void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// 打印霍夫曼编码
void printCodes(struct MinHeapNode* root, char* code, int top) {
    if (root->left) {
        code[top] = '0';
        printCodes(root->left, code, top + 1);
    }
    if (root->right) {
        code[top] = '1';
        printCodes(root->right, code, top + 1);
    }
    if (!(root->left) && !(root->right)) {
        code[top] = '\0';
        printf("%d:%s\n", root->data, code);
    }
}

// 构建霍夫曼树并打印编码
void HuffmanCodes(int data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);

    while (!isSizeOne(minHeap)) {
        struct MinHeapNode* left = extractMin(minHeap);
        struct MinHeapNode* right = extractMin(minHeap);
        struct MinHeapNode* sum = newNode(-1, left->freq + right->freq);
        sum->left = left;
        sum->right = right;
        insertMinHeap(minHeap, sum);
    }

    char code[100];
    printCodes(minHeap->array[0], code, 0);
}

int main() {
    int n;
    scanf("%d", &n);

    int* data = (int*)malloc(n * sizeof(int));
    int* freq = (int*)malloc(n * sizeof(int));
    if (!data || !freq) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < n; ++i) {
        scanf("%d", &freq[i]);
        data[i] = freq[i]; // 使用权重作为数据值
    }

    printf("Huffman code is:\n");
    HuffmanCodes(data, freq, n);

    free(data);
    free(freq);
    return 0;
}