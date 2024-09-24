#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>  
#include <string.h>  

// 定义用户信息的结构体  
typedef struct {
    char username[50];
    char password[50];
} UserInfo;

// 初始化用户信息  
UserInfo users[] = {
    {"user1", "pass123"},
    {"user2", "password"},
    {"admin", "admin123"}
};

// 用户数量  
#define USER_COUNT 3  

// 登录验证函数  
int login(UserInfo users[], int userCount, char* inputUsername, char* inputPassword) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, inputUsername) == 0 && strcmp(users[i].password, inputPassword) == 0) {
            return 1; // 登录成功  
        }
    }
    return 0; // 登录失败  
}

int main() {
    char username[50], password[50];

    // 提示用户输入账号和密码  
    printf("请输入账号: ");
    scanf("%49s", username); // 读取字符串时限制长度，防止溢出  
    printf("请输入密码: ");
    scanf("%49s", password); // 同样限制长度  

    // 调用登录验证函数  
    if (login(users, USER_COUNT, username, password)) {
        printf("登录成功！\n");
    }
    else {
        printf("账号或者密码错误！\n");
    }

    return 0;
}