#define _CRT_SECURE_NO_WARNINGS 1
#include<graphics.h>//����ͼ�ο�ͷ�ļ�
#include <conio.h>
int main()
{
	initgraph(640, 480);    //�������ڴ�СΪ640x480����
	setbkcolor(WHITE);
	settextcolor(RED);
	settextstyle(72, 0, _T("����"));
	outtextxy(170, 200, _T("ͼ�����ϵͳ"));
	_getch();      //�����������,��ֹ����
	closegraph();   //�رջ�ͼ����
	return 0;
}