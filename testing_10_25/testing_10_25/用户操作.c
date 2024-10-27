#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#define MAX_STUDENTS 100
#define NAME_LEN 50
void mainMenu();

typedef struct {
    char name[NAME_LEN];
    char password[NAME_LEN];
} Student;

typedef struct {
    char zhanghao[20];
    char mima[20];
} user;

typedef struct {
    char name[50];
    char author[50];
    char history[200];
    char famousWorks[100][50];
} Ceramic;

typedef struct {
    char name[20];
    char username[20];
    char password[20];
} Manager;

typedef struct {
    char name[20];
    char username[20];
    char password[20];
} User;

Student students[MAX_STUDENTS];
int count = 0;
char filename[] = "用户信息.txt";
int choice;
char name[NAME_LEN];

Manager managers[100];
int managerCount = 0;

User users[100];
int userCount = 0;

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
}

void loadFromFile(Student students[], int* count, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("打开文件失败!\n");
        return;
    }
    while (fscanf(file, "%49s %49s", students[*count].name, students[*count].password) != EOF) {
        (*count)++;
        if (*count >= MAX_STUDENTS) break;
    }
    fclose(file);
}

void readPassword(char* password, int size) {
    char* ptr = password;
    int ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b' && ptr > password) {
            ptr--;
            printf("\b \b");
        }
        else if (ch >= ' ' && ptr < password + size - 1) {
            *ptr++ = ch;
            printf("*");
        }
    }
    *ptr = '\0';
}

void registerManager() {
    printf("注册管理员:\n");
    printf("输入姓名: ");
    scanf("%19s", managers[managerCount].name);
    while (getchar() != '\n');
    printf("输入用户名: ");
    scanf("%19s", managers[managerCount].username);
    while (getchar() != '\n');
    printf("输入密码: ");
    readPassword(managers[managerCount].password, 20);
    managers[managerCount].password[19] = '\0';
    managerCount++;

    FILE* file = fopen("管理员信息.txt", "a");
    if (file == NULL) {
        printf("文件打开失败。\n");
        return;
    }
    fprintf(file, "%s %s %s\n", managers[managerCount - 1].name, managers[managerCount - 1].username, managers[managerCount - 1].password);
    fclose(file);
    printf("注册成功，返回登录页面。\n");
}

void loginManager() {
    printf("管理登录:\n");
    char username[20];
    printf("输入用户名: ");
    scanf("%19s", username);
    while (getchar() != '\n');  // 清除输入缓冲区
    char password[20];  // 声明一个局部变量来存储密码
    printf("输入密码: ");
    readPassword(password, 19);
    password[19] = '\0';  // 确保不会超出界限

    // 从文件中读取信息
    FILE* file = fopen("管理员信息.txt", "r");
    if (file == NULL) {
        printf("文件打开失败。\n");
        return;
    }
    char line[100];
    int logged = 0;
    while (fgets(line, sizeof(line), file)) {
        char name[20], usernameFromFile[20], passwordFromFile[20];
        sscanf(line, "%19s %19s %19s", name, usernameFromFile, passwordFromFile);
        if (strcmp(usernameFromFile, username) == 0 && strcmp(passwordFromFile, password) == 0) {
            printf("登录成功，跳转到管理页面。\n");
            logged = 1;
            break;
        }
    }
    fclose(file);
    if (!logged) {
        printf("用户名或密码错误。\n");
    }
    else if (logged) {
        mainMenu();  // 登录成功后调用 mainMenu
    }
}

void registerUser() {
    printf("注册用户:\n");
    char name[20];
    char username[20];
    char password[20];

    printf("输入姓名: ");
    scanf("%19s", name);
    while (getchar() != '\n');
    printf("输入用户名: ");
    scanf("%19s", username);
    while (getchar() != '\n');
    printf("输入密码: ");
    readPassword(password, 19);
    password[19] = '\0';

    strcpy(users[userCount].name, name);
    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    userCount++;

    FILE* file = fopen("用户信息.txt", "a");
    if (file == NULL) {
        printf("文件打开失败。\n");
        return;
    }
    fprintf(file, "%s %s %s\n", users[userCount - 1].name, users[userCount - 1].username, users[userCount - 1].password);
    fclose(file);
    printf("注册成功，返回登录页面。\n");
}

