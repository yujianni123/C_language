#define _CRT_SECURE_NO_WARNINGS 1
#include <graphics.h>  
#include <conio.h>  
#include <fstream>  
#include <string>  

// 定义用户结构体  
struct User {
    std::string username;
    std::string password;
};

// 检查用户是否存在  
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

// 绘制登录界面  
void drawLoginScreen() {
 /*   setfillchar(' ');*/
    setbkcolor(WHITE);
    cleardevice();
    outtextxy(100, 50, "Login");
    outtextxy(100, 100, "Username:");
    outtextxy(100, 150, "Password:");
}

// 绘制欢迎界面（登录成功后显示）  
void drawWelcomeScreen() {
   /* setfillchar(' ');*/
    setbkcolor(WHITE);
    cleardevice();
    outtextxy(100, 50, "Welcome!");
    outtextxy(100, 100, "You have successfully logged in.");
}

// 绘制错误界面（登录失败时显示，但这里我们选择返回登录界面而不是显示新界面）  
// 不过为了示例完整性，还是定义一个这样的函数（尽管在这个例子中不会被调用）  
void drawErrorScreen() {
   
    setbkcolor(WHITE);
    cleardevice();
    outtextxy(100, 50, "Error");
    outtextxy(100, 100, "Invalid username or password.");
}

// 处理登录逻辑  
bool handleLogin(const std::string& filename) {
    std::string username, password;
    drawLoginScreen();

    // 模拟用户输入（在实际应用中，你会从键盘读取这些输入）  
    // 为了演示，我们直接设置用户名和密码为预设值  
    username = "testuser";
    password = "testpass";
    // std::getline(std::cin, username);  
    // while (kbhit()) getch(); // 清空缓冲区（在实际应用中需要）  
    // std::getline(std::cin, password);  
    // while (kbhit()) getch(); // 清空缓冲区（在实际应用中需要）  

    // 验证用户  
    if (authenticateUser(username, password, filename)) {
        // 登录成功，绘制欢迎界面  
        drawWelcomeScreen();
        return true;
    }
    else {
        // 登录失败，重新绘制登录界面（这里不调用drawErrorScreen，而是直接返回登录界面）  
        // 在实际应用中，你可能希望给用户一些反馈，比如显示一个错误消息，然后再返回登录界面  
        // 但为了简化，我们直接返回登录界面  
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
        // 在这里，您可能想要添加一些逻辑来处理用户输入，  
        // 而不是立即重新尝试登录。例如，您可以等待用户按下回车键。  
        if (!_kbhit() || _getch() != '\r') { // 检查是否按下了回车键  
            continue; // 如果没有按下回车键，则继续循环并重新显示登录界面  
        }
    }

    // 登录成功后，可以在这里添加更多逻辑  

    _getch(); // 等待用户按键后关闭图形窗口  
    closegraph();
    return 0;
}