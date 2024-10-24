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
        printf("人员已满\n");
        return;
    }
    printf("请输入用户姓名: ");
    scanf("%49s", students[*count].name);
    printf("请输入用户密码: ");
    scanf("%49s", students[*count].password);
    (*count)++;
    printf("用户添加成功!\n");
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
        printf("未发现用户 %s!\n", name);
        return;
    }
    for (int i = found; i < *count - 1; i++) {
        students[i] = students[i + 1];
    }
    (*count)--;
    printf("用户删除成功!\n");
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
        printf("未发现用户%s !\n", name);
        return;
    }
    printf("请输入新的用户姓名: ");
    scanf("%49s", students[found].name);
    printf("请输入新的用户密码: ");
    scanf("%49s", students[found].password);
    printf("用户信息添加成功!\n");
}
void searchStudent(Student students[], int count, char name[NAME_LEN]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("发现用户: 姓名 = %s, 密码 = %s\n", students[i].name, students[i].password);
            return;
        }
    }
    printf("未发现用户 %s !\n", name);
}
void saveToFile(Student students[], int count, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("打开文件失败!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s\n", students[i].name, students[i].password);
    }
    fclose(file);
    printf("数据已经成功保存到文件!\n");
}
void loadFromFile(Student students[], int* count, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("打开文件失败!\n");
        return;
    }
    while (fscanf(file, "%49s %49s", students[*count].name, students[*count].password) != EOF && *count < MAX_STUDENTS) {
        (*count)++;
    }
    fclose(file);
    printf("数据已成功在文件中加载!\n");
}

void OpenFile(const Student* students, int count) {
    if (count == 0) {
        printf("没有用户信息。\n");
        return;
    }
    for (int i = 0; i < count; ++i) {
        printf("用户名: %s, 密码: %s, 姓名: %s\n", students[i].name, students[i].password, students[i].name);
    }
}
void manager_Open() {
    Student students[MAX_STUDENTS];
    int count = 0;
    char filename[] = "用户信息.txt";
    int choice;
    char name[NAME_LEN];
    loadFromFile(students, &count, filename);
    do {
        printf("\n1. 查看用户\n");
        printf("2. 增加用户\n");
        printf("3. 删除用户\n");
        printf("4. 更新用户\n");
        printf("5. 查找用户\n");
        printf("6. 保存并退出\n");
        printf("请输入你的选择: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            OpenFile(students, count);
            break;
        case 2:
            addStudent(students, &count);
            break;
        case 3:
            printf("请输入需要删除的用户名: ");
            scanf("%49s", name);
            deleteStudent(students, &count, name);
            break;
        case 4:
            printf("请输入需要修改的用户名: ");
            scanf("%49s", name);
            updateStudent(students, count, name);
            break;
        case 5:
            printf("请输入需要查找的用户名: ");
            scanf("%49s", name);
            searchStudent(students, count, name);
            break;
        case 6:
            saveToFile(students, count, filename);
            break;
        default:
            printf("错误的选择，请再选择一次\n");
        }
    } while (choice != 6);
}

int main() {
    manager_Open();
    return 0;
}