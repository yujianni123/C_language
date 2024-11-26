#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

    // 定义联系人结构体
    typedef struct Contact {
        char name[50];
        char job[50];
        char phone[20];
        char email[50];
        char address[100];
    } Contact;

    int main() {
        int n;
        printf("请输入联系人条目数: ");
        scanf("%d", &n);

        Contact* contacts = (Contact*)malloc(n * sizeof(Contact)); // 动态分配内存

        if (contacts == NULL) {
            printf("内存分配失败\n");
            return 1;
        }

        // 读取每个联系人的信息
        for (int i = 0; i < n; i++) {
            printf("请输入联系人 #%d 的信息（姓名 职业 电话号码 电子邮件 通讯地址）:\n", i + 1);
            scanf("%s %s %s %s %s", contacts[i].name, contacts[i].job, contacts[i].phone, contacts[i].email, contacts[i].address);
        }

       

        // 输出每个联系人的信息
        printf("\n通讯录:\n");
        for (int i = 0; i < n; i++) {
            printf("%s %s %s %s %s\n", contacts[i].name, contacts[i].job, contacts[i].phone, contacts[i].email, contacts[i].address);
        }

        free(contacts); // 释放内存
        return 0;
    }