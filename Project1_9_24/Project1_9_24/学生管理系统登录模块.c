#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<string.h>

//用户名和密码
typedef struct{
	char username[50];
	char password[50];
}Student;

//登录
int login(Student *users, int size, char* username, char* password) {
	for (int i = 0; i < size; i++)
	{
		if (strcmp(users[i].username,username ) == 0 && strcmp(users[i].password, password) == 0)
		{
			return 1;//成功
		}
	}

	return 0;//失败
}

int main()
{
	//初始化
	Student students[] = {
	{"student1","password1"},
	{"student2","password2"},
	{"student3","password3"}
	};

	char username=0, password=0;

	printf("请输入账号：");
	scanf("%s", username);
	printf("请输入密码：");
	scanf("%s", password);

	if (login(students, 3, username, password)) {
		printf("登陆成功！\n");
	}
	else {
		printf("账号或密码错误！\n");
	}
	return 0;
}