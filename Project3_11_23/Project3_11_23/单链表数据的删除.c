#define _CRT_SECURE_NO_WARNINGS 1

//������������ǰ�潨�õ�ͨѶ¼�У�ɾ��һ���µ���ϵ����Ϣ��
//����Ҫ�󣺣�1����������ͨѶ¼���ݣ��ܼ�n + 1��, ��������ְҵ���绰���롢�����ʼ���ͨѶ��ַ����
// ÿ����ϵ����Ϣռһ�У�������ְҵ���绰���롢�����ʼ���ͨѶ��ַ�ÿո�ָ�����1����������Ҫ��������ϵ����Ŀ��n��
// ��2�������ɾ���ļ�¼�š�
//
//���Ҫ��(1)���ɾ������ǰ��ͨѶ¼
// ��2�����ɾ�����ݺ��ͨѶ¼
//
//����������ݺ��Ѷ¼��������ϵ�˵���Ϣ���ܼ�n�У�ÿ����ϵ����Ϣռһ�У�������ְҵ���绰���롢�����ʼ���ͨѶ��ַ�ÿո�ָ���
//�������� 1
//
//3
//mary student 13765121111 mary@qq.com baoshan#road
//tom student 18765656655 tom@qq.com baoli#road
//john teacher 12655556666 john@qq.com kenli#road
//2
//
//������� 1
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
        return head; // λ�ò��Ϸ�������ԭ����
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

    // �ͷ�����ռ�õ��ڴ�
    free_list(h);

    return 0;
}


