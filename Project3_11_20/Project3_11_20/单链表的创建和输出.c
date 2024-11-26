#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

    // ������ϵ�˽ṹ��
    typedef struct Contact {
        char name[50];
        char job[50];
        char phone[20];
        char email[50];
        char address[100];
    } Contact;

    int main() {
        int n;
        printf("��������ϵ����Ŀ��: ");
        scanf("%d", &n);

        Contact* contacts = (Contact*)malloc(n * sizeof(Contact)); // ��̬�����ڴ�

        if (contacts == NULL) {
            printf("�ڴ����ʧ��\n");
            return 1;
        }

        // ��ȡÿ����ϵ�˵���Ϣ
        for (int i = 0; i < n; i++) {
            printf("��������ϵ�� #%d ����Ϣ������ ְҵ �绰���� �����ʼ� ͨѶ��ַ��:\n", i + 1);
            scanf("%s %s %s %s %s", contacts[i].name, contacts[i].job, contacts[i].phone, contacts[i].email, contacts[i].address);
        }

       

        // ���ÿ����ϵ�˵���Ϣ
        printf("\nͨѶ¼:\n");
        for (int i = 0; i < n; i++) {
            printf("%s %s %s %s %s\n", contacts[i].name, contacts[i].job, contacts[i].phone, contacts[i].email, contacts[i].address);
        }

        free(contacts); // �ͷ��ڴ�
        return 0;
    }