void loginUser() {
    printf("用户登录:\n");
    char username[20];
    char password[20]; // 增加一个局部变量来存储密码

    printf("输入用户名: ");
    scanf("%19s", username);
    while (getchar() != '\n');  // 清除输入缓冲区

    printf("输入密码: ");
    readPassword(password, 19);  // 使用 readPassword 函数遮挡密码输入
    password[19] = '\0';  // 确保不会超出界限

    // 从文件中读取信息
    FILE* file = fopen("用户信息.txt", "r");
    if (file == NULL) {
        printf("文件打开失败。\n");
        return;
    }
    char line[100];
    int logged = 0;
    while (fgets(line, sizeof(line), file)) {
        char name[20], usernameFromFile[20], passwordFromFile[20];
        sscanf(line, "%19s %19s %19s", name, usernameFromFile, passwordFromFile);
        if (strcmp(usernameFromFile, username) == 0 && strcmp(passwordFromFile, password) == 0) {
            printf("登录成功，跳转到用户页面。\n");
            logged = 1;
            break;
        }
    }
    fclose(file);
    if (!logged) {
        printf("用户名或密码错误。\n");
    }
    else if (logged) {
        mainMenu();  // 登录成功后调用 mainMenu
    }
}

void showCeramics() {
    FILE* fp = fopen("陶瓷信息.txt", "r");
    if (fp == NULL) {
        printf("无法打开陶瓷文件！\n");
        return;
    }

    char line[256]; // 假设每行不超过255个字符
    while (fgets(line, sizeof(line), fp) != NULL) {
        // 去除换行符
        char* pos = strchr(line, '\n');
        if (pos) {
            *pos = '\0';
        }
        printf("%s\n", line);
    }

    fclose(fp);
}

void searchByName() {
    char name[50];
    printf("请输入陶瓷名称: ");
    scanf_s("%49s", name, sizeof(name));

    FILE* fp = fopen("陶瓷信息.txt", "r");
    if (fp == NULL) {
        printf("无法打开陶瓷文件！\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        char ceramicName[50], author[50], history[200], famousWorks[100][50];
        sscanf(line, "%49[^,],%49[^,],%199[^,],%49[^\n]", ceramicName, author, history, famousWorks[0]);
        if (strcmp(ceramicName, name) == 0) {
            printf("\n找到陶瓷: %s\n", ceramicName);
            printf("作者: %s\n", author);
            printf("历史: %s\n", history);
            printf("著名作品: %s\n", famousWorks[0]);
            break;
        }
    }

    fclose(fp);
}

void searchByAuthor() {
    char author[50];
    printf("请输入作者名称: ");
    scanf_s("%49s", author, sizeof(author));

    FILE* fp = fopen("陶瓷信息.txt", "r");
    if (fp == NULL) {
        printf("无法打开陶瓷文件！\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        char ceramicName[50], authorName[50], history[200], famousWorks[100][50];
        sscanf(line, "%49[^,],%49[^,],%199[^,],%49[^\n]", ceramicName, authorName, history, famousWorks[0]);
        if (strcmp(authorName, author) == 0) {
            printf("\n找到陶瓷: %s\n", ceramicName);
            printf("作者: %s\n", authorName);
            printf("历史: %s\n", history);
            printf("著名作品: %s\n", famousWorks[0]);
            break;
        }
    }

    fclose(fp);
}

void loginMenu() {
    int choice;
    do {
        printf("\n请选择登录类型:\n");
        printf("1. 管理员登录\n");
        printf("2. 管理员注册\n");
        printf("3. 用户登录\n");
        printf("4. 用户注册\n");
        printf("0. 注销\n");
        printf("请选择: ");
        scanf_s("%d", &choice, sizeof(choice));

        switch (choice) {
        case 1:
            loginManager();
            break;
        case 2:
            registerManager();
            break;
        case 3:
            loginUser();
            break;
        case 4:
            registerUser();
            break;
        case 0:
            printf("注销系统。\n");
            break;
        default:
            printf("无效选择，请重新输入。\n");
        }
    } while (choice != 0);
}
void mainMenu() {
    int choice = 0;
    do {
        printf("\n陶瓷管理系统\n");
        printf("1. 展示所有陶瓷\n");
        printf("2. 按陶瓷名称查询\n");
        printf("3. 按作者查询\n");
        printf("0. 退出\n");
        printf("请选择操作: ");
        scanf_s("%d", &choice, sizeof(choice));

        switch (choice) {
        case 1:
            showCeramics();
            break;
        case 2:
            searchByName();
            break;
        case 3:
            searchByAuthor();
            break;
        case 0:
            printf("退出系统。\n");
            break;
        default:
            printf("无效选择，请重新输入。\n");
        }
    } while (choice != 0);
}

int main() {
    // 不再需要直接调用注册和登录函数
    // 直接显示登录菜单
    loginMenu();
  
}