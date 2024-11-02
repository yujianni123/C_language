#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <graphics.h> // ����ͼ�ο⣬����һ����management guy
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include "Management.h"
#include "Window.h"
#define MAX_STUDENTS 100
#define NAME_LEN 50
#pragma comment(lib, "winmm.lib")
#pragma warning(disable: 4996)

typedef struct {
    char name[NAME_LEN];
    char password[NAME_LEN];
} Student;

void registerManager();
void loginManager();
void registerUser();
void loginUser();
void loadFromFile(Student students[], int* count, const char* filename);
void saveToFile(Student students[], int count, const char* filename);
void addStudent(Student students[], int* count);
void deleteStudent(Student students[], int* count, char name[NAME_LEN]);
void updateStudent(Student students[], int count, char name[NAME_LEN]);
void searchStudent(Student students[], int count, char name[NAME_LEN]);
void OpenFile(const Student* students, int count);



struct Resource {
    IMAGE img_start[3]; // ����һ������
    IMAGE img_loginSubPage[3]; // user�˵���ת����ҳ��
    IMAGE img_display[5]; // ��Ʒչʾҳ��
    IMAGE img_query;      //�û���ѯҳ��
    IMAGE img_requery;    //����Ա����ҳ��
} res; // ��ʼ����Դ

void res_init(struct Resource* res) {
    // ������������ͼƬ
    for (int i = 0; i < 3; i++) {
        char path[50] = { 0 };
        sprintf_s(path, "����0%d.jpg", i + 1);
        loadimage(&res->img_start[i], path, getwidth(), getheight());
    }

    // ������ƷչʾͼƬ
    for (int i = 0; i < 5; i++) {
        char path[50] = { 0 };
        sprintf_s(path, "��Ʒ0%d.jpg", i + 1);
        loadimage(&res->img_display[i], path, getwidth(), getheight());
    }

    // ����user��ҳ
    loadimage(&res->img_loginSubPage[0], "�û�����.jpg", getwidth(), getheight());
    loadimage(&res->img_loginSubPage[1], "����Ա����.jpg", getwidth(), getheight());
    loadimage(&res->img_loginSubPage[2], "��Ʒչʾ����.jpg", getwidth(), getheight());

    //�����û���ѯҳ��͹���Ա����ҳ��
    loadimage(&res->img_query, "�û���ѯ����.jpg", getwidth(), getheight());
    loadimage(&res->img_requery, "�����߲�������.jpg", getwidth(), getheight());
}

// ����Ƿ���ĳ������
bool isInRect(ExMessage* msg, int x, int y, int w, int h) {
    return (msg->x > x && msg->x < x + w && msg->y > y && msg->y < y + h);
}

enum MenuOp {
    user,     // �û���¼
    manager,  // �����¼
    display,  // ��Ʒչʾҳ��
    Home,
    query,   //�û���ѯҳ��
    requery   //����Ա����ҳ��
};

enum Display {
    work1,     //��һ����Ʒ
    work2,     //�ڶ�����Ʒ
    work3,     //��������Ʒ
    work4,     //���ĸ���Ʒ
    work5,     //�������Ʒ
    display1
};

enum MenuOp menuState = Home;
enum Display menuState1 = display1;
int which = 0;

void manager_Open() {
    Student students[MAX_STUDENTS];
    int count = 0;
    char filename[] = "�û���Ϣ.txt";
    loadFromFile(students, &count, filename);
    menuState = requery; // ���ò˵�״̬Ϊ����Ա����ҳ��
}

