#include "PushButton.h"
#include "Window.h"
PushButton::PushButton(const std::string& text, int x ,int y, int w, int h)
	:BasicWidget(x,y,w,h),m_text(text)
{

}

void setButtonStyle(PushButton* button) {
	// ���������ɫΪ������ɫ������ʹ�� RGB(232, 232, 236)
	setfillcolor(BLUE);
	// ���û�����ɫΪ��ɫ�����ڱ߿�
	setlinecolor(RGB(0, 0, 0));
	// ���ñ߿��ȣ���������Ϊ2������
	setlinestyle(PS_SOLID, 2);

	// �������ľ��Σ���ť������
	solidrectangle(button->x(), button->y(), button->x() + button->width(), button->y() + button->height());
}


void PushButton::show()
{
	setfillcolor(cur_c);//���ð�ť��ɫ
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

	settextcolor(BLACK);//������ɫ
	//�����־�����ʾ�ڰ�ť�м�
	int tx = m_x + (m_w - textwidth(m_text.c_str())) / 2;
	int ty = m_y + (m_h - textwidth(m_text.c_str())) / 2+ textwidth(m_text.c_str())/2;
	::outtextxy(tx, ty, m_text.c_str());
}




