#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>  
#include <string.h>  

// �����û���Ϣ�Ľṹ��  
typedef struct {
    char username[50];
    char password[50];
} UserInfo;

// ��ʼ���û���Ϣ  
UserInfo users[] = {
    {"user1", "pass123"},
    {"user2", "password"},
    {"admin", "admin123"}
};

// �û�����  
#define USER_COUNT 3  

// ��¼��֤����  
int login(UserInfo users[], int userCount, char* inputUsername, char* inputPassword) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, inputUsername) == 0 && strcmp(users[i].password, inputPassword) == 0) {
            return 1; // ��¼�ɹ�  
        }
    }
    return 0; // ��¼ʧ��  
}

int main() {
    char username[50], password[50];

    // ��ʾ�û������˺ź�����  
    printf("�������˺�: ");
    scanf("%49s", username); // ��ȡ�ַ���ʱ���Ƴ��ȣ���ֹ���  
    printf("����������: ");
    scanf("%49s", password); // ͬ�����Ƴ���  

    // ���õ�¼��֤����  
    if (login(users, USER_COUNT, username, password)) {
        printf("��¼�ɹ���\n");
    }
    else {
        printf("�˺Ż����������\n");
    }

    return 0;
}