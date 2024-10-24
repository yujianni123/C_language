#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <graphics.h>//引用图形库
#include <conio.h>
#include <mmstream.h>
#pragma comment (lib,"winmm.lib")

int main()
{
	initgraph(960, 580);//创建窗口
	setbkcolor(WHITE);//设置背景颜色
	settextstyle(30, 0, "汉仪古隶W");//设置字体
	outtextxy(400, 10, _T("陶瓷文化管理系统"));
	getchar();//按任意键继续，防止闪退
	closegraph();//关闭绘图窗口
	return 0;
}