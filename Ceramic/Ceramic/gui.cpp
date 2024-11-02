#define _CRT_SECURE_NO_WARNINGS 1
#include "gui.h"
#include <malloc.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <assert.h>
#include <time.h>
#pragma comment(lib,"msimg32.lib")
/*style*/
GUIStyle ButtonStyle = { {RGB(240,240,240),RGB(166,166,166)},{BLACK ,BLACK ,16,"Arial"},{RGB(179,202,234),RGB(179,202,234),1,10},{RGB(196,213,255)} };
GUIStyle EditStyle = { {RGB(242,245,252),RGB(252,252,252)},{BLACK ,BLACK,16,"Arial"},{RGB(133,145,162),RGB(32,61,119),1,10},{RGB(252,252,252)} };

static GUIStyle SaveButtonStyle;
static GUIStyle SaveEditStyle;

void drawFillRoundRect(Rect* rect, COLORREF fill, COLORREF border);
static void drawSolidRoundRect(const Rect& rect, COLORREF border);
void drawRoundRect(const Rect& rect, COLORREF border);
void drawkeyboardFocus(const Rect& rect);

/*UI״̬*/
struct GUIState
{
	//Mouse
	int mx;
	int my;
	bool mouseDown;
	int mouseButton;

	int hotItem;	//��굱ǰ��ͣ��item
	int activeItem;	//ӵ����꽹���item
	int lastHotItem;	//������ȵ��item

	//key
	int kbdItem;		//ӵ�м��̽����item
	int keyEntered;		//��ǰ����
	int keyModifier;	//���η�����

	//char
	char ch;

	int lastWidget;
};

static GUIState uiState = { 0,0,false };
static GroupID  gGroupId = { -1,-1,NULL };		/*!> ���û�и�radioButton ָ���飬��ʹ�����*/

/*״̬����*/
bool regionHit(Rect* rect)
{
	Point pos = { uiState.mx,uiState.my };
	return pointInRect(&pos, rect);
}
void GUI_Init()
{
	setbkcolor(RGB(232, 232, 236));
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	DK_SetFont(18, "����");

	BeginBatchDraw();

	//uiState.kbdItem = -1;	/*!> Ĭ������£�û���κ�item��ý��㡣ͨ����tab�����Ե�������*/
	GUI_ClearFocus();
}

void GUI_Clean()
{
	EndBatchDraw();
	closegraph();
}

void GUI_Update(ExMessage* msg)
{
	if (msg->message == WM_MOUSEMOVE)
	{
		uiState.mx = msg->x;
		uiState.my = msg->y;
	}
	else if (msg->message == WM_LBUTTONDOWN)
	{
		uiState.mouseDown = true;
		uiState.mouseButton = WM_LBUTTONDOWN;
	}
	else if (msg->message == WM_LBUTTONUP)
	{
		uiState.mouseDown = false;
		uiState.mouseButton = 0;
	}
	else if (msg->message == WM_RBUTTONDOWN)
	{
		uiState.mouseButton = WM_RBUTTONDOWN;
	}
	else if (msg->message == WM_RBUTTONUP)
	{
		uiState.mouseButton = 0;
	}
	else if (msg->message == WM_CHAR)
	{
		uiState.ch = msg->ch;
	}
	else if (msg->message == WM_KEYDOWN)
	{
		uiState.keyEntered = msg->vkcode;
		uiState.keyModifier |= msg->ctrl ? 2 : (msg->shift ? 4 : 0);
	}
	else if (msg->message == WM_KEYUP)
	{
	}
}

void GUI_Prepare()
{
	cleardevice();

	//ÿ֡��ʼʱ�����������ͣ
	uiState.hotItem = 0;
}

void GUI_Finish()
{
	FlushBatchDraw();

	//������û�а���
	if (!uiState.mouseDown)
	{
		//ȡ������
		uiState.activeItem = 0;
	}
	//�����갴����
	else
	{
		if (uiState.activeItem == 0)
			uiState.activeItem = -1;

	}

	if (uiState.keyEntered == VK_TAB)
		uiState.kbdItem = 0;
	uiState.keyEntered = 0;
	uiState.ch = 0;
}

void GUI_ClearFocus()
{
	uiState.kbdItem = -1;	/*!> Ĭ������£�û���κ�item��ý��㡣ͨ����tab�����Ե�������*/
}

//����Ƿ���ĳ��������ͣ���߰�����
static bool mouseHotActiveHandle(ItemID id, Rect* rect)
{
	//����Ƿ��������������
	if (regionHit(rect))
	{
		//��ǰӵ������ȵ㣨�����ͣ����item
		uiState.hotItem = id;

		//������û�а��£���ô�ͽ��˿ؼ��������һ����ȡ�ȵ�Ŀؼ���������û�а��£���ôlastHotItem��hotItem��һ���ģ�
		//����Ϊ�˼�¼����������ĸ��ؼ�����Ϊ�����slider���϶�ʱ��������hot�ƶ����˱�Ŀؼ�����ô��ʱslier��ʧȥhot��active�����϶�ʧЧ
		//��������˵��ʱ�����ڵĿؼ�����ô���ԶԴ˽����ж�(������)
		if (!uiState.mouseDown)
			uiState.lastHotItem = id;

		//�������ȡ�ȵ�Ŀؼ������Լ�����ô��ʾ�������ؼ����ڴ����Լ��������ȵ㣨��������ť���ɿ����ٰ�����ƶ��������ؼ���ʱ�������ؼ����ܻ�ȡ�ȵ㣩
		if (uiState.lastHotItem != id)
			uiState.hotItem = 0;

		//�����갴���ˣ�������������hot���Ǳ��ؼ���������Ϊ����
		if (uiState.mouseDown && uiState.lastHotItem == id)
		{
			uiState.activeItem = id;
			return true;
		}
	}
	return false;
}
//���̽���
static bool keyboardHot(ItemID id, Rect* rect)
{
	//���̽���
	if (uiState.kbdItem == 0)
		uiState.kbdItem = id;

	if (uiState.kbdItem == id)
	{
		Rect drect = { rect->x - 1,rect->y - 1,rect->w + 2,rect->h + 2 };
		drawkeyboardFocus(drect);
	}

	if (uiState.kbdItem == id)
	{
		switch (uiState.keyEntered)
		{
		case VK_TAB:
			uiState.kbdItem = 0;

			//���������shift
			if (uiState.keyModifier & 4)
				uiState.kbdItem = uiState.lastWidget;

			uiState.keyEntered = 0;
			break;
		case VK_RETURN:		//�س�
			return true;
			break;
		}
	}
	uiState.lastWidget = id;
	return false;
}


/*�ؼ�*/
/* Button*/
bool GUI_TextButton(ItemID id, Rect* rect, const char* text, bool lucency)
{
	if (mouseHotActiveHandle(id, rect))
	{
		uiState.hotItem = id;
		//���û�л�ȡ�����item��������갴���ˣ��ͻ�ȡ����
		if (uiState.activeItem == 0 && uiState.mouseDown)
			uiState.activeItem = id;
	}

	if (!lucency)
	{
		//�������ڵ�ǰ��ť����ͣ
		if (uiState.hotItem == id)
		{
			//�����н���
			if (uiState.activeItem == id)
			{
				drawFillRoundRect(rect, ButtonStyle.focus.color, ButtonStyle.focus.color);
			}
			else
			{
				drawFillRoundRect(rect, ButtonStyle.background.hoverColor, ButtonStyle.border.hoverColor);
			}
		}
		else
		{
			drawFillRoundRect(rect, ButtonStyle.background.color, ButtonStyle.border.color);
		}
	}
	//�����ı�
	outtextxy(rect->x + (rect->w - textwidth(text)) / 2,
		rect->y + (rect->h - textheight(text)) / 2, text);

	if (keyboardHot(id, rect))
		return true;

	//��굯��ʱ�������
	if (uiState.mouseDown == false && uiState.hotItem == id && uiState.activeItem == id)
		return true;

	return false;
}

bool GUI_TextureButton(ItemID id, Point* pos, IMAGE* normalImg, IMAGE* hoverImg)
{
	if (!normalImg)
		return false;

	Rect rect = { pos->x, pos->y, normalImg->getwidth(), normalImg->getheight() };
	if (mouseHotActiveHandle(id, &rect))
	{
		uiState.hotItem = id;
		//���û�л�ȡ�����item��������갴���ˣ��ͻ�ȡ����
		if (uiState.activeItem == 0 && uiState.mouseDown)
			uiState.activeItem = id;
	}

	//�������ڵ�ǰ��ť����ͣ
	if (uiState.hotItem == id && hoverImg)
	{
		DK_PutImage(pos->x - 1, pos->y - 1, hoverImg);
	}
	else
	{
		DK_PutImage(pos->x, pos->y, normalImg);
	}

	if (keyboardHot(id, &rect))
		return true;

	//��굯��ʱ�������
	if (uiState.mouseDown == false && uiState.hotItem == id && uiState.activeItem == id)
		return true;

	return false;
}

bool GUI_LucencyButton(ItemID id, Rect* rect, bool test)
{
	if (mouseHotActiveHandle(id, rect))
	{
		uiState.hotItem = id;
		//���û�л�ȡ�����item��������갴���ˣ��ͻ�ȡ����
		if (uiState.activeItem == 0 && uiState.mouseDown)
			uiState.activeItem = id;
	}

	if (test)
	{
		COLORREF tmp = getlinecolor();
		//�������ڵ�ǰ��ť����ͣ
		if (uiState.hotItem == id)
		{
			setlinecolor(ButtonStyle.border.color);
			rectangle(rect->x, rect->y, rect->x + rect->w, rect->y + rect->h);
		}
		else
		{
			setlinecolor(ButtonStyle.border.hoverColor);
			rectangle(rect->x, rect->y, rect->x + rect->w, rect->y + rect->h);
		}
		setlinecolor(tmp);
	}

	if (keyboardHot(id, rect))
		return true;

	//��굯��ʱ�������
	if (uiState.mouseDown == false && uiState.hotItem == id && uiState.activeItem == id)
		return true;

	return false;
}

bool GUI_SwitchButtonEx(ItemID id, Rect* rect, bool* state, const char* offText, const char* onText)
{
	if (!state) return false;

	//����Ƿ��������������
	mouseHotActiveHandle(id, rect);

	//���ư�ť
	if (uiState.hotItem == id || uiState.activeItem == id)
	{
		drawFillRoundRect(rect, RGB(171, 239, 250), RGB(16, 124, 16));
	}
	else
	{
		drawFillRoundRect(rect, RGB(230, 231, 232), RGB(16, 124, 16));
	}

	//�����ڲ���Сָʾ��
	int interval = 5;	//ָʾ��������߿�ľ���
	Rect leftRect = { rect->x + interval,rect->y + interval,rect->w / 2 - interval,rect->h - 2 * interval };
	Rect rightRect = { rect->x + rect->w / 2 + interval,rect->y + interval,rect->w / 2 - 2 * interval,rect->h - 2 * interval };

	if (!*state)
	{
		drawFillRoundRect(&leftRect, RGB(129, 217, 233), RGB(69, 199, 222));
	}
	else
	{
		drawFillRoundRect(&rightRect, RGB(129, 217, 233), RGB(69, 199, 222));
	}
	GUI_Label(&leftRect, offText, BLACK, AlignCenter);
	GUI_Label(&rightRect, onText, BLACK, AlignCenter);


	if (keyboardHot(id, rect))
	{
		*state = !*state;
		return true;
	}

	//�Ƿ����˰�ť
	if (!uiState.mouseDown && uiState.hotItem == id && uiState.activeItem == id)
	{
		*state = !*state;
		return true;
	}

	return false;
}

bool GUI_SwitchButton(ItemID id, Rect* rect, bool* state)
{
	return GUI_SwitchButtonEx(id, rect, state, "��", "��");
}

GroupID GUI_CreateGroupID()
{
	static int lastid = 0;
	return GroupID{ lastid++ ,0,NULL };
}

bool GUI_RadioButton(ItemID id, Rect* rect, const char* label, bool* checked, GroupID* group)
{
	if (!checked)
		return false;
	if (!group)
		group = &gGroupId;

	mouseHotActiveHandle(id, rect);


	int ir = rect->h / 2 - 10;
	int ix = rect->x + ir + 5;
	int iy = rect->y + rect->h / 2;

	//if (uiState.hotItem == id)
	//{
	//	if (uiState.activeItem == id)
	//	{
	//		//drawFillRoundRect(rect, RGB(196, 213, 255), RGB(16, 124, 16));
	//	}
	//	else
	//	{
	//		//drawFillRoundRect(rect, RGB(104, 104, 104), RGB(16, 124, 16));
	//	}
	//}
	//else
	{
		setlinecolor(BLACK);
		circle(ix, iy, ir);
	}



	if (*checked)
	{
		setfillcolor(BLACK);
		solidcircle(ix, iy, ir - 2);
	}

	Rect drect = { ix + ir + 5,rect->y,rect->w - (ix + iy + 5 - rect->x),rect->h };
	GUI_Label(&drect, label, BLACK, AlignLeft | AlignVCenter);

	//���ѡ�еĲ����Լ���ȡ��ѡ��
	if (group->checkedItem != -1 && //�����û��ѡ�У�ֱ�Ӻ���
		group->checkedItem != id && *checked == true)
	{
		*checked = false;
		group->itemText = NULL;
	}
	//�м��̽��㣬�������˻س�����ѡ��
	if (keyboardHot(id, rect))
	{
		*checked = !*checked;
		group->checkedItem = id;
		group->itemText = label;
		return true;
	}
	//������ˣ���ѡ��
	if (!uiState.mouseDown && uiState.hotItem == id && uiState.activeItem == id)
	{
		//����Լ�û��ѡ�У���ѡ�У�����ѡ��һ����
		if (group->checkedItem != id && *checked == false)
			*checked = true;
		//*checked = !*checked;
		group->checkedItem = id;
		group->itemText = label;
		return true;
	}
	return false;
}

bool GUI_CheckBox(ItemID id, Rect* rect, const char* label, bool* checked)
{
	if (!checked) return false;
	mouseHotActiveHandle(id, rect);

	Rect indRect = { rect->x + 5,rect->y + (rect->h - rect->h * 0.5) / 2,rect->h * 0.5,rect->h * 0.5 };


	//if (uiState.hotItem == id)
	//{
	//	if (uiState.activeItem == id)
	//	{
	//		drawFillRoundRect(rect, RGB(196, 213, 255), RGB(16, 124, 16));
	//	}
	//	else
	//	{
	//		drawFillRoundRect(rect, RGB(104, 104, 104), RGB(16, 124, 16));
	//	}
	//}
	//else
	{
		drawRoundRect(indRect, RGB(125, 125, 125));
	}

	if (*checked)
	{
		Rect trect = indRect;
		trect.x += 2;
		trect.y += 2;
		trect.w -= 4;
		trect.h -= 4;
		drawSolidRoundRect(trect, RGB(125, 125, 125));
	}

	Rect drect = { indRect.x + indRect.w + 5,rect->y, rect->w - (indRect.x + indRect.w + 5),rect->h };
	GUI_Label(&drect, label, BLACK, AlignLeft | AlignVCenter);

	if (keyboardHot(id, rect))
	{
		*checked = !*checked;
		return true;
	}

	if (!uiState.mouseDown && uiState.hotItem == id && uiState.activeItem == id)
	{
		*checked = !*checked;
		return true;
	}

	return false;
}



/* edit */
EditSignal GUI_Edit(ItemID id, Rect* rect, char* buffer, EchoMode mode)
{
	return GUI_Edit(id, rect, buffer, "", mode);
}

EditSignal GUI_Edit(ItemID id, Rect* rect, char* buffer, const char* placeholder_text, EchoMode mode)
{
	if (mouseHotActiveHandle(id, rect))
	{
		uiState.hotItem = id;
		if (uiState.activeItem == 0 && uiState.mouseDown)
		{
			uiState.activeItem = id;
		}
	}


	if (uiState.hotItem == id)
	{
		if (uiState.activeItem == id)
		{
			drawFillRoundRect(rect, RGB(166, 166, 166), RGB(43, 145, 175));
		}
		else
		{
			drawFillRoundRect(rect, RGB(231, 231, 231), RGB(43, 145, 175));
		}
	}
	else
	{
		drawFillRoundRect(rect, RGB(255, 255, 255), RGB(115, 198, 221));
	}


	int len = strlen(buffer);
	//bool changed = false;
	EditSignal sig = Edit_Normal;

	//�����ı�
	if (mode == Normal)
	{
		outtextxy(rect->x + 5, rect->y + (rect->h - textheight(buffer)) / 2, buffer);

		if (uiState.kbdItem == id && (clock() >> 9) & 1)
			outtextxy(rect->x + 5 + textwidth(buffer), rect->y + (rect->h - textheight("|")) / 2, "|");
	}
	else if (mode == Password)
	{
		for (int i = 0; i < len; i++)
		{
			outtextxy(rect->x + 5 + i * textwidth('*'), rect->y + (rect->h - textheight('*')) / 2, '*');
		}

		if (uiState.kbdItem == id && (clock() >> 9) & 1)
			outtextxy(rect->x + 5 + textwidth(buffer), rect->y + (rect->h - textheight("|")) / 2, "|");
	}
	else
	{
		if (uiState.kbdItem == id && (clock() >> 9) & 1)
			outtextxy(rect->x + 5, rect->y + (rect->h - textheight("|")) / 2, "|");
	}


	//����ռλ�ı�
	if (buffer[0] == '\0' && uiState.kbdItem != id)
	{
		COLORREF c = gettextcolor();
		settextcolor(RGB(127, 127, 127));
		outtextxy(rect->x + 5, rect->y + (rect->h - textheight(placeholder_text)) / 2, placeholder_text);
		settextcolor(c);
	}

	//���û�пؼ��м��̽��㣬��ȡ��
	if (uiState.kbdItem == 0)
		uiState.kbdItem = id;

	if (uiState.kbdItem == id)
	{
		drawkeyboardFocus(*rect);
	}

	if (uiState.kbdItem == id)
	{
		switch (uiState.keyEntered)
		{
		case VK_TAB:
			uiState.kbdItem = 0;
			//��tab�����ý����л�����һ�������
			if (uiState.keyModifier & 4)
				uiState.kbdItem = uiState.lastWidget;

			uiState.keyEntered = 0;

			break;
		case '\b':
			//���뻹�������ַ��������������ַ����һ�����ģ���ɾ���������������ÿ���ֽڶ��Ǹ�����
			if (len > 1 && buffer[len - 1] < 0 && buffer[len - 2] < 0)
			{
				buffer[len - 2] = '\0';
				//changed = true;
				sig = Edit_TextChanged;
			}
			//ɾ��һ���ַ�
			else if (len > 0)
			{
				buffer[len - 1] = '\0';
				//changed = true;
				sig = Edit_TextChanged;
			}

			break;
		case '\r':
		case '\n':
			uiState.kbdItem = -1;	//�������
			sig = Edit_Finish;
			//return changed;
			break;
		default:
			//���ֻ������size-1����
			//if (len < size)
		{
			//ֻ���ܿɴ�ӡ�ַ�����������
			if ((uiState.ch >= 32 && uiState.ch < 127) || uiState.ch < 0)
			{
				buffer[len++] = uiState.ch;
				buffer[len] = '\0';
				//changed = true;
				sig = Edit_TextChanged;
			}
		}

		break;
		}
	}

	if (uiState.mouseDown == false &&
		uiState.hotItem == id &&
		uiState.activeItem == id)
	{
		uiState.kbdItem = id;
	}
	uiState.lastWidget = id;
	return sig;
}

bool GUI_ChineseEdit(char* buffer, const char* def_value, const char* title, const char* hitText)
{
	return InputBox(buffer, 128, hitText, title, def_value);
}

/* label */
void GUI_Label(Rect* rect, const char* text, COLORREF color, int aliginment)
{
	int tx = rect->x, ty = rect->y;
	if (rect->w != 0 && rect->h != 0)
	{
		int tw = textwidth(text);
		int th = textheight(text);

		int hspace = (rect->w - tw) / 2;
		int vspace = (rect->h - th) / 2;

		//���뷽ʽ
		if (aliginment & AlignTop)
			ty = rect->y;

		if (aliginment & AlignBottom)
			ty = rect->y + rect->h - th;

		if (aliginment & AlignLeft)
			tx = rect->x;

		if (aliginment & AlignRight)
			tx = rect->x + rect->w - tw;

		if (aliginment & AlignHCenter)
			tx = rect->x + hspace;

		if (aliginment & AlignVCenter)
			ty = rect->y + vspace;
	}
	settextcolor(color);
	outtextxy(tx, ty, text);
}
void GUI_LabelFormatEx(Rect* rect, COLORREF color, int aliginment, const char* fmt, ...)
{
	va_list alist;
	va_start(alist, fmt);

	char buf[256];
	vsnprintf(buf, 128, fmt, alist);
	GUI_Label(rect, buf, color, aliginment);

	va_end(alist);
}
void GUI_LabelFormat(Rect* rect, const char* fmt, ...)
{
	va_list alist;
	va_start(alist, fmt);

	char buf[256];
	vsnprintf(buf, 128, fmt, alist);
	GUI_Label(rect, buf, BLACK, AlignCenter);

	va_end(alist);
}

/* dialog */
bool GUI_DialogBase(ItemID id, const char* title, const Rect* rect, Rect* clientRect)
{
	DK_SetFont(26, "����");
	mouseHotActiveHandle(id, (Rect*)rect);
	//�����Ի��� + �߿�
	if (!regionHit((Rect*)rect) && uiState.mouseDown)
	{
		Rect* rr = (Rect*)rect;
		rr->x -= 2;
		rr->y -= 2;
		rr->w += 2 * 2;
		rr->h += 2 * 2;
	}
	//���ƶԻ���
	drawFillRoundRect((Rect*)rect, RGB(225, 225, 225), RGB(115, 198, 221));

	//���Ʊ������������
	setlinecolor(ButtonStyle.border.color);
	Rect r = { rect->x + 1,rect->y + 38,rect->w - 2,rect->h - 39 };
	line(r.x, r.y - 3, r.x + r.w, r.y - 3);

	//�����ͻ�������
	if (clientRect) *clientRect = r;

	//���Ʊ���
	settextstyle(18, 0, "Arial");
	Rect titleR = { rect->x + 5,rect->y + 0,textwidth(title),39 };
	GUI_Label(&titleR, title, 0, AlignVCenter);

	//�رհ�ť
	Rect closeR = { rect->x + rect->w - 33,rect->y + 1,32,32 };

	if (GUI_TextButton(id + 10000, &closeR, "��"))
	{
		return true;
	}
	return false;
}

/* slider */
bool GUI_SliderHorizontal(ItemID id, Rect* r, int maxVal, int* value)
{
	//���㻬��Ļ����С
	int handleSize = r->h / 2;

	//�������������yƫ����
	int xPos = ((r->w - handleSize * 1.5) * *value) / maxVal;

	//������������ƶ�������������ܻ�������
	Rect rect = { r->x + handleSize / 2, r->y + handleSize / 2, r->w - handleSize / 2, handleSize };
	mouseHotActiveHandle(id, &rect);
	//�����
	{
		Rect tRect = { r->x, r->y, r->w + handleSize / 2, r->h };
		drawFillRoundRect(&tRect, RGB(119, 119, 119), RGB(119, 119, 119));

	}
	//������
	{
		Rect tRect = { rect.x, rect.y, rect.w - handleSize / 2, rect.h };
		drawFillRoundRect(&rect, RGB(71, 71, 71), RGB(71, 71, 71));
	}

	//����꽹����������ͣ
	if (uiState.activeItem == id || uiState.hotItem == id)
	{
		Rect tRect = { r->x + handleSize / 2 + xPos, r->y + handleSize / 2, handleSize, handleSize };
		drawFillRoundRect(&tRect, WHITE, WHITE);
	}
	else
	{
		Rect tRect = { r->x + handleSize / 2 + xPos, r->y + handleSize / 2, handleSize, handleSize };
		drawFillRoundRect(&tRect, RGB(170, 170, 170), RGB(170, 170, 170));
	}

	// If no widget has keyboard focus, take it
	if (uiState.kbdItem == 0)
		uiState.kbdItem = id;

	// ���Ƽ��̽���
	if (uiState.kbdItem == id)
	{
		Rect tRect = { r->x, r->y, r->w + handleSize / 2, r->h };
		drawkeyboardFocus(tRect);
	}


	// If we have keyboard focus, we'll need to process the keys
	if (uiState.kbdItem == id)
	{
		switch (uiState.keyEntered)
		{
		case VK_TAB:
			// If tab is pressed, lose keyboard focus.
			// Next widget will grab the focus.
			uiState.kbdItem = 0;
			// If shift was also pressed, we want to move focus
			// to the previous widget instead.
			if (uiState.keyModifier & VK_SHIFT)
				uiState.kbdItem = uiState.lastWidget;
			// Also clear the key so that next widget
			// won't process it
			uiState.keyEntered = 0;
			break;
		case VK_LEFT:
			// Slide slider up (if not at zero)
			if (*value > 0)
			{
				(*value)--;
				return 1;
			}
			break;
		case VK_RIGHT:
			// Slide slider down (if not at max)
			if (*value < maxVal)
			{
				(*value)++;
				return 1;
			}
			break;
		}
	}

	uiState.lastWidget = id;

	// Update widget value
	if (uiState.activeItem == id)
	{
		int mousepos = uiState.mx - (r->x + handleSize / 2);
		if (mousepos < 0) mousepos = 0;
		if (mousepos > r->w) mousepos = r->w;
		int v = (mousepos * maxVal) / r->w;
		if (v != *value)
		{
			*value = v;
			return true;
		}
	}
	return false;
}

bool GUI_SliderVertical(ItemID id, Rect* r, int maxVal, int* value)
{
	//���㻬��Ļ����С
	int handleSize = r->w / 2;

	//�������������yƫ����
	int yPos = ((r->h - handleSize * 1.5) * *value) / maxVal;

	Rect rect = { r->x + handleSize / 2, r->y + handleSize / 2, handleSize, r->h - handleSize / 2 };
	mouseHotActiveHandle(id, &rect);
	//�����
	{
		Rect tRect = { r->x, r->y, r->w, r->h + handleSize / 2 };
		drawFillRoundRect(&tRect, RGB(119, 119, 119), RGB(119, 119, 119));
	}

	//������
	{
		drawFillRoundRect(&rect, RGB(71, 71, 71), RGB(71, 71, 71));
	}

	//����꽹����������ͣ
	if (uiState.activeItem == id || uiState.hotItem == id)
	{
		Rect tRect = { r->x + handleSize / 2, r->y + handleSize / 2 + yPos, handleSize, handleSize };
		drawFillRoundRect(&tRect, WHITE, WHITE);
	}
	else
	{
		Rect tRect = { r->x + handleSize / 2, r->y + handleSize / 2 + yPos, handleSize, handleSize };
		drawFillRoundRect(&tRect, RGB(170, 170, 170), RGB(170, 170, 170));
	}


	// If no widget has keyboard focus, take it
	if (uiState.kbdItem == 0)
		uiState.kbdItem = id;

	// ���Ƽ��̽���
	if (uiState.kbdItem == id)
	{
		drawkeyboardFocus({ r->x, r->y, r->w, r->h + handleSize / 2 });
	}


	// If we have keyboard focus, we'll need to process the keys
	if (uiState.kbdItem == id)
	{
		switch (uiState.keyEntered)
		{
		case VK_TAB:
			// If tab is pressed, lose keyboard focus.
			// Next widget will grab the focus.
			uiState.kbdItem = 0;
			// If shift was also pressed, we want to move focus
			// to the previous widget instead.
			if (uiState.keyModifier & VK_SHIFT)
				uiState.kbdItem = uiState.lastWidget;
			// Also clear the key so that next widget
			// won't process it
			uiState.keyEntered = 0;
			break;
		case VK_UP:
			// Slide slider up (if not at zero)
			if (*value > 0)
			{
				(*value)--;
				return 1;
			}
			break;
		case VK_DOWN:
			// Slide slider down (if not at max)
			if (*value < maxVal)
			{
				(*value)++;
				return 1;
			}
			break;
		}
	}

	uiState.lastWidget = id;

	// Update widget value
	if (uiState.activeItem == id)
	{
		int mousepos = uiState.my - (r->y + handleSize / 2);
		if (mousepos < 0) mousepos = 0;
		if (mousepos > r->h) mousepos = r->h;
		int v = (mousepos * maxVal) / r->h;
		if (v != *value)
		{
			*value = v;
			return true;
		}
	}
	return false;
}

bool GUI_Slider(ItemID id, Rect* rect, int maxVal, int* value)
{
	if (!value) return false;

	enum Orientation orien = rect->w > rect->h ? Horizontal : Vertical;
	bool sliderMoved = false;
	switch (orien)
	{
	case Horizontal:
		sliderMoved = GUI_SliderHorizontal(id, rect, maxVal, value);
		break;
	case Vertical:
		sliderMoved = GUI_SliderVertical(id, rect, maxVal, value);
		break;
	}
	return sliderMoved;
}

bool GUI_YearPicker(ItemID id, Point* pos, YearPickerData* currentYear)
{
	//׼������
	static Size size = { 230, 250 };	//�ؼ���С
	static const int	ROWS = 4;
	static const int	COLS = 3;

	static Point index = { -1,-1 };

	if (!currentYear)
		return false;

	if (currentYear->year <= 0)
	{
		time_t tim;
		time(&tim);
		tm* t = localtime(&tim);
		currentYear->year = 1900 + t->tm_year;
		currentYear->_startYear = currentYear->year;
	}

	int boundWidth = size.w / COLS;
	int boundHeight = (size.h - 35) / ROWS;
	int realWidth = 50;
	int realHeight = 30;
	int hSpace = (boundWidth - realWidth) / 2;
	int vSpace = (boundHeight - realHeight) / 2;
	/*if (uiState.mx >= pos->x && uiState.mx <= pos->x + size.w &&
		uiState.my >= pos->y + 35 && uiState.my <= pos->y + size.h)
	{
		int r = (uiState.my - pos->y - 35) / boundHeight;
		int c = (uiState.mx - pos->x) / boundWidth;
		index = { r,c };
		if (uiState.mouseDown)
		{
			currentYear->_isChecked = true;
		}
	}
	else
	{
		index = { -1,-1 };
	}
	*/

	//���������ؼ�����
	setfillcolor(WHITE);
	fillroundrect(pos->x, pos->y, pos->x + size.w, pos->y + size.h, 10, 10);

	//���Ƶ�����
	line(pos->x, pos->y + 35, pos->x + size.w, pos->y + 35);

	Rect barRect = { pos->x, pos->y,  size.w,35 };
	char str[128];
	sprintf(str, "%d", currentYear->year);
	GUI_Label(&barRect, str);

	if (GUI_LucencyButton(GUID + id, R(barRect.x + 95, barRect.y + 2, 40, 32)))
	{
		currentYear->_startYear = currentYear->year;
	}
	if (GUI_TextButton(GUID + id, R(barRect.x + 10, barRect.y, 32, 32), "<", true))
	{
		currentYear->_startYear -= ROWS * COLS;
	}
	if (GUI_TextButton(GUID + id, R(barRect.x + barRect.w - 32, barRect.y, 32, 32), ">", true))
	{
		currentYear->_startYear += ROWS * COLS;
	}

	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			int x = c * boundWidth + pos->x;
			int y = r * boundHeight + pos->y + 35;

			COLORREF textColor;

			if (currentYear->year == currentYear->_startYear + r * COLS + c)
			{
				setfillcolor(RGB(9, 132, 216));
				textColor = WHITE;
			}
			else
			{
				Point mpos = { uiState.mx,uiState.my };
				Rect yearRect = { x + hSpace, y + vSpace, realWidth, realHeight };
				if (pointInRect(&mpos, &yearRect))
				{
					setfillcolor(RGB(194, 195, 201));
					textColor = BLACK;

					if (GUI_LucencyButton(id + r * COLS + c, &yearRect))
					{
						currentYear->year = currentYear->_startYear + r * COLS + c;
						return true;
					}
					//if (uiState.mouseDown)
					//{
					//	currentYear->year = currentYear->_startYear + r * COLS + c;
					//}
				}
				else
				{
					setfillcolor(WHITE);
					textColor = RGB(194, 195, 201);
				}
			}


			fillroundrect(x + hSpace, y + vSpace, x + hSpace + realWidth, y + vSpace + realHeight, 10, 10);

			Rect rect = { x + hSpace, y + vSpace,  realWidth , realHeight };
			GUI_LabelFormatEx(&rect, textColor, AlignCenter, "%d", currentYear->_startYear + r * COLS + c);
		}
	}

	return false;
}


/* helper */
void DK_SetFont(int size, const char* family)
{
	static LOGFONT font = { 0 };
	font.lfHeight = size;
	strcpy(font.lfFaceName, family);
	settextstyle(&font);
}

void DK_PutImage(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

void DK_PutImage(int dstX, int dstY, int dstWidth, int dstHeight, IMAGE* img, int srcX, int srcY)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), dstX, dstY, dstWidth, dstHeight,
		GetImageHDC(img), srcX, srcY, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

bool pointInRect(Point* pos, Rect* rect)
{
	return pos->x >= rect->x && pos->x <= rect->x + rect->w && pos->y >= rect->y && pos->y <= rect->y + rect->h;
}

Rect* R(int x, int y, int w, int h)
{
	static Rect r = { 0 };
	if (w == -1 || h == -1) {
		w = 150;
		h = 35;
	}
	r = { x,y,w,h };
	return &r;
}
Point* P(int x, int y)
{
	static Point p = { 0 };
	p = { x,y };
	return &p;
}

static void drawFillRoundRect(Rect* rect, COLORREF fill, COLORREF border)
{
	setfillcolor(fill);
	setlinecolor(border);
	fillroundrect(rect->x, rect->y, rect->x + rect->w, rect->y + rect->h, 10, 10);
}

static void drawSolidRoundRect(const Rect& rect, COLORREF c)
{
	setfillcolor(c);
	solidroundrect(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, 10, 10);
}

static void drawRoundRect(const Rect& rect, COLORREF border)
{
	setlinecolor(border);
	roundrect(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, 10, 10);
}

static void drawRect(const Rect& rect, COLORREF border)
{
	setlinecolor(border);
	rectangle(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
}

static void drawkeyboardFocus(const Rect& rect)
{
	LINESTYLE lineStyle;
	getlinestyle(&lineStyle);

	setlinecolor(RGB(165, 165, 165));
	setlinestyle(PS_DASH);
	roundrect(rect.x - 1, rect.y - 1, rect.x + rect.w + 1, rect.y + rect.h + 1, 10, 10);

	setlinestyle(&lineStyle);
}


void saveStyle()
{
	SaveButtonStyle = ButtonStyle;
	SaveEditStyle = EditStyle;
}

void restoreStyle()
{
	ButtonStyle = SaveButtonStyle;
	EditStyle = SaveEditStyle;
}




