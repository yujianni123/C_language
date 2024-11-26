#define _CRT_SECURE_NO_WARNINGS 1
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>

//������������ǰ�潨�õ�ͨѵ¼�У�����һ���µ���ϵ����Ϣ��
//����Ҫ�󣺣�1����������ͨߤ¼���ݣ��ܼ�n + 1��, ���Փҡ�ְҵ���绰���롢�����ʼ���ͨߤ��ַ�����ָ���ϵ�˓�Ϣռһ�У�
//�Փҡ�ְҵ���绰���롢�����ʼ���ͨߤ��ַ�ÿո�ָ�����1�Г�������Ҫ��������ϵ����Ŀ��n����
//2�������µĪ��ݣ��ܹ�2�У���һ�������λ�ã��ڶ���������ϵ�˵ē�Ϣ���Փҡ�ְҵ���绰���롢�����ʼ���ͨߤ��ַ�����ÿո�֓ء�
//���Ҫ��(1)��������ª���ǰ��ͨߤ¼��2����������ª��ݺ��ͨߤ¼
//������몑�ݺ��ͨߤ¼��������ϵ�˵ē�Ϣ���ܼ�n�У��ָ���ϵ�˓�Ϣռһ�У��Փҡ�ְҵ���绰���롢�����ʼ���ͨߤ��ַ�ÿո�ָ���
//�������� 1
//3
//mary student 13765121111 mary@qq.com baoshan#road
//tom student 18765656655 tom@qq.com baoli#road
//john teacher 12655556666 john@qq.com kenli#road
//2
//kitty teacher 18766655463 kitty@qq.com kenli#road
//
//������� 1
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
//��������2��
//3
//mary student 13765121111 mary@qq.com baoshan#road
//tom student 18765656655 tom@qq.com baoli#road
//john teacher 12655556666 john@qq.com kenli#road
//4
//
//�������2��
//database is :
//mary student 13765121111 mary@qq.com baoshan#road
//tom student 18765656655 tom@qq.com baoli#road
//john teacher 12655556666 john@qq.com kenli#road
//illegal location!
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct people { // ��ϵ����Ϣ�ṹ������
    char name[20];        // ����
    char job[20];         // ְҵ
    char mobile_phone[20]; // �ֻ�
    char email[30];        // �����ʼ�
    char address[30];     // ͨѶ��ַ
} Record;

typedef struct Node {
    Record data;          // �������������
    struct Node* next;   // ָ����
} Lnode, LinkList;

// ��������
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

// ��ʾ����
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

// ��������ϵ����Ϣ
LinkList* insert_list(LinkList* head) {
    int i;
    Record e;
    LinkList* p, * s;
    scanf("%d", &i);
    scanf("%s %s %s %s %s", e.name, e.job, e.mobile_phone, e.email, e.address);
    p = head;
    int j = 0;
    // Ѱ�ҵ� i-1 �����
    while (j < i - 1 && p != NULL) {
        p = p->next;
        j++;
    }
    // ��� p Ϊ NULL �� j ������ i-1��˵���� i-1 ����㲻����
    if (p == NULL || j != i - 1) {
        printf("illegal location!\n");
        return head; // ����ʧ��
    }
    else {
        // �����½�� s
        s = (LinkList*)malloc(sizeof(LinkList));
        if (s == NULL) {
            return NULL;
        }
        s->data = e; // �½��� data ����Ϊ e
        s->next = p->next; // �� s ���뵽 p ֮��
        p->next = s;
        return head; // ����ɹ�������ͷ���
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