#define _CRT_SECURE_NO_WARNINGS 1
#include<graphics.h>//引用图形库头文件
#include <conio.h>
int main()
{
	initgraph(640, 480);    //创建窗口大小为640x480像素
	setbkcolor(WHITE);
	settextcolor(RED);
	settextstyle(72, 0, _T("宋体"));
	outtextxy(170, 200, _T("图书管理系统"));
	_getch();      //按任意键继续,防止闪退
	closegraph();   //关闭绘图窗口
	return 0;
}