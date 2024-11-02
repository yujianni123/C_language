#include "PushButton.h"
#include "Window.h"
PushButton::PushButton(const std::string& text, int x ,int y, int w, int h)
	:BasicWidget(x,y,w,h),m_text(text)
{

}

void setButtonStyle(PushButton* button) {
	// 设置填充颜色为所需颜色，这里使用 RGB(232, 232, 236)
	setfillcolor(BLUE);
	// 设置画笔颜色为黑色，用于边框
	setlinecolor(RGB(0, 0, 0));
	// 设置边框宽度，例如设置为2个像素
	setlinestyle(PS_SOLID, 2);

	// 绘制填充的矩形（按钮背景）
	solidrectangle(button->x(), button->y(), button->x() + button->width(), button->y() + button->height());
}


void PushButton::show()
{
	setfillcolor(cur_c);//设置按钮颜色
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

	settextcolor(BLACK);//字体颜色
	//把文字居中显示在按钮中间
	int tx = m_x + (m_w - textwidth(m_text.c_str())) / 2;
	int ty = m_y + (m_h - textwidth(m_text.c_str())) / 2+ textwidth(m_text.c_str())/2;
	::outtextxy(tx, ty, m_text.c_str());
}




