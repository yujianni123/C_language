#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STUDENTS 100
#define NAME_LEN 50
typedef struct {
    char name[NAME_LEN];
    char password[NAME_LEN];
} Student;
void addStudent(Student students[], int* count) {
    if (*count >= MAX_STUDENTS) {
        printf("��Ա����\n");
        return;
    }
    printf("�������û�����: ");
    scanf("%49s", students[*count].name);
    printf("�������û�����: ");
    scanf("%49s", students[*count].password);
    (*count)++;
    printf("�û���ӳɹ�!\n");
}
void deleteStudent(Student students[], int* count, char name[NAME_LEN]) {
    int found = -1;
    for (int i = 0; i < *count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            found = i;
            break;
        }
    }
    if (found == -1) {
        printf("δ�����û� %s!\n", name);
        return;
    }
    for (int i = found; i < *count - 1; i++) {
        students[i] = students[i + 1];
    }
    (*count)--;
    printf("�û�ɾ���ɹ�!\n");
}
void updateStudent(Student students[], int count, char name[NAME_LEN]) {
    int found = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            found = i;
            break;
        }
    }
    if (found == -1) {
        printf("δ�����û�%s !\n", name);
        return;
    }
    printf("�������µ��û�����: ");
    scanf("%49s", students[found].name);
    printf("�������µ��û�����: ");
    scanf("%49s", students[found].password);
    printf("�û���Ϣ��ӳɹ�!\n");
}
void searchStudent(Student students[], int count, char name[NAME_LEN]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("�����û�: ���� = %s, ���� = %s\n", students[i].name, students[i].password);
            return;
        }
    }
    printf("δ�����û� %s !\n", name);
}
void saveToFile(Student students[], int count, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("���ļ�ʧ��!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s\n", students[i].name, students[i].password);
    }
    fclose(file);
    printf("�����Ѿ��ɹ����浽�ļ�!\n");
}
void loadFromFile(Student students[], int* count, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("���ļ�ʧ��!\n");
        return;
    }
    while (fscanf(file, "%49s %49s", students[*count].name, students[*count].password) != EOF && *count < MAX_STUDENTS) {
        (*count)++;
    }
    fclose(file);
    printf("�����ѳɹ����ļ��м���!\n");
}

void OpenFile(const Student* students, int count) {
    if (count == 0) {
        printf("û���û���Ϣ��\n");
        return;
    }
    for (int i = 0; i < count; ++i) {
        printf("�û���: %s, ����: %s, ����: %s\n", students[i].name, students[i].password, students[i].name);
    }
}
void manager_Open() {
    Student students[MAX_STUDENTS];
    int count = 0;
    char filename[] = "�û���Ϣ.txt";
    int choice;
    char name[NAME_LEN];
    loadFromFile(students, &count, filename);
    do {
        printf("\n1. �鿴�û�\n");
        printf("2. �����û�\n");
        printf("3. ɾ���û�\n");
        printf("4. �����û�\n");
        printf("5. �����û�\n");
        printf("6. ���沢�˳�\n");
        printf("���������ѡ��: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            OpenFile(students, count);
            break;
        case 2:
            addStudent(students, &count);
            break;
        case 3:
            printf("��������Ҫɾ�����û���: ");
            scanf("%49s", name);
            deleteStudent(students, &count, name);
            break;
        case 4:
            printf("��������Ҫ�޸ĵ��û���: ");
            scanf("%49s", name);
            updateStudent(students, count, name);
            break;
        case 5:
            printf("��������Ҫ���ҵ��û���: ");
            scanf("%49s", name);
            searchStudent(students, count, name);
            break;
        case 6:
            saveToFile(students, count, filename);
            break;
        default:
            printf("�����ѡ������ѡ��һ��\n");
        }
    } while (choice != 6);
}

int main() {
    manager_Open();
    return 0;
}