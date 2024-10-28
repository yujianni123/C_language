#define _CRT_SECURE_NO_WARNINGS 1
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    char password[NAME_LEN];
} Student;

Student students[MAX_STUDENTS];
int count = 0;
char filename[] = "用户信息.txt";

struct Resource {
    IMAGE img_background;
    IMAGE img_button;
    IMAGE img_input;
} res;

void initResources() {
    loadimage(&res.img_background, _T("background.jpg"), getwidth(), getheight());
    loadimage(&res.img_button, _T("button.jpg"), 100, 50);
    loadimage(&res.img_input, _T("input.jpg"), 200, 30);
}

void drawBackground() {
    putimage(0, 0, &res.img_background);
}

void drawButton(int x, int y, const char* text, bool active) {
    if (active) {
        putimage(x, y, &res.img_button);
    }
    else {
        setfillcolor(LIGHTGRAY);
        bar(x, y, x + 100, y + 50);
    }
    settextstyle(16, 0, _T("Arial"));
    settextcolor(BLACK);
    outtextxy(x + 10, y + 10, text);
}

void drawInput(int x, int y, const char* placeholder) {
    putimage(x, y, &res.img_input);
    settextstyle(16, 0, _T("Arial"));
    settextcolor(BLACK);
    outtextxy(x + 10, y + 5, placeholder);
}

void registerUser() {
    char name[NAME_LEN], password[NAME_LEN];
    drawInput(200, 200, "姓名:");
    drawInput(200, 250, "密码:");
    _getch();
    scanf("%49s", name);
    _getch();
    scanf("%49s", password);

    Student newStudent = { name, password };
    strcpy(students[count].name, newStudent.name);
    strcpy(students[count].password, newStudent.password);
    count++;

    saveToFile();
    outtextxy(200, 300, "用户注册成功！");
}

void loginUser() {
    char username[NAME_LEN], password[NAME_LEN];
    drawInput(200, 200, "用户名:");
    drawInput(200, 250, "密码:");
    _getch();
    scanf("%49s", username);
    _getch();
    scanf("%49s", password);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, username) == 0 && strcmp(students[i].password, password) == 0) {
            outtextxy(200, 300, "登录成功！");
            found = 1;
            break;
        }
    }
    if (!found) {
        outtextxy(200, 300, "用户名或密码错误！");
    }
}

void displayStudents() {
    for (int i = 0; i < count; i++) {
        outtextxy(200, 200 + i * 20, "%s", _T("students[i].name"));
    }
}

void saveToFile() {
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

void loadFromFile() {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("打开文件失败!\n");
        return;
    }
    count = 0;
    while (fscanf(file, "%49s %49s", students[count].name, students[count].password) != EOF) {
        count++;
        if (count >= MAX_STUDENTS) break;
    }
    fclose(file);
}

int main() {
    initgraph(800, 600);
    initResources();

    loadFromFile();

    while (true) {
        drawBackground();

        // 绘制按钮
        drawButton(200, 100, "注册用户", true);
        drawButton(200, 150, "用户登录", true);
        drawButton(200, 200, "显示所有用户", true);

        // 检查鼠标事件
        if (ismouselick(WM_LBUTTONDOWN)) {
            int x = getmouseclick(WM_LBUTTONDOWN).x;
            int y = getmouseclick(WM_LBUTTONDOWN).y;
            if (x > 200 && x < 300 && y > 100 && y < 150) {
                registerUser();
            }
            else if (x > 200 && x < 300 && y > 150 && y < 200) {
                loginUser();
            }
            else if (x > 200 && x < 300 && y > 200 && y < 250) {
                displayStudents();
            }
        }

        // 延时
        Sleep(100);
        cleardevice();
    }

    closegraph();
    return 0;
}