void startupScene(ExMessage* msg) {
    if (msg->message == WM_LBUTTONDOWN) { // ����������л�����
        if (which++ < 3 - 1) {
            // �л���������
        }
        else if (menuState == Home) {
            if (isInRect(msg, 550, 310, 180, 56)) {
                menuState = user;
            }
            else if (isInRect(msg, 550, 410, 180, 56)) {
                menuState = manager;
            }
            else if (isInRect(msg, 500, 510, 180, 56)) {
                menuState = display;
            }
        }
        else {
            switch (menuState) {
            case user:
                // ����Home
                if (isInRect(msg, 10, 10, 100, 100)) {
                    menuState = Home;
                    which = 2;
                }
                // �û�����
                else if (isInRect(msg, 550, 410, 180, 56)) {
                    registerUser();
                    if (menuState == query)
                    {
                        if (isInRect(msg, 10, 10, 100, 100)) {
                            menuState = user;
                            which = 3;
                        }
                    }
                }
                else if (isInRect(msg, 550, 310, 180, 56)) {
                    loginUser();
                    if (menuState == query)
                    {
                        if (isInRect(msg, 10, 10, 100, 100)) {
                            menuState = user;
                            which = 3;
                        }
                    }
                }
                break;
            case manager:
                if (isInRect(msg, 10, 10, 100, 100)) {
                    menuState = Home;
                    which = 2;
                }
                // �����ߵ�¼���� 
                else if (isInRect(msg, 550, 410, 180, 56)) {
                    registerManager();
                    if (menuState == requery)
                    {
                        if (isInRect(msg, 10, 10, 100, 100)) {
                            menuState = manager;
                            which = 3;
                        }
                    }
                }
                else if (isInRect(msg, 550, 310, 180, 56)) {
                    loginManager();
                    if (menuState == requery)
                    {
                        if (isInRect(msg, 10, 10, 100, 100)) {
                            menuState = manager;
                            which = 3;
                        }
                    }
                    break;
            case display:
                if (isInRect(msg, 10, 10, 100, 100)) {
                    if (menuState1 == display1) {
                        // ����Ʒչʾ���淵�ص�����03.jpg
                        menuState = Home;
                        which = 2;
                    }
                    else {
                        // ����Ʒ01-05���ص���Ʒչʾ����
                        menuState1 = display1;
                    }
                }
                else {
                    if (which++ < 5 - 1) {
                        // �л�չʾ����
                    }
                    else if (menuState1 == display1) {
                        if (isInRect(msg, 240, 280, 180, 100)) {
                            menuState1 = work1;//ok
                        }
                        else if (isInRect(msg, 500, 280, 180, 100)) {
                            menuState1 = work2;
                        }
                        else if (isInRect(msg, 700, 280, 180, 100)) {
                            menuState1 = work3;
                        }
                        else if (isInRect(msg, 450, 610, 180, 100)) {

                            menuState1 = work4;//ok
                        }
                        else if (isInRect(msg, 650, 580, 180, 100)) {
                            menuState1 = work5;
                        }
                    }
                    else {
                        switch (menuState1) {
                        case work1:
                            // ����display
                            if (isInRect(msg, 10, 10, 100, 100)) {
                                menuState1 = display1;
                                which = 4;
                            }
                            break;
                        case work2:
                            if (isInRect(msg, 10, 10, 100, 100)) {
                                menuState1 = display1;
                                which = 4;
                            }
                            break;
                        case work3:
                            if (isInRect(msg, 10, 10, 100, 100)) {
                                menuState1 = display1;
                                which = 4;
                            }
                            break;
                        case work4:
                            if (isInRect(msg, 10, 10, 100, 100)) {
                                menuState1 = display1;
                                which = 4;
                            }
                            break;
                        case work5:
                            if (isInRect(msg, 10, 10, 100, 100)) {
                                menuState1 = display1;
                                which = 4;
                            }
                            break;
                        }
            case query:

            {
                if (isInRect(msg, 10, 10, 100, 100)) {
                    menuState = user;
                    which = 3;
                }


                break;
            }
            case requery:
                Student students[MAX_STUDENTS];
                int count = 0; // �ƶ��� case �ⲿ����ڴ�������
                char filename[] = "�û���Ϣ.txt"; // �ƶ��� case �ⲿ����ڴ�������
                int choice;
                char name[NAME_LEN];
                loadFromFile(students, &count, filename);

                {
                    if (isInRect(msg, 10, 10, 100, 100)) {
                        menuState = manager;
                        which = 3;
                    }

                    else {
                        Window w(1220, 860, EW_SHOWCONSOLE);
                        w.setWindowTilte("����Ա����ҳ��");
                        Management m;
                        m.run();
                        /*return w.exec();*/
                        // �����������ͳ�ʼ�����ڿ���
                        /*{*/
                            /*Student students[MAX_STUDENTS];
                            int count = 0;
                            char filename[] ="�û���Ϣ.txt";
                            int choice;
                            char name[NAME_LEN];
                            loadFromFile(students, &count, filename);

                            if (isInRect(msg, 510, 210, 180, 56)) {
                                printf("�Ѵ��û���Ϣ��");
                                OpenFile(students, count);
                            }
                            else if (isInRect(msg, 510, 310, 180, 56)) {
                                printf("��������Ҫ�����û�: ");
                                scanf("%49s", name);
                                addStudent(students, &count);
                            }
                            else if (isInRect(msg, 510, 390, 180, 56)) {
                                printf("��������Ҫɾ�����û���: ");
                                scanf("%49s", name);
                                deleteStudent(students, &count, name);
                            }
                            else if (isInRect(msg, 510, 460, 180, 56)) {
                                printf("��������Ҫ���ҵ��û���: ");
                                scanf("%49s", name);
                                searchStudent(students, count, name);
                            }
                            else if (isInRect(msg, 510, 530, 180, 56)) {
                                printf("��������Ҫ�޸ĵ��û���: ");
                                scanf("%49s", name);
                                updateStudent(students, count, name);
                            }

                            else if (isInRect(msg, 400, 690, 180, 56)) {
                                saveToFile(students, count, "�û���Ϣ.txt");
                            }
                            else if (isInRect(msg, 400, 790, 180, 56)) {
                                loadFromFile(students, &count, "�û���Ϣ.txt");
                            }*/
                            /*}*/
                    }
                }
                break;

                    }
                }
                break;
                }
            }
        }
        printf("state:%d which:%d state1:%d \n", menuState, which, menuState1);
    }
    // ����ͼƬ
    if (which < 3) {
        putimage(0, 0, &res.img_start[which]);
    }
    else if (menuState == display) {
        if (menuState1 == display1) {
            // ��ʾ��Ʒչʾ����.jpg
            putimage(0, 0, &res.img_loginSubPage[2]);
        }
        else {
            // ��ʾ��Ӧ����ƷͼƬ
            putimage(0, 0, &res.img_display[menuState1 - work1]);
        }
    }
    else if (menuState == user) {
        putimage(0, 0, &res.img_loginSubPage[0]);
    }
    else if (menuState == query) {
        putimage(0, 0, &res.img_query);
    }
    else if (menuState == requery) {
        Window w(1220, 860, EW_SHOWCONSOLE);
        w.setWindowTilte("����Ա����ҳ��");
        Management m;
        m.run(); // ȷ��������ʾ���ǹ���Ա��������
    }
    else {
        putimage(0, 0, &res.img_loginSubPage[menuState]);
    }
}

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

Manager managers[100]; // �洢������Ա��Ϣ������
int managerCount = 0; // ������Ա����

User users[100]; // �洢�û���Ա��Ϣ������
int userCount = 0; // �û���Ա����

//��������
void readPassword(char* password, int size) {
    char* ptr = password;
    int ch;
    while ((ch = _getch()) != '\r') {  // �س�����������
        if (ch == '\b' && ptr > password) {  // �˸��
            ptr--;
            printf("\b \b");  // �����˸�
        }
        else if (ch >= ' ' && ptr < password + size - 1) {
            *ptr++ = ch;
            printf("*");  // ���ǺŴ���ʵ���ַ�
        }
    }
    *ptr = '\0';  // ȷ���ַ����Կ��ַ���β
}

void registerManager() {
    printf("ע�����Ա:\n");
    printf("��������: ");
    scanf("%19s", managers[managerCount].name);
    while (getchar() != '\n');  // ������뻺����
    printf("�����û���: ");
    scanf("%19s", managers[managerCount].username);
    while (getchar() != '\n');  // ������뻺����
    printf("��������: ");
    readPassword(managers[managerCount].password, 20);
    managers[managerCount].password[19] = '\0';  // ȷ�����ᳬ������
    managerCount++;

    // ���浽�ļ�
    FILE* file = fopen("����Ա��Ϣ.txt", "a");
    if (file == NULL) {
        printf("�ļ���ʧ�ܡ�\n");
        return;
    }
    fprintf(file, "%s %s %s\n", managers[managerCount - 1].name, managers[managerCount - 1].username, managers[managerCount - 1].password);
    fclose(file);
    printf("ע��ɹ������ص�¼ҳ�档\n");
    menuState = manager;
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
    while (fgets(line, sizeof(line), file)) {
        char name[20], usernameFromFile[20], passwordFromFile[20];
        sscanf(line, "%19s %19s %19s", name, usernameFromFile, passwordFromFile);
        if (strcmp(usernameFromFile, username) == 0 && strcmp(passwordFromFile, password) == 0) {
            printf("��¼�ɹ�����ת������ҳ�档\n");
            menuState = requery;
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("�û������������\n");
}



void registerUser() {
    printf("ע���û�:\n");
    char name[20];
    char username[20];
    char password[20]; // ����һ���ֲ��������洢����

    printf("��������: ");
    scanf("%19s", name);
    while (getchar() != '\n');  // ������뻺����

    printf("�����û���: ");
    scanf("%19s", username);
    while (getchar() != '\n');  // ������뻺����

    printf("��������: ");
    readPassword(password, 19);  // ʹ�� readPassword �����ڵ���������
    password[19] = '\0';  // ȷ�����ᳬ������

    // �����û���Ϣ���浽������ļ���
    strcpy(users[userCount].name, name);
    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    userCount++;

    // ���浽�ļ�
    FILE* file = fopen("�û���Ϣ.txt", "a");
    if (file == NULL) {
        printf("�ļ���ʧ�ܡ�\n");
        return;
    }
    fprintf(file, "%s %s %s\n", users[userCount - 1].name, users[userCount - 1].username, users[userCount - 1].password);
    fclose(file);
    printf("ע��ɹ������ص�¼ҳ�档\n");
    menuState = user; // ע��ɹ�����ת����¼ҳ��
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
    while (fgets(line, sizeof(line), file)) {
        char name[20], usernameFromFile[20], passwordFromFile[20];
        sscanf(line, "%19s %19s %19s", name, usernameFromFile, passwordFromFile);
        if (strcmp(usernameFromFile, username) == 0 && strcmp(passwordFromFile, password) == 0) {
            printf("��¼�ɹ�����ת���û�ҳ�档\n");
            menuState = query;
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("�û������������\n");
}

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
    saveToFile(students, *count, "�û���Ϣ.txt"); // �������ݵ��ļ�
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
    saveToFile(students, *count, "�û���Ϣ.txt"); // �������ݵ��ļ�
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
    printf("�û���Ϣ���³ɹ�!\n");
    saveToFile(students, count, "�û���Ϣ.txt"); // �������ݵ��ļ�
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
    /*printf("�����Ѿ��ɹ����浽�ļ�!\n");*/
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
    /*printf("�����ѳɹ����ļ��м���!\n");*/
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



int main() {
    // ��������
    initgraph(1220, 860, EW_SHOWCONSOLE);
    res_init(&res);


    // ��ʼ��ѧ������
    Student students[MAX_STUDENTS];
    int count = 0;
    loadFromFile(students, &count, "�û���Ϣ.txt");


    while (true) {
        setbkcolor(WHITE); // ���ñ�����ɫ
        settextstyle(30, 0, "����"); // ��������
        settextcolor(BLACK);
        ExMessage msg; // ������Ϣ�����ϵػ�ȡ�����Ϣ���������Ϣ����true�����򷵻�false
        while (peekmessage(&msg, EM_MOUSE)) {
            startupScene(&msg);
        }

        outtextxy(500, 10, _T("�մ��Ļ�����ϵͳ"));
        settextstyle(20, 0, "����"); // ��������
        outtextxy(400, 700, _T("������,��С������˫��,����ԭ,��¶¶��ͬ���"));
    }



    // ��������
    getchar(); // ���������������ֹ����
    closegraph(); // �رջ�ͼ����
    return 0;
}