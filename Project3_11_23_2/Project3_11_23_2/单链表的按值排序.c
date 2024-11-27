#define _CRT_SECURE_NO_WARNINGS 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct people {
    char name[20];
    char profession[20];
    char mobile_phone[20];
    char email[50];
    char address[50];
} Record;

typedef struct Node {
    Record data;
    struct Node* next;
} Lnode, LinkList;

LinkList* create_list(int length) {
    LinkList* head, * rear, * p;
    int i;
    head = (LinkList*)malloc(sizeof(LinkList));
    head->next = NULL;
    rear = head;
    for (i = 1; i <= length; i++) {
        p = (LinkList*)malloc(sizeof(LinkList));
        scanf("%s %s %s %s %s", p->data.name, p->data.profession, p->data.mobile_phone, p->data.email, p->data.address);
        p->next = NULL;
        rear->next = p;
        rear = p;
    }
    return head;
}

void show_list(LinkList* head) {
    LinkList* p;
    if (head != NULL) {
        p = head->next;
        while (p != NULL) {
            printf("%s %s %s %s %s\n", p->data.name, p->data.profession, p->data.mobile_phone, p->data.email, p->data.address);
            p = p->next;
        }
    }
}

LinkList* sort_list(LinkList* head) {
    if ((head == NULL) || (head->next == NULL)) {
        return head;
    }

    LinkList* newnode = (LinkList*)malloc(sizeof(LinkList));
    newnode->next = head;
    LinkList* sortlast = head;
    LinkList* cur = head->next;

    while (cur != NULL) {
        if (strcmp(cur->data.name, sortlast->data.name) >= 0) {
            sortlast->next = cur;
            sortlast = cur;
            cur = cur->next;
            sortlast->next = NULL;
        }
        else {
            LinkList* pre = newnode;
            while (pre->next != NULL && strcmp(pre->next->data.name, cur->data.name) < 0) {
                pre = pre->next;
            }
            sortlast->next = cur->next;
            cur->next = pre->next;
            pre->next = cur;
            cur = sortlast->next;
        }
    }
    return newnode->next;
}

int main() {
    LinkList* h, * pt;
    int len;
    scanf("%d", &len);
    h = create_list(len);
    printf("database is:\n");
    show_list(h);
    h = sort_list(h);
    printf("after:\n");
    show_list(h);
    return 0;
}