#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<graphics.h>//引用图形库头文件
#include <conio.h>
#include <mmsystem.h>//引用音乐库
#pragma comment(lib,"winmm.lib")
void menu()
{
	printf("**********************************\n");
	printf("*******欢迎来到系统菜单界面*******\n");
	printf("**********请选择登录页面**********\n");
	printf("**********************************\n");
	printf("\t1-图书管理\n");
	printf("\t2-图书借阅\n");
	printf("\t3-用户管理\n");
	printf("\t4-图书浏览\n");
	printf("\t5-座位预约\n");
	printf("**********************************\n");
	printf("**********************************\n");
}

void menu1()
{
	printf("**********************************\n");
	printf("**********************************\n");
	printf("*******欢迎来到图书管理界面*******\n");
	printf("**********************************\n");
	printf("**********************************\n");
	printf("\t1-图书的添加\n");
	printf("\t2-图书的删除\n");
	printf("\t3-图书的修改\n");
	printf("\t4-返回系统菜单\n");
	printf("**********************************\n");
	printf("**********************************\n");
}

void menu2()
{
	printf("**********************************\n");
	printf("**********************************\n");
	printf("*******欢迎来到图书借阅界面*******\n");
	printf("**********************************\n");
	printf("**********************************\n");
	printf("\t1-按书名查找\n");
	printf("\t2-按作者名查找\n");
	printf("\t3-按分类号查找\n");
	printf("\t4-返回系统菜单\n");
	printf("**********************************\n");
	printf("**********************************\n");
}

void menu3()
{
	printf("**********************************\n");
	printf("**********************************\n");
	printf("*******欢迎来到用户管理界面*******\n");
	printf("**********************************\n");
	printf("**********************************\n");
	printf("\t1-用户注册\n");
	printf("\t2-用户消除\n");
	printf("\t3-用户修改\n");
	printf("\t4-返回系统菜单\n");
	printf("**********************************\n");
	printf("**********************************\n");
}

void Login()
{

}

int main()
{
	//initgraph(960, 960);
	//setbkcolor(WHITE);//背景颜色
	//settextcolor(RGB(255, 149, 144));//字体颜色

	//settextstyle(72, 0, _T("宋体"));//设置字体
	//outtextxy(0, 0, _T("图书管理系统"));//输出字体
	//outtextxy(300, 100, _T("欢迎来到主界面"));

	//_getch();      //按任意键继续,防止闪退
	//closegraph();   //关闭绘图窗口

	int a;
	printf("账号登录：\n");
	menu();
	scanf("%d", &a);
	if (a == 1)
		menu1();
	else if (a == 2)
		menu2();
	else if (a == 3)
		menu3();
	else
		printf("输入有误！请从新输入：");
	return 0;
}