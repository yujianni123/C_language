#define _CRT_SECURE_NO_WARNINGS 1

//问题描述：往前面建好的通讯录中，删除一条新的联系人信息。
//输入要求：（1）首先输入通讯录数据，总计n + 1行, （姓名、职业、电话号码、电子邮件、通讯地址），
// 每个联系人信息占一行，姓名、职业、电话号码、电子邮件、通讯地址用空格分隔。第1行是输入你要创建的联系人条目数n。
// （2）输入待删除的记录号。
//
//输出要求：(1)输出删除数据前的通讯录
// （2）输出删除数据后的通讯录
//
//输出插入数据后的讯录中所有联系人的信息，总计n行，每个联系人信息占一行，姓名、职业、电话号码、电子邮件、通讯地址用空格分隔。
//输入样例 1
//
//3
//mary student 13765121111 mary@qq.com baoshan#road
//tom student 18765656655 tom@qq.com baoli#road
//john teacher 12655556666 john@qq.com kenli#road
//2
//
//输出样例 1
//
//database is :
//mary student 13765121111 mary@qq.com baoshan#road
//tom student 18765656655 tom@qq.com baoli#road
//john teacher 12655556666 john@qq.com kenli#road
//after :
//mary student 13765121111 mary@qq.com baoshan#road
//john teacher 12655556666 john@qq.com kenli#road

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct people {
    char name[20];
    char profession[20];
    char mobile_phone[20];
    char email[50];
    char address[100];
} Record;

typedef struct Node {
    Record data;
    struct Node* next;
} Lnode, * LinkList;

LinkList create_list(int length) {
    LinkList head, rear, p;
    int i;
    head = (LinkList)malloc(sizeof(Lnode));
    if (head == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    head->next = NULL;
    rear = head;
    for (i = 1; i <= length; i++) {
        p = (LinkList)malloc(sizeof(Lnode));
        if (p == NULL) {
            fprintf(stderr, "Memory allocation failed!\n");
            exit(EXIT_FAILURE);
        }
        scanf("%19s %19s %19s %49s %99s", p->data.name, p->data.profession, p->data.mobile_phone, p->data.email, p->data.address);
        p->next = NULL;
        rear->next = p;
        rear = p;
    }
    return head;
}

void show_list(LinkList head) {
    LinkList p;
    p = head->next;
    while (p != NULL) {
        printf("%s %s %s %s %s\n", p->data.name, p->data.profession, p->data.mobile_phone, p->data.email, p->data.address);
        p = p->next;
    }
}

LinkList delete_list(LinkList head, int position) {
    LinkList s = head, q;
    int j = 0;
    while (j < position - 1 && s->next) {
        j++;
        s = s->next;
    }
    if (s->next == NULL) {
        printf("Illegal location!\n");
        return head; // 位置不合法，返回原链表
    }
    q = s->next;
    s->next = q->next;
    free(q);
    return head;
}

void free_list(LinkList head) {
    LinkList p, tmp;
    p = head;
    while (p != NULL) {
        tmp = p;
        p = p->next;
        free(tmp);
    }
}

int main() {
    LinkList h;
    int len, pos;

    printf("Enter the number of records: ");
    scanf("%d", &len);
    h = create_list(len);

    printf("Database is:\n");
    show_list(h);

    printf("Enter the position to delete: ");
    scanf("%d", &pos);
    h = delete_list(h, pos);

    printf("After deletion:\n");
    show_list(h);

    // 释放链表占用的内存
    free_list(h);

    return 0;
}


