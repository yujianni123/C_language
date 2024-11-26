#define _CRT_SECURE_NO_WARNINGS 1
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>

//问题描述：往前面建好的通训录中，插入一条新的联系人信息。
//输入要求：（1）首先输入通撙录獞据，总计n + 1行, （姓撘、职业、电话号码、电子邮件、通撙地址），撝个联系人撜息占一行，
//姓撘、职业、电话号码、电子邮件、通撙地址用空格分隔。第1行撛输入你要创建的联系人条目獞n。（
//2）输入新的獞据：总共2行，第一行输入的位置，第二行输入联系人的撜息（姓撘、职业、电话号码、电子邮件、通撙地址），用空格分撠。
//输出要求：(1)输出插入新獞据前的通撙录（2）输出插入新獞据后的通撙录
//输出插入獞据后的通撙录中所有联系人的撜息，总计n行，撝个联系人撜息占一行，姓撘、职业、电话号码、电子邮件、通撙地址用空格分隔。
//输入样例 1
//3
//mary student 13765121111 mary@qq.com baoshan#road
//tom student 18765656655 tom@qq.com baoli#road
//john teacher 12655556666 john@qq.com kenli#road
//2
//kitty teacher 18766655463 kitty@qq.com kenli#road
//
//输出样例 1
//database is :
//mary student 13765121111 mary@qq.com baoshan#road
//tom student 18765656655 tom@qq.com baoli#road
//john teacher 12655556666 john@qq.com kenli#road
//after :
//mary student 13765121111 mary@qq.com baoshan#road
//kitty teacher 18766655463 kitty@qq.com kenli#road
//tom student 18765656655 tom@qq.com baoli#road
//john teacher 12655556666 john@qq.com kenli#road
//
//输入样例2：
//3
//mary student 13765121111 mary@qq.com baoshan#road
//tom student 18765656655 tom@qq.com baoli#road
//john teacher 12655556666 john@qq.com kenli#road
//4
//
//输出样例2：
//database is :
//mary student 13765121111 mary@qq.com baoshan#road
//tom student 18765656655 tom@qq.com baoli#road
//john teacher 12655556666 john@qq.com kenli#road
//illegal location!
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct people { // 联系人信息结构体类型
    char name[20];        // 名字
    char job[20];         // 职业
    char mobile_phone[20]; // 手机
    char email[30];        // 电子邮件
    char address[30];     // 通讯地址
} Record;

typedef struct Node {
    Record data;          // 单链表的数据域
    struct Node* next;   // 指针域
} Lnode, LinkList;

// 创建链表
LinkList* create_list(int length) {
    LinkList* head, * rear, * p;
    int i;
    head = (LinkList*)malloc(sizeof(LinkList));
    head->next = NULL;
    rear = head;
    for (i = 1; i <= length; i++) {
        p = (LinkList*)malloc(sizeof(LinkList));
        scanf("%s %s %s %s %s", p->data.name, p->data.job, p->data.mobile_phone, p->data.email, p->data.address);
        p->next = NULL;
        rear->next = p;
        rear = p;
    }
    return head;
}

// 显示链表
void show_list(LinkList* head) {
    LinkList* p;
    if (head != NULL) {
        p = head->next;
        while (p != NULL) {
            printf("%s %s %s %s %s\n", p->data.name, p->data.job, p->data.mobile_phone, p->data.email, p->data.address);
            p = p->next;
        }
    }
}

// 插入新联系人信息
LinkList* insert_list(LinkList* head) {
    int i;
    Record e;
    LinkList* p, * s;
    scanf("%d", &i);
    scanf("%s %s %s %s %s", e.name, e.job, e.mobile_phone, e.email, e.address);
    p = head;
    int j = 0;
    // 寻找第 i-1 个结点
    while (j < i - 1 && p != NULL) {
        p = p->next;
        j++;
    }
    // 如果 p 为 NULL 或 j 不等于 i-1，说明第 i-1 个结点不存在
    if (p == NULL || j != i - 1) {
        printf("illegal location!\n");
        return head; // 插入失败
    }
    else {
        // 创建新结点 s
        s = (LinkList*)malloc(sizeof(LinkList));
        if (s == NULL) {
            return NULL;
        }
        s->data = e; // 新结点的 data 域置为 e
        s->next = p->next; // 将 s 插入到 p 之后
        p->next = s;
        return head; // 插入成功，返回头结点
    }
}

int main() {
    LinkList* h;
    int len = 0;
    scanf("%d", &len);
    h = create_list(len);
    printf("database is:\n");
    show_list(h);
    insert_list(h);
    printf("after:\n");
    show_list(h);
    return 0;
}