#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>  
#include <stdlib.h>  

// �������ṹ��  
typedef struct {
    int** data; // ָ��ָ�������ָ�룬ÿ��ָ��ָ��һ�е�����  
    int rows;   // ���������  
    int cols;   // ���������  
} Matrix;

// ��ʼ�����󣬶�̬�����ڴ�  
Matrix* initMatrix(int rows, int cols) {
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix->data[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            matrix->data[i][j] = 0; // ��ʼ��Ϊ0  
        }
    }
    return matrix;
}

// ������������  
int getRows(Matrix* matrix) {
    return matrix->rows;
}

// ������������  
int getCols(Matrix* matrix) {
    return matrix->cols;
}

// ��������е�Aij  
int getElement(Matrix* matrix, int i, int j) {
    if (i >= 0 && i < matrix->rows && j >= 0 && j < matrix->cols) {
        return matrix->data[i][j];
    }
    else {
        printf("Error: Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

// ���þ����е�Aij  
void setElement(Matrix* matrix, int i, int j, int value) {
    if (i >= 0 && i < matrix->rows && j >= 0 && j < matrix->cols) {
        matrix->data[i][j] = value;
    }
    else {
        printf("Error: Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

// ����ļӷ�  
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

// ����ĳ˷�  
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

// �������󲢴�ӡ  
void printMatrix(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
           // printf("%05d ", matrix->data[i][j]); // ���ʱռ5λ���  
        }
        printf("\n");
    }
}

// �ͷž���ռ�õ��ڴ�  
void freeMatrix(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

int main() {
    // ʾ��ʹ��  
    Matrix* matrix1 = initMatrix(3, 3);
    Matrix* matrix2 = initMatrix(3, 3);

    // ���þ���Ԫ�أ�Ϊ��ʾ���������ֶ����ã�  
    setElement(matrix1, 0, 0, 1); setElement(matrix1, 0, 1, 2); setElement(matrix1, 0, 2, 3);
    setElement(matrix1, 1, 0, 4); setElement(matrix1, 1, 1, 5); setElement(matrix1, 1, 2, 6);
    setElement(matrix1, 2, 0, 7); setElement(matrix1, 2, 1, 8); setElement(matrix1, 2, 2, 9);

    setElement(matrix2, 0, 0, 9); setElement(matrix2, 0, 1, 8); setElement(matrix2, 0, 2, 7);
    setElement(matrix2, 1, 0, 6); setElement(matrix2, 1, 1, 5); setElement(matrix2, 1, 2, 4);
    setElement(matrix2, 2, 0, 3); setElement(matrix2, 2, 1, 2); setElement(matrix2, 2, 2, 1);

    // ��ӡ����  
    printf("Matrix 1:\n");
    printMatrix(matrix1);

    printf("Matrix 2:\n");
    printMatrix(matrix2);

    // ����ӷ�  
    Matrix* sumMatrix = addMatrices(matrix1, matrix2);
    printf("Sum of Matrices:\n");
    printMatrix(sumMatrix);
    freeMatrix(sumMatrix); // �������ͷ��ڴ�  

    // ����˷�  
    Matrix* productMatrix = multiplyMatrices(matrix1, matrix2);
    printf("Product of Matrices:\n");
    printMatrix(productMatrix);
    freeMatrix(productMatrix); // �ͷ��ڴ�  

    // �ͷ�ԭʼ������ڴ�  
    freeMatrix(matrix1);
    freeMatrix(matrix2);

    return 0;
}