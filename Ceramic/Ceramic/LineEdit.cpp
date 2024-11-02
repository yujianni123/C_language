#include "LineEdit.h"

LineEdit::LineEdit(int x, int y, int w, int h)
	:BasicWidget(x,y,w,h)
{
	
}

void LineEdit::show()
{
	setfillcolor(cur_c);//设置按钮颜色
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

	settextcolor(BLACK);//字体颜色
	settextstyle(23, 0, "宋体");
	//把文字居中显示在按钮中间
	int ty = m_y + (m_h - textwidth(m_text.c_str())) / 2 + textwidth(m_text.c_str()) / 2;
	::outtextxy(m_x+5, ty, m_text.c_str());

	//点击自己弹出对话框
	if (isClicked()) {
		char buf[128];
		InputBox(buf, 128, m_hitText.data(),m_title.data());
		if(buf[0]!='\0')
		m_text = buf;
	}
}

bool LineEdit::textChanged()
{
	if (m_text.empty())
		return false;
	if (m_prevText == m_text) {
		return false;
	}
	m_prevText = m_text;
	return true;
}

