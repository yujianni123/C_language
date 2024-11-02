#pragma once
#include <easyx.h>
class BasicWidget
{
public:
	BasicWidget(int x, int y, int w, int h);
	virtual ~BasicWidget() {}
	int width();
	int height();
	void setFixedSize(int w, int h);

	int x();
	int y();
	void move(int x, int y);//�ƶ�����

	bool isin();//�ж�����Ƿ��ڵ�ǰ��ť��
	bool isClicked();//�ж�����Ƿ����˰�ť
	virtual void show() = 0;//�麯��
	virtual void event();
	void setBackgroundColor(COLORREF c);
	void setHoverColor(COLORREF c);

protected:

	int m_x;
	int m_y;
	int m_w;
	int m_h;


	COLORREF cur_c = RGB(232, 232, 236);//��ǰ��ɫ
	COLORREF normal_c = RGB(232, 232, 236);//������ɫ
	COLORREF hover_c = RGB(173, 216, 230);//�ƶ�����ɫ

};

