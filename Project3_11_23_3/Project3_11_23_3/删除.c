#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct people //联系人信息结构体类型
{
    char name[20]; //名字
    char profession[20]; //职业
    char mobile_phone[20]; //手机
    char email[50]; //电子邮件
    char address[100]; //通讯地址
} Record;

typedef struct Node {
    Record data; //单链表的数据域
    struct Node* next; //指针域
} Lnode, * LinkList;

LinkList create_list(int length) {
    LinkList head, rear, p;
    int i;
    head = (LinkList)malloc(sizeof(Lnode));
    head->next = NULL;
    rear = head;
    for (i = 1; i <= length; i++) {
        p = (LinkList)malloc(sizeof(Lnode));
        scanf("%s %s %s %s %s", p->data.name, p->data.profession, p->data.mobile_phone, p->data.email, p->data.address);
        p->next = NULL;
        rear->next = p;
        rear = p;
    }
    return head;
}



void show_list(LinkList head) {
    LinkList p;
    if (head != NULL) {
        p = head->next;
        while (p != NULL) {
            printf("%s %s %s %s %s\n", p->data.name, p->data.profession, p->data.mobile_phone, p->data.email, p->data.address);
            p = p->next;
        }
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
        return head; // 返回原链表，因为位置不合法
    }
    q = s->next;
    s->next = q->next;
    free(q);
    return head;
}

int main() {
    LinkList h;
    int len, pos;
    scanf("%d", &len);
    h = create_list(len);
   printf("database is:\n");
    show_list(h);
    scanf("%d", &pos);
    h = delete_list(h, pos);
    printf("after:\n");
    show_list(h);
    return 0;
}

