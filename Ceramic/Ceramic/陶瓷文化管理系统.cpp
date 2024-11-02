#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <graphics.h> // ，创建一个类management guy
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>引用图形库
#include <string.h>
#include <iostream>
#include <vector>
#include "Management.h"
#include "Window.h"
#include "Table.h"
#include "gui_simple.h"
#include <map>


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
void startupScene(ExMessage* msg);
//void render(void* arg);
//void init(void* arg);
void displayImage(const std::string& imagePath, bool& keepDisplaying);
std::map<std::string, std::string> getCeramicImageMap();


struct Resource {
    IMAGE img_start[3]; // 定义一个数组
    IMAGE img_loginSubPage[3]; // user菜单跳转到的页面
    IMAGE img_display[5]; // 作品展示页面
    IMAGE img_query;      //用户查询页面
    IMAGE img_requery;    //管理员操作页面
} res; // 初始化资源

void res_init(struct Resource* res) {
    // 加载启动界面图片
    for (int i = 0; i < 3; i++) {
        char path[50] = { 0 };
        sprintf_s(path, "背景0%d.jpg", i + 1);
        loadimage(&res->img_start[i], path, getwidth(), getheight());
    }

    // 加载作品展示图片
    for (int i = 0; i < 5; i++) {
        char path[50] = { 0 };
        sprintf_s(path, "作品0%d.jpg", i + 1);
        loadimage(&res->img_display[i], path, getwidth(), getheight());
    }

    // 加载user子页
    loadimage(&res->img_loginSubPage[0], "用户界面.jpg", getwidth(), getheight());
    loadimage(&res->img_loginSubPage[1], "管理员界面.jpg", getwidth(), getheight());
    loadimage(&res->img_loginSubPage[2], "作品展示界面.jpg", getwidth(), getheight());

    //加载用户查询页面和管理员操作页面
    loadimage(&res->img_query, "用户查询界面.jpg", getwidth(), getheight());
    loadimage(&res->img_requery, "管理者操作界面.jpg", getwidth(), getheight());
}

// 鼠标是否处在某个区域
bool isInRect(ExMessage* msg, int x, int y, int w, int h) {
    return (msg->x > x && msg->x < x + w && msg->y > y && msg->y < y + h);
}

enum MenuOp {
    user,     // 用户登录
    manager,  // 管理登录
    display,  // 作品展示页面
    Home,
    query,   //用户查询页面
    requery   //管理员操作页面
};

enum Display {
    work1,     //第一个作品
    work2,     //第二个作品
    work3,     //第三个作品
    work4,     //第四个作品
    work5,     //第五个作品
    display1
};







enum MenuOp menuState = Home;
enum Display menuState1 = display1;
int which = 0;

void manager_Open() {
    Student students[MAX_STUDENTS];
    int count = 0;
    char filename[] = "用户信息.txt";
    loadFromFile(students, &count, filename);
    menuState = requery; // 设置菜单状态为管理员操作页面
}

void startupScene(ExMessage* msg) {
    if (msg->message == WM_LBUTTONDOWN) { // 点击鼠标左键切换画面
        if (which++ < 3 - 1) {
            // 切换启动画面
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
                // 返回Home
                if (isInRect(msg, 10, 10, 100, 100)) {
                    menuState = Home;
                    which = 2;
                }
                // 用户界面
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
                // 管理者登录界面 
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
                        // 从作品展示界面返回到背景03.jpg
                        menuState = Home;
                        which = 2;
                    }
                    else {
                        // 从作品01-05返回到作品展示界面
                        menuState1 = display1;
                    }
                }
                else {
                    if (which++ < 5 - 1) {
                        // 切换展示画面
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
                            // 返回display
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

                else if (menuState == query) {
                    if (isInRect(msg, 10, 10, 100, 100)) {
                        menuState = user;
                        which = 3;
                    }
                    else if (isInRect(msg, 550, 320, 100, 100)) {
                        std::string ceramicName;
                        char continueQuery = 'y';

                        while (continueQuery != 'n') {
                            std::cout << "可查找:紫砂陶 唐三彩 玲珑瓷 唐山骨质瓷 清乾隆粉彩牡丹纹玉壶春瓶 \n粉彩九桃纹天球瓶 清乾隆粉彩百鹿图双耳尊 清宫御用瓷器 瓶 清康熙青花花鸟纹鱼尾瓶\n";
                            std::cout << "请输入瓷器的名字（输入'q'退出）：";
                            std::cin >> ceramicName;

                            if (ceramicName == "q") {
                                break; // 退出循环
                            }

                            std::map<std::string, std::string> ceramicMap = getCeramicImageMap();
                            auto it = ceramicMap.find(ceramicName);
                            if (it != ceramicMap.end()) {
                                bool keepDisplaying = true;
                                displayImage(it->second, keepDisplaying);
                                if (!keepDisplaying) { // 如果按ESC退出，则不继续下面的循环
                                    continue;
                                }
                            }
                            else {
                                std::cout << "没有找到对应的图片。" << std::endl;
                            }

                            std::cout << "是否继续查询？(输入'y'继续，'n'结束查询)：";
                            std::cin >> continueQuery;
                        }
                    }
                }
                break;
            }
            case requery:
                Student students[MAX_STUDENTS];
                int count = 0; // 移动到 case 外部或放在大括号内
                char filename[] = "用户信息.txt"; // 移动到 case 外部或放在大括号内
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
                        w.setWindowTilte("管理员操作页面");
                        Management m;
                        m.run();
                    }
                }
                break;

                    }
                }
                break;
                }
            }
        }
        //printf("state:%d which:%d state1:%d \n", menuState, which, menuState1);
    }

    // 导入图片
    if (which < 3) {
        putimage(0, 0, &res.img_start[which]);
    }
    else if (menuState == display) {
        if (menuState1 == display1) {
            // 显示作品展示界面.jpg
            putimage(0, 0, &res.img_loginSubPage[2]);
        }
        else {
            // 显示对应的作品图片
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
        w.setWindowTilte("管理员操作页面");
        Management m;
        m.run(); // 确保这里显示的是管理员操作界面
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

Manager managers[100]; // 存储管理人员信息的数组
int managerCount = 0; // 管理人员数量

User users[100]; // 存储用户人员信息的数组
int userCount = 0; // 用户人员数量

//隐藏密码
void readPassword(char* password, int size) {
    char* ptr = password;
    int ch;
    while ((ch = _getch()) != '\r') {  // 回车键结束输入
        if (ch == '\b' && ptr > password) {  // 退格键
            ptr--;
            printf("\b \b");  // 回显退格
        }
        else if (ch >= ' ' && ptr < password + size - 1) {
            *ptr++ = ch;
            printf("*");  // 用星号代替实际字符
        }
    }
    *ptr = '\0';  // 确保字符串以空字符结尾
}

void registerManager() {
    printf("注册管理员:\n");
    printf("输入姓名: ");
    scanf("%19s", managers[managerCount].name);
    while (getchar() != '\n');  // 清除输入缓冲区
    printf("输入用户名: ");
    scanf("%19s", managers[managerCount].username);
    while (getchar() != '\n');  // 清除输入缓冲区
    printf("输入密码: ");
    readPassword(managers[managerCount].password, 20);
    managers[managerCount].password[19] = '\0';  // 确保不会超出界限
    managerCount++;

    // 保存到文件
    FILE* file = fopen("管理员信息.txt", "a");
    if (file == NULL) {
        printf("文件打开失败。\n");
        return;
    }
    fprintf(file, "%s %s %s\n", managers[managerCount - 1].name, managers[managerCount - 1].username, managers[managerCount - 1].password);
    fclose(file);
    printf("注册成功，返回登录页面。\n");
    menuState = manager;
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
    while (fgets(line, sizeof(line), file)) {
        char name[20], usernameFromFile[20], passwordFromFile[20];
        sscanf(line, "%19s %19s %19s", name, usernameFromFile, passwordFromFile);
        if (strcmp(usernameFromFile, username) == 0 && strcmp(passwordFromFile, password) == 0) {
            printf("登录成功，跳转到管理页面。\n");
            menuState = requery;
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("用户名或密码错误。\n");
}



void registerUser() {
    Student students[MAX_STUDENTS];
    int count = 0; // 移动到 case 外部或放在大括号内
    char filename[] = "用户信息.txt"; // 移动到 case 外部或放在大括号内
    int choice;
    char name[NAME_LEN];
    loadFromFile(students, &count, filename);
    printf("注册用户:\n");

    char Name[20];
    char username[20];
    char password[20]; // 增加一个局部变量来存储密码

    printf("输入姓名: ");
    scanf("%19s", Name);
    while (getchar() != '\n');  // 清除输入缓冲区

    printf("输入用户名: ");
    scanf("%19s", username);
    while (getchar() != '\n');  // 清除输入缓冲区

    printf("输入密码: ");
    readPassword(password, 19);  // 使用 readPassword 函数遮挡密码输入
    password[19] = '\0';  // 确保不会超出界限

    // 将新用户信息保存到数组和文件中
    strcpy(users[userCount].name, Name);
    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    userCount++;

    // 保存到文件
    FILE* file = fopen("用户信息.txt", "a");
    if (file == NULL) {
        printf("文件打开失败。\n");
        return;
    }
    fprintf(file, "%s %s %s\n", users[userCount - 1].name, users[userCount - 1].username, users[userCount - 1].password);
    fclose(file);
    printf("注册成功，返回登录页面。\n");
    saveToFile(students, count, "用户信息.txt");
    loadFromFile(students, &count, "用户信息.txt");
    menuState = user; // 注册成功后跳转到登录页面
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
    while (fgets(line, sizeof(line), file)) {
        char name[20], usernameFromFile[20], passwordFromFile[20];
        sscanf(line, "%19s %19s %19s", name, usernameFromFile, passwordFromFile);
        if (strcmp(usernameFromFile, username) == 0 && strcmp(passwordFromFile, password) == 0) {
            printf("登录成功，跳转到用户页面。\n");
            menuState = query;
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("用户名或密码错误。\n");
}

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
    saveToFile(students, *count, "用户信息.txt"); // 保存数据到文件
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
    saveToFile(students, *count, "用户信息.txt"); // 保存数据到文件
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
    printf("用户信息更新成功!\n");
    saveToFile(students, count, "用户信息.txt"); // 保存数据到文件
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
    /*printf("数据已经成功保存到文件!\n");*/
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
    /*printf("数据已成功在文件中加载!\n");*/
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



//char username[32];
//char password[32];
//char rePassword[32];
//
//IMAGE img_bg;
//
//void init(void* arg)
//{
//    printf("arg:%p  %d\n", arg, *(int*)(arg));
//    loadimage(&img_bg, "980.jpg", getwidth(), getheight());
//    void loginUser();
//    
//}
//
///** 页面  */
//enum Page
//{
//    Page_Login,//主页面
//    Page_Reg,//注册页面
//    Page_Guanlilogin,//管理员登录页面
//    Page_GuanliHome,//管理员操作页面
//    Page_UserHome,//用户主页面
//    Page_Userlogin,//用户登录页面
//    Page_Image1,
//    Page_Image2,
//    Page_Image3,
//    Page_Image4
//};
//Page currentPage = Page_Login;
//void setPage(Page page)//框框里的提示语
//{
//    currentPage = page;
//    GUI_ClearFocus();
//    username[0] = '\0';
//    password[0] = '\0';
//    rePassword[0] = '\0';
//}
//
//
//
//void render(void* arg)//主页面
//{
//    //绘制背景
//    putimage(0, 0, &img_bg);
//
//    Rect rect = { (getwidth() - 340) / 2,128,340,370 };
//    //登录界面
//    if (currentPage == Page_Login)
//    {
//        //--文本
//        DK_SetFont(36, "楷体");
//        GUI_Label(R(rect.x, rect.y, rect.w, 40), "最美陶瓷管理系统");
//
//        //--透明的文本按钮
//        DK_SetFont(30, "楷体");
//        settextcolor(RGB(18, 183, 245));
//        if (GUI_TextButton(GUID, R(rect.x, rect.y + 120, rect.w, 35), "用户登录"))
//        {
//            setPage(Page_Userlogin);
//        }
//        if (GUI_TextButton(GUID, R(rect.x, rect.y + 160, rect.w, 35), "管理员登录"))
//        {
//            setPage(Page_Guanlilogin);
//        }
//        if (GUI_TextButton(GUID, R(rect.x, rect.y + 200, rect.w, 35), "注册"))
//        {
//            setPage(Page_Reg);
//        }
//    }
//
//
//    //注册界面
//    else if (currentPage == Page_Reg)
//    {
//
//        //--文本
//        DK_SetFont(36, "楷体");
//        GUI_Label(R(rect.x, rect.y, rect.w, 40), "最美陶瓷管理系统");
//        DK_SetFont(20, "楷体");
//        GUI_Label(R(rect.x, rect.y + 80, rect.w, 20), "用户注册");
//
//        //--输入框
//        GUI_Edit(GUID, R(rect.x, rect.y + 120, rect.w, 35), username, "输入用户名");
//        GUI_Edit(GUID, R(rect.x, rect.y + 160, rect.w, 35), password, "输入密码", EchoMode::Password);
//        GUI_Edit(GUID, R(rect.x, rect.y + 200, rect.w, 35), rePassword, "再次输入密码", EchoMode::Password);
//
//        //--透明的文本按钮
//        DK_SetFont(16, "楷体");
//        settextcolor(RGB(18, 183, 245));
//        if (GUI_TextButton(GUID, R(rect.x, rect.y + 240, 150, 35), "已有账户？去登录", true))
//        {
//            setPage(Page_Login);
//        }
//
//        //--注册按钮
//        settextcolor(WHITE);
//        saveStyle();
//        ButtonStyle.background.color = RGB(24, 144, 255);
//        ButtonStyle.background.hoverColor = RGB(31, 199, 253);
//        if (GUI_TextButton(GUID, R(rect.x, rect.y + 280, rect.w, 35), "注册"))
//        {
//            //两次密码输入是否一致
//            if (strcmp(password, rePassword) != 0)
//            {
//
//            }
//            //用户名是否存在
//            std::vector<User> use; // 存储User对象的vector
//
//            // 检查用户名是否存在的代码
//            for (size_t i = 0; i < use.size(); i++) {
//                if (use[i].username == username) { // 使用std::string的比较操作
//                    // 用户已经存在
//                    std::cout << "用户名已存在。" << std::endl;
//                    break; // 一旦找到匹配，就跳出循环
//                }
//            }
//
//            //保存用户
//            void saveToFile(Student students[], int count, const char* filename);
//            /*User* user = (User*)calloc(1, sizeof(User));
//
//            time_t t = time(NULL);
//            struct tm* _tm = localtime(&t);
//
//            User->name = (((1900 + _tm->tm_year) * 100 + _tm->tm_mon + 1) * 10 + _tm->tm_mday) * 10 + _tm->tm_sec;
//            strcpy_s(user->username, sizeof(user->username), username);
//            strcpy_s(user->password, password);
//            users.push_back(user);*/
//        }
//        restoreStyle();
//    }
//
//    //管理员登录页面
//    else if (currentPage == Page_Guanlilogin)
//    {
//        //--文本
//        DK_SetFont(36, "楷体");
//        GUI_Label(R(rect.x, rect.y, rect.w, 40), "最美陶瓷管理系统");
//        DK_SetFont(20, "楷体");
//        GUI_Label(R(rect.x, rect.y + 80, rect.w, 20), "管理员登录");
//
//        //--输入框
//        GUI_Edit(GUID, R(rect.x, rect.y + 120, rect.w, 35), username, "输入用户名");
//        GUI_Edit(GUID, R(rect.x, rect.y + 160, rect.w, 35), password, "输入密码", EchoMode::Password);
//
//        //--透明的文本按钮
//        DK_SetFont(16, "楷体");
//        settextcolor(RGB(18, 183, 245));
//        if (GUI_TextButton(GUID, R(rect.x + 200, rect.y + 200, 150, 35), "尚无账户？去注册", true))
//        {
//            setPage(Page_Reg);
//        }
//
//        //--登录按钮
//        settextcolor(WHITE);
//        saveStyle();
//        ButtonStyle.background.color = RGB(24, 144, 255);
//        ButtonStyle.background.hoverColor = RGB(31, 199, 253);
//        if (GUI_TextButton(GUID, R(rect.x, rect.y + 250, rect.w, 35), "登录"))
//        {
//            printf("username:%s password:%s\n", username, password);
//
//            //如果登录成功
//            void registerManager();
//            void loginManager();
//            restoreStyle();
//        }
//
//        //用户登录页面
//        else if (currentPage == Page_Userlogin)
//        {
//            //--文本
//            DK_SetFont(36, "楷体");
//            GUI_Label(R(rect.x, rect.y, rect.w, 40), "最美陶瓷管理系统");
//            DK_SetFont(20, "楷体");
//            GUI_Label(R(rect.x, rect.y + 80, rect.w, 20), "用户登录");
//
//            //--输入框
//            GUI_Edit(GUID, R(rect.x, rect.y + 120, rect.w, 35), username, "输入用户名");
//            GUI_Edit(GUID, R(rect.x, rect.y + 160, rect.w, 35), password, "输入密码", EchoMode::Password);
//
//
//            //--透明的文本按钮
//            DK_SetFont(16, "楷体");
//            settextcolor(RGB(18, 183, 245));
//            if (GUI_TextButton(GUID, R(rect.x + 200, rect.y + 200, 150, 35), "尚无账户？去注册", true))
//            {
//                setPage(Page_Reg);
//            }
//
//            //--登录按钮
//            settextcolor(WHITE);
//            saveStyle();
//            ButtonStyle.background.color = RGB(24, 144, 255);
//            ButtonStyle.background.hoverColor = RGB(31, 199, 253);
//            if (GUI_TextButton(GUID, R(rect.x, rect.y + 250, rect.w, 35), "登录"))
//            {
//                printf("username:%s password:%s\n", username, password);
//                //如果登录成功
//                void registerUser();
//                void loginUser();
//            }
//            restoreStyle();
//        }
//
//        //管理员主界面
//        else if (currentPage == Page_GuanliHome)
//        {
//            // 创建窗口
//            initgraph(1220, 860, EW_SHOWCONSOLE);
//            res_init(&res);
//
//            /*int select = -1;
//            settextcolor(BLACK);
//            const char* menuStr[] = { "查看用户","添加用户","查找学生","删除学生","退出系统","返回登录" };
//            size_t size = sizeof(menuStr) / sizeof(menuStr[0]);
//            Rect mRect = { (getwidth() - 150) / 2,(getheight() - size * 40) / 2,150,35 };
//            for (size_t i = 0; i < size; i++)
//            {
//                if (GUI_TextButton(GUID + i, R(mRect.x, mRect.y + i * 40, mRect.w, mRect.h), menuStr[i]))
//                {
//                    select = i;
//                }
//            }
//
//            switch (select)
//            {
//            case 4:
//                quit();
//                break;
//            case 5:
//                setPage(Page_Login);
//                break;
//            default:
//                break;
//            }*/
//        }
//
//        //用户主页面
//        else if (currentPage == Page_UserHome)
//        {
//            int select = -1;
//            settextcolor(BLACK);
//            const char* menuStr[] = { "陶瓷展示","查询陶瓷","退出系统","返回登录" };
//            size_t size = sizeof(menuStr) / sizeof(menuStr[0]);
//            Rect mRect = { (getwidth() - 150) / 2,(getheight() - size * 40) / 2,150,35 };
//            for (size_t i = 0; i < size; i++)
//            {
//                if (GUI_TextButton(GUID + i, R(mRect.x, mRect.y + i * 40, mRect.w, mRect.h), menuStr[i]))
//                {
//                    select = i;
//                }
//            }
//
//            switch (select)
//            {
//            case 0:
//                setPage(Page_Image1);//陶瓷展示
//                break;
//            case 1:
//                //查询陶瓷
//                break;
//            case 2:
//                quit();
//                break;
//            case 3://从0开始，所以-1
//                setPage(Page_Login);
//                break;
//            default:
//                break;
//            }
//        }
//
//        else if (currentPage == Page_Image1)
//        {
//            loadimage(&img_bg, "Resource/images/image1.png", getwidth(), getheight());
//
//            //--透明的文本按钮
//            DK_SetFont(16, "楷体");
//            settextcolor(RGB(18, 183, 245));
//            if (GUI_TextButton(GUID, R(rect.x + 400, rect.y + 400, 150, 35), "下一页"))
//            {
//                setPage(Page_Image2);
//            }
//        }
//
//        else if (currentPage == Page_Image2)
//        {
//            loadimage(&img_bg, "Resource/images/image2.jpg", getwidth(), getheight());
//
//            //--透明的文本按钮
//            DK_SetFont(16, "楷体");
//            settextcolor(RGB(18, 183, 245));
//            if (GUI_TextButton(GUID, R(rect.x + 400, rect.y + 400, 150, 35), "下一页"))
//            {
//                setPage(Page_Image3);
//            }
//        }
//
//        else if (currentPage == Page_Image3)
//        {
//            loadimage(&img_bg, "Resource/images/image3.png", getwidth(), getheight());
//
//            //--透明的文本按钮
//            DK_SetFont(16, "楷体");
//            settextcolor(RGB(18, 183, 245));
//            if (GUI_TextButton(GUID, R(rect.x + 400, rect.y + 400, 150, 35), "下一页"))
//            {
//                setPage(Page_Image4);
//            }
//        }
//
//        else if (currentPage == Page_Image4)
//        {
//            loadimage(&img_bg, "Resource/images/bg.jpg", getwidth(), getheight());
//
//            //--透明的文本按钮
//            DK_SetFont(16, "楷体");
//            settextcolor(RGB(18, 183, 245));
//            if (GUI_TextButton(GUID, R(rect.x + 400, rect.y + 400, 150, 35), "返回"))
//            {
//                setPage(Page_UserHome);
//            }
//        }
//    }
//}



// 获取所有瓷器的名称和对应的图片路径
std::map<std::string, std::string> getCeramicImageMap() {
    std::map<std::string, std::string> ceramicMap;
    ceramicMap["紫砂陶"] = "images/紫砂陶.jpg";
    ceramicMap["唐三彩"] = "images/唐三彩.jpg";
    ceramicMap["玲珑瓷"] = "images/玲珑瓷.jpg";
    ceramicMap["唐山骨质瓷"] = "images/唐山骨质瓷.jpg";
    ceramicMap["清乾隆粉彩牡丹纹玉壶春瓶"] = "images/清乾隆粉彩牡丹纹玉壶春瓶.jpg";
    ceramicMap["粉彩九桃纹天球瓶"] = "images/粉彩九桃纹天球瓶.jpg";
    ceramicMap["清乾隆粉彩百鹿图双耳尊"] = "images/清乾隆粉彩百鹿图双耳尊.jpg";
    ceramicMap["清宫御用瓷器"] = "images/清宫御用瓷器.jpg";
    ceramicMap["梅瓶"] = "images/梅瓶.jpg";
    ceramicMap["清康熙青花花鸟纹鱼尾瓶"] = "images/清康熙青花花鸟纹鱼尾瓶.jpg";
    return ceramicMap;
}



void displayImage(const std::string& imagePath, bool& keepDisplaying) {
    initgraph(1220, 860, EW_SHOWCONSOLE); // 初始化图形界面
    IMAGE image;
    loadimage(&image, imagePath.c_str(),getwidth(),getheight()); // 加载图片
    putimage(0, 0, &image); // 显示图片

    keepDisplaying = true;
    while (keepDisplaying) {
        if (_kbhit()) {  // 检查键盘是否有输入
            char key = _getch();  // 获取按键值
            if (key == 27) {  // 27是ESC键的ASCII码
                keepDisplaying = false;  // 按下ESC键则退出显示
            }
        }
    }
    closegraph(); // 关闭图形界面
}



int main() {

  
    // 创建窗口
    initgraph(1220, 860, EW_SHOWCONSOLE);
    res_init(&res);
 
    // 初始化学生数据
    Student students[MAX_STUDENTS];
    int count = 0;
    loadFromFile(students, &count, "用户信息.txt");
    

    while (true) {
        setbkcolor(WHITE); // 设置背景颜色
        settextstyle(30, 0, "宋体"); // 设置字体
        settextcolor(BLACK);
        ExMessage msg; // 处理消息，不断地获取鼠标信息，如果有信息返回true，否则返回false
        while (peekmessage(&msg, EM_MOUSE)) {
            startupScene(&msg);
        }

        outtextxy(500, 10, _T("陶瓷文化管理系统"));
        settextstyle(20, 0, "宋体"); // 设置字体
        outtextxy(400, 700, _T("由王容,王小兰，王双飞,王草原,宿露露共同完成"));
    }
    
 

    // 结束部分
    getchar(); // 按任意键继续，防止闪退
    closegraph(); // 关闭绘图窗口
    return 0;
}