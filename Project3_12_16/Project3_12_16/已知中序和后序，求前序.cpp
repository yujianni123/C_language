#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* buildTree(int* postorder, int postStart, int postEnd, int* inorder, int inStart, int inEnd);
void preorderTraversal(TreeNode* root);
void freeTree(TreeNode* root); // 增加释放整棵树内存的函数

int main() {
    int N;
    scanf("%d", &N);

    int* postorder = (int*)malloc(N * sizeof(int));
    int* inorder = (int*)malloc(N * sizeof(int));
    if (!postorder || !inorder) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < N; i++) {
        scanf("%d", &postorder[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &inorder[i]);
    }

    TreeNode* root = buildTree(postorder, 0, N - 1, inorder, 0, N - 1);

    printf("Preorder: ");
    preorderTraversal(root);
    printf("\n");

    freeTree(root); // 释放整棵树的内存
    free(postorder);
    free(inorder);

    return 0;
}

TreeNode* buildTree(int* postorder, int postStart, int postEnd, int* inorder, int inStart, int inEnd) {
    if (postStart > postEnd) return NULL;

    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    if (!root) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    root->val = postorder[postEnd];
    int rootIndex = -1;

    for (int i = inStart; i <= inEnd; i++) {
        if (inorder[i] == root->val) {
            rootIndex = i;
            break;
        }
    }

    int leftTreeSize = rootIndex - inStart;

    root->left = buildTree(postorder, postStart, postStart + leftTreeSize - 1, inorder, inStart, rootIndex - 1);
    root->right = buildTree(postorder, postStart + leftTreeSize, postEnd - 1, inorder, rootIndex + 1, inEnd);

    return root;
}

void preorderTraversal(TreeNode* root) {
    if (root == NULL) return;

    printf("%d ", root->val);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void freeTree(TreeNode* root) {
    if (root == NULL) return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}