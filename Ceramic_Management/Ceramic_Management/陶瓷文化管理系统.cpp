#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <graphics.h>//����ͼ�ο�
#include <conio.h>
#include <mmstream.h>
#pragma comment (lib,"winmm.lib")

int main()
{
	initgraph(960, 580);//��������
	setbkcolor(WHITE);//���ñ�����ɫ
	settextstyle(30, 0, "���ǹ���W");//��������
	outtextxy(400, 10, _T("�մ��Ļ�����ϵͳ"));
	getchar();//���������������ֹ����
	closegraph();//�رջ�ͼ����
	return 0;
}