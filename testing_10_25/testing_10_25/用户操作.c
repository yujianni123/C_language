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
char filename[] = "�û���Ϣ.txt";
int choice;
char name[NAME_LEN];

Manager managers[100];
int managerCount = 0;

User users[100];
int userCount = 0;

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
}

void loadFromFile(Student students[], int* count, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("���ļ�ʧ��!\n");
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
    printf("ע�����Ա:\n");
    printf("��������: ");
    scanf("%19s", managers[managerCount].name);
    while (getchar() != '\n');
    printf("�����û���: ");
    scanf("%19s", managers[managerCount].username);
    while (getchar() != '\n');
    printf("��������: ");
    readPassword(managers[managerCount].password, 20);
    managers[managerCount].password[19] = '\0';
    managerCount++;

    FILE* file = fopen("����Ա��Ϣ.txt", "a");
    if (file == NULL) {
        printf("�ļ���ʧ�ܡ�\n");
        return;
    }
    fprintf(file, "%s %s %s\n", managers[managerCount - 1].name, managers[managerCount - 1].username, managers[managerCount - 1].password);
    fclose(file);
    printf("ע��ɹ������ص�¼ҳ�档\n");
}

void loginManager() {
    printf("�����¼:\n");
    char username[20];
    printf("�����û���: ");
    scanf("%19s", username);
    while (getchar() != '\n');  // ������뻺����
    char password[20];  // ����һ���ֲ��������洢����
    printf("��������: ");
    readPassword(password, 19);
    password[19] = '\0';  // ȷ�����ᳬ������

    // ���ļ��ж�ȡ��Ϣ
    FILE* file = fopen("����Ա��Ϣ.txt", "r");
    if (file == NULL) {
        printf("�ļ���ʧ�ܡ�\n");
        return;
    }
    char line[100];
    int logged = 0;
    while (fgets(line, sizeof(line), file)) {
        char name[20], usernameFromFile[20], passwordFromFile[20];
        sscanf(line, "%19s %19s %19s", name, usernameFromFile, passwordFromFile);
        if (strcmp(usernameFromFile, username) == 0 && strcmp(passwordFromFile, password) == 0) {
            printf("��¼�ɹ�����ת������ҳ�档\n");
            logged = 1;
            break;
        }
    }
    fclose(file);
    if (!logged) {
        printf("�û������������\n");
    }
    else if (logged) {
        mainMenu();  // ��¼�ɹ������ mainMenu
    }
}

void registerUser() {
    printf("ע���û�:\n");
    char name[20];
    char username[20];
    char password[20];

    printf("��������: ");
    scanf("%19s", name);
    while (getchar() != '\n');
    printf("�����û���: ");
    scanf("%19s", username);
    while (getchar() != '\n');
    printf("��������: ");
    readPassword(password, 19);
    password[19] = '\0';

    strcpy(users[userCount].name, name);
    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    userCount++;

    FILE* file = fopen("�û���Ϣ.txt", "a");
    if (file == NULL) {
        printf("�ļ���ʧ�ܡ�\n");
        return;
    }
    fprintf(file, "%s %s %s\n", users[userCount - 1].name, users[userCount - 1].username, users[userCount - 1].password);
    fclose(file);
    printf("ע��ɹ������ص�¼ҳ�档\n");
}

void loginUser() {
    printf("�û���¼:\n");
    char username[20];
    char password[20]; // ����һ���ֲ��������洢����

    printf("�����û���: ");
    scanf("%19s", username);
    while (getchar() != '\n');  // ������뻺����

    printf("��������: ");
    readPassword(password, 19);  // ʹ�� readPassword �����ڵ���������
    password[19] = '\0';  // ȷ�����ᳬ������

    // ���ļ��ж�ȡ��Ϣ
    FILE* file = fopen("�û���Ϣ.txt", "r");
    if (file == NULL) {
        printf("�ļ���ʧ�ܡ�\n");
        return;
    }
    char line[100];
    int logged = 0;
    while (fgets(line, sizeof(line), file)) {
        char name[20], usernameFromFile[20], passwordFromFile[20];
        sscanf(line, "%19s %19s %19s", name, usernameFromFile, passwordFromFile);
        if (strcmp(usernameFromFile, username) == 0 && strcmp(passwordFromFile, password) == 0) {
            printf("��¼�ɹ�����ת���û�ҳ�档\n");
            logged = 1;
            break;
        }
    }
    fclose(file);
    if (!logged) {
        printf("�û������������\n");
    }
    else if (logged) {
        mainMenu();  // ��¼�ɹ������ mainMenu
    }
}

void showCeramics() {
    FILE* fp = fopen("�մ���Ϣ.txt", "r");
    if (fp == NULL) {
        printf("�޷����մ��ļ���\n");
        return;
    }

    char line[256]; // ����ÿ�в�����255���ַ�
    while (fgets(line, sizeof(line), fp) != NULL) {
        // ȥ�����з�
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
    printf("�������մ�����: ");
    scanf_s("%49s", name, sizeof(name));

    FILE* fp = fopen("�մ���Ϣ.txt", "r");
    if (fp == NULL) {
        printf("�޷����մ��ļ���\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        char ceramicName[50], author[50], history[200], famousWorks[100][50];
        sscanf(line, "%49[^,],%49[^,],%199[^,],%49[^\n]", ceramicName, author, history, famousWorks[0]);
        if (strcmp(ceramicName, name) == 0) {
            printf("\n�ҵ��մ�: %s\n", ceramicName);
            printf("����: %s\n", author);
            printf("��ʷ: %s\n", history);
            printf("������Ʒ: %s\n", famousWorks[0]);
            break;
        }
    }

    fclose(fp);
}

void searchByAuthor() {
    char author[50];
    printf("��������������: ");
    scanf_s("%49s", author, sizeof(author));

    FILE* fp = fopen("�մ���Ϣ.txt", "r");
    if (fp == NULL) {
        printf("�޷����մ��ļ���\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        char ceramicName[50], authorName[50], history[200], famousWorks[100][50];
        sscanf(line, "%49[^,],%49[^,],%199[^,],%49[^\n]", ceramicName, authorName, history, famousWorks[0]);
        if (strcmp(authorName, author) == 0) {
            printf("\n�ҵ��մ�: %s\n", ceramicName);
            printf("����: %s\n", authorName);
            printf("��ʷ: %s\n", history);
            printf("������Ʒ: %s\n", famousWorks[0]);
            break;
        }
    }

    fclose(fp);
}

void loginMenu() {
    int choice;
    do {
        printf("\n��ѡ���¼����:\n");
        printf("1. ����Ա��¼\n");
        printf("2. ����Աע��\n");
        printf("3. �û���¼\n");
        printf("4. �û�ע��\n");
        printf("0. ע��\n");
        printf("��ѡ��: ");
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
            printf("ע��ϵͳ��\n");
            break;
        default:
            printf("��Чѡ�����������롣\n");
        }
    } while (choice != 0);
}
void mainMenu() {
    int choice = 0;
    do {
        printf("\n�մɹ���ϵͳ\n");
        printf("1. չʾ�����մ�\n");
        printf("2. ���մ����Ʋ�ѯ\n");
        printf("3. �����߲�ѯ\n");
        printf("0. �˳�\n");
        printf("��ѡ�����: ");
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
            printf("�˳�ϵͳ��\n");
            break;
        default:
            printf("��Чѡ�����������롣\n");
        }
    } while (choice != 0);
}

int main() {
    // ������Ҫֱ�ӵ���ע��͵�¼����
    // ֱ����ʾ��¼�˵�
    loginMenu();
  
}