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
    }
    // ��ʼ������Ԫ��Ϊ0����ѡ��������Ҫ����ʡ�ԣ�  
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix->data[i][j] = 0;
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

// ���þ����е�Aij���˴�Ϊ������������ֱ������ADT�������������ڲ��ԣ�  
void setElement(Matrix* matrix, int i, int j, int value) {
    if (i >= 0 && i < matrix->rows && j >= 0 && j < matrix->cols) {
        matrix->data[i][j] = value;
    }
    else {
        printf("Error: Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

// �ӱ�׼�����ȡ����  
void readMatrix(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            scanf("%d", &matrix->data[i][j]);
        }
    }
}

// �������  
void printMatrix(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%5d", matrix->data[i][j]);
        }
        printf("\n");
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

// �ͷž���ռ�õ��ڴ�  
void freeMatrix(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

int main() {
    // ��ʼ������  
    Matrix* matrixA = initMatrix(3, 3);
    Matrix* matrixB = initMatrix(3, 3);
    Matrix* sumMatrix = NULL;
    Matrix* productMatrix = NULL;

    // ��ȡ����A��B  
    readMatrix(matrixA);
    readMatrix(matrixB);

    // �������A��B�ĺ�  
    sumMatrix = addMatrices(matrixA, matrixB);
    printf("A+B=:\n");
    printMatrix(sumMatrix);

    // �������A��B�ĳ˻�  
    productMatrix = multiplyMatrices(matrixA, matrixB);
    printf("A*B=:\n");
    printMatrix(productMatrix);

    // �ͷ��ڴ�  
    freeMatrix(matrixA);
    freeMatrix(matrixB);
    freeMatrix(sumMatrix);
    freeMatrix(productMatrix);

    return 0;
}