#include "PushButton.h"
#include "Window.h"
PushButton::PushButton(const std::string& text, int x, int y, int w, int h)
	:BasicWidget(x,y,w,h),m_text(text)
{

}

void PushButton::show()
{
	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

	settextcolor(BLACK);
	settextstyle(20, 0, "����");
	//�����־�����ʾ�ڰ�ť�м�
	int tx = m_x+(m_w - textwidth(m_text.c_str()))/2;
	int ty = m_y +(m_h - textheight(m_text.c_str()))/2;

	::outtextxy(tx, ty, m_text.c_str());
}
