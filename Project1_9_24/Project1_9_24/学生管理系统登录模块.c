#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<string.h>

//�û���������
typedef struct{
	char username[50];
	char password[50];
}Student;

//��¼
int login(Student *users, int size, char* username, char* password) {
	for (int i = 0; i < size; i++)
	{
		if (strcmp(users[i].username,username ) == 0 && strcmp(users[i].password, password) == 0)
		{
			return 1;//�ɹ�
		}
	}

	return 0;//ʧ��
}

int main()
{
	//��ʼ��
	Student students[] = {
	{"student1","password1"},
	{"student2","password2"},
	{"student3","password3"}
	};

	char username=0, password=0;

	printf("�������˺ţ�");
	scanf("%s", username);
	printf("���������룺");
	scanf("%s", password);

	if (login(students, 3, username, password)) {
		printf("��½�ɹ���\n");
	}
	else {
		printf("�˺Ż��������\n");
	}
	return 0;
}