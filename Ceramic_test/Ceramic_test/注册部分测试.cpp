#define _CRT_SECURE_NO_WARNINGS 1
#include <graphics.h>  
#include <conio.h>  
#include <fstream>  
#include <string>  

// �����û��ṹ��  
struct User {
    std::string username;
    std::string password;
};

// ����û��Ƿ����  
bool authenticateUser(const std::string& username, const std::string& password, const std::string& filename) {
    std::ifstream file(filename);
    std::string storedUsername, storedPassword;
    while (file >> storedUsername >> storedPassword) {
        if (storedUsername == username && storedPassword == password) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// ���Ƶ�¼����  
void drawLoginScreen() {
 /*   setfillchar(' ');*/
    setbkcolor(WHITE);
    cleardevice();
    outtextxy(100, 50, "Login");
    outtextxy(100, 100, "Username:");
    outtextxy(100, 150, "Password:");
}

// ���ƻ�ӭ���棨��¼�ɹ�����ʾ��  
void drawWelcomeScreen() {
   /* setfillchar(' ');*/
    setbkcolor(WHITE);
    cleardevice();
    outtextxy(100, 50, "Welcome!");
    outtextxy(100, 100, "You have successfully logged in.");
}

// ���ƴ�����棨��¼ʧ��ʱ��ʾ������������ѡ�񷵻ص�¼�����������ʾ�½��棩  
// ����Ϊ��ʾ�������ԣ����Ƕ���һ�������ĺ�������������������в��ᱻ���ã�  
void drawErrorScreen() {
   
    setbkcolor(WHITE);
    cleardevice();
    outtextxy(100, 50, "Error");
    outtextxy(100, 100, "Invalid username or password.");
}

// �����¼�߼�  
bool handleLogin(const std::string& filename) {
    std::string username, password;
    drawLoginScreen();

    // ģ���û����루��ʵ��Ӧ���У����Ӽ��̶�ȡ��Щ���룩  
    // Ϊ����ʾ������ֱ�������û���������ΪԤ��ֵ  
    username = "testuser";
    password = "testpass";
    // std::getline(std::cin, username);  
    // while (kbhit()) getch(); // ��ջ���������ʵ��Ӧ������Ҫ��  
    // std::getline(std::cin, password);  
    // while (kbhit()) getch(); // ��ջ���������ʵ��Ӧ������Ҫ��  

    // ��֤�û�  
    if (authenticateUser(username, password, filename)) {
        // ��¼�ɹ������ƻ�ӭ����  
        drawWelcomeScreen();
        return true;
    }
    else {
        // ��¼ʧ�ܣ����»��Ƶ�¼���棨���ﲻ����drawErrorScreen������ֱ�ӷ��ص�¼���棩  
        // ��ʵ��Ӧ���У������ϣ�����û�һЩ������������ʾһ��������Ϣ��Ȼ���ٷ��ص�¼����  
        // ��Ϊ�˼򻯣�����ֱ�ӷ��ص�¼����  
        drawLoginScreen();
        return false;
    }
}

int main() {
    initgraph(640, 480);
    std::string filename = "users.txt";

    bool loggedIn = false;
    while (!loggedIn) {
        loggedIn = handleLogin(filename);
        // �������������Ҫ���һЩ�߼��������û����룬  
        // �������������³��Ե�¼�����磬�����Եȴ��û����»س�����  
        if (!_kbhit() || _getch() != '\r') { // ����Ƿ����˻س���  
            continue; // ���û�а��»س����������ѭ����������ʾ��¼����  
        }
    }

    // ��¼�ɹ��󣬿�����������Ӹ����߼�  

    _getch(); // �ȴ��û�������ر�ͼ�δ���  
    closegraph();
    return 0;
}