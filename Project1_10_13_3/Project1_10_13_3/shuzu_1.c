#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>  
#include <stdlib.h>  

// 定义矩阵结构体  
typedef struct {
    int** data; // 指向指针数组的指针，每个指针指向一行的整数  
    int rows;   // 矩阵的行数  
    int cols;   // 矩阵的列数  
} Matrix;

// 初始化矩阵，动态分配内存  
Matrix* initMatrix(int rows, int cols) {
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix->data[i] = (int*)malloc(cols * sizeof(int));
    }
    // 初始化所有元素为0（可选，根据需要可以省略）  
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix->data[i][j] = 0;
        }
    }
    return matrix;
}

// 输出矩阵的行数  
int getRows(Matrix* matrix) {
    return matrix->rows;
}

// 输出矩阵的列数  
int getCols(Matrix* matrix) {
    return matrix->cols;
}

// 输出矩阵中的Aij  
int getElement(Matrix* matrix, int i, int j) {
    if (i >= 0 && i < matrix->rows && j >= 0 && j < matrix->cols) {
        return matrix->data[i][j];
    }
    else {
        printf("Error: Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

// 设置矩阵中的Aij（此处为辅助函数，不直接用于ADT操作，但可用于测试）  
void setElement(Matrix* matrix, int i, int j, int value) {
    if (i >= 0 && i < matrix->rows && j >= 0 && j < matrix->cols) {
        matrix->data[i][j] = value;
    }
    else {
        printf("Error: Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

// 从标准输入读取矩阵  
void readMatrix(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            scanf("%d", &matrix->data[i][j]);
        }
    }
}

// 输出矩阵  
void printMatrix(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%5d", matrix->data[i][j]);
        }
        printf("\n");
    }
}

// 矩阵的加法  
Matrix* addMatrices(Matrix* matrix1, Matrix* matrix2) {
    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols) {
        printf("Error: Matrices dimensions do not match\n");
        exit(EXIT_FAILURE);
    }
    Matrix* result = initMatrix(matrix1->rows, matrix1->cols);
    for (int i = 0; i < matrix1->rows; i++) {
        for (int j = 0; j < matrix1->cols; j++) {
            result->data[i][j] = matrix1->data[i][j] + matrix2->data[i][j];
        }
    }
    return result;
}

// 矩阵的乘法  
Matrix* multiplyMatrices(Matrix* matrix1, Matrix* matrix2) {
    if (matrix1->cols != matrix2->rows) {
        printf("Error: Matrices cannot be multiplied\n");
        exit(EXIT_FAILURE);
    }
    Matrix* result = initMatrix(matrix1->rows, matrix2->cols);
    for (int i = 0; i < matrix1->rows; i++) {
        for (int j = 0; j < matrix2->cols; j++) {
            result->data[i][j] = 0;
            for (int k = 0; k < matrix1->cols; k++) {
                result->data[i][j] += matrix1->data[i][k] * matrix2->data[k][j];
            }
        }
    }
    return result;
}

// 释放矩阵占用的内存  
void freeMatrix(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

int main() {
    // 初始化矩阵  
    Matrix* matrixA = initMatrix(3, 3);
    Matrix* matrixB = initMatrix(3, 3);
    Matrix* sumMatrix = NULL;
    Matrix* productMatrix = NULL;

    // 读取矩阵A和B  
    readMatrix(matrixA);
    readMatrix(matrixB);

    // 输出矩阵A和B的和  
    sumMatrix = addMatrices(matrixA, matrixB);
    printf("A+B=:\n");
    printMatrix(sumMatrix);

    // 计算矩阵A和B的乘积  
    productMatrix = multiplyMatrices(matrixA, matrixB);
    printf("A*B=:\n");
    printMatrix(productMatrix);

    // 释放内存  
    freeMatrix(matrixA);
    freeMatrix(matrixB);
    freeMatrix(sumMatrix);
    freeMatrix(productMatrix);

    return 0;
}