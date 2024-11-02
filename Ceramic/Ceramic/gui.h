#ifndef DK_GUI_H_
#define DK_GUI_H_

#include <easyx.h>

/**
 * �ؼ�ID.
 */
#ifdef _START_ID_
#define GUID __LINE__ + _START_ID_
#else
#define GUID __LINE__
#endif // !_START_ID_

typedef int ItemID;		//�ؼ�ID

/**
 * ����.
 */
struct Rect
{
	int x;
	int y;
	int w;
	int h;
};

/**
 * ��.
 */
struct Point
{
	int x;
	int y;
};

/**
 * �ߴ�.
 */
struct Size
{
	int w;
	int h;
};

/*!> ���뷽ʽ */
enum Alignment
{
	AlignTop = 1,	/*!> �������� */
	AlignBottom = 2,	/*!> �ײ����� */
	AlignLeft = 4,	/*!> ����� */
	AlignRight = 8,	/*!> �Ҷ��� */
	AlignHCenter = 16,	/*!> ˮƽ���ж��� */
	AlignVCenter = 32,	/*!> ��ֱ���ж��� */
	AlignCenter = AlignHCenter | AlignVCenter
};

/*!> ���� */
enum Orientation
{
	Horizontal,
	Vertical
};

/*!> Edit��ʾģʽ */
enum EchoMode
{
	Normal,			/*!> ������ʾ */
	Password,		/*!> ���� */
	NoEcho			/*!> ����ʾ */
};

/*UIState*/
void GUI_Init();
void GUI_Clean();
void GUI_Update(ExMessage* msg);
void GUI_Prepare();
void GUI_Finish();
void GUI_ClearFocus();

/*��ť*/
bool GUI_TextButton(ItemID id, Rect* rect, const char* text, bool lucency = false);	/*!> �ı���ť */
bool GUI_TextureButton(ItemID id, Point* pos, IMAGE* normalImg, IMAGE* hoverImg);	/*!> ͼƬ��ť */
bool GUI_LucencyButton(ItemID id, Rect* rect, bool test = false);					/*!> ͸����ť */

bool GUI_SwitchButtonEx(ItemID id, Rect* rect, bool* state, const char* offText, const char* onText);
bool GUI_SwitchButton(ItemID id, Rect* rect, bool* state);

typedef struct GroupID
{
	int id;					/*!> ��id */
	ItemID checkedItem;		/*!> ��ǰѡ�е�itemid */
	const char* itemText;	/*!> ��ǰѡ�е�item��lable */
}GroupID;
GroupID GUI_CreateGroupID();
bool GUI_RadioButton(ItemID id, Rect* rect, const char* label, bool* checked, GroupID* group = NULL);
bool GUI_CheckBox(ItemID id, Rect* rect, const char* label, bool* checked);

/*�����*/
enum EditSignal { Edit_Normal, Edit_Finish, Edit_TextChanged };
EditSignal GUI_Edit(ItemID id, Rect* rect, char* buffer, EchoMode mode = Normal);
EditSignal GUI_Edit(ItemID id, Rect* rect, char* buffer, const char* placeholder_text, EchoMode mode = Normal);
bool GUI_ChineseEdit(char* buffer, const char* def_value = NULL, const char* title = NULL, const char* hitText = NULL);

/*�ı���*/
void GUI_Label(Rect* rect, const char* text, COLORREF color = BLACK, int aliginment = AlignCenter);
void GUI_LabelFormatEx(Rect* rect, COLORREF color, int aliginment, const char* fmt, ...);
void GUI_LabelFormat(Rect* rect, const char* fmt, ...);

/*�Ի���*/
bool GUI_DialogBase(ItemID id, const char* title, const Rect* rect, Rect* clientRect);

#define GUI_DialogEx(title,width,height)\
        Rect ___rect = { (getwidth() - (width)) / 2,(getheight() - (height)) / 2,(width),(height) };\
		Rect crect;\
		if(GUI_DialogBase(GUID, title, &___rect, &crect))

#define GUI_Dialog(title) GUI_DialogEx(title,350,250)

/* ���� */
bool GUI_SliderHorizontal(ItemID id, Rect* r, int maxVal, int* value);
bool GUI_SliderVertical(ItemID id, Rect* r, int maxVal, int* value);
bool GUI_Slider(ItemID id, Rect* rect, int maxVal, int* value);

/** ��ѡ��ؼ� */
struct YearPickerData
{
	int year;
	int _startYear;
};
bool GUI_YearPicker(ItemID id, Point* pos, YearPickerData* currentYear);

/*helper*/
bool pointInRect(Point* pos, Rect* rect);
Rect* R(int x, int y, int w = -1, int h = -1);
Point* P(int x, int y);
/**
 * ��������.
 * @param size �����С��Ĭ��ֵΪ18
 * @param family �����壬Ĭ��Ϊ'����'
 */
void DK_SetFont(int size, const char* family);

/**
 * ֧��͸����ͼ����.
 */
void DK_PutImage(int x, int y, IMAGE* img);
void DK_PutImage(int dstX, int dstY, int dstWidth, int dstHeight, IMAGE* pSrcImg, int srcX, int srcY);


/*GUIStyle*/
/*��ɫ*/
typedef struct GUI_Color
{
	COLORREF color;
	COLORREF hoverColor;
}GUI_Color;
/*�߿�*/
typedef struct GUI_Border
{
	COLORREF color;
	COLORREF hoverColor;
	int width;		//�߿���
	int radius;		//Բ�ǰ뾶
}GUI_Border;
/*�ı�*/
typedef struct GUI_Text
{
	COLORREF color;
	COLORREF hoverColor;
	int size;				//���ִ�С
	const char* font;		//����
}GUI_Text;
/*��ʽ*/
typedef struct GUIStyle
{
	GUI_Color  background;
	GUI_Text   text;
	GUI_Border border;
	GUI_Color  focus;
}GUIStyle;

extern  GUIStyle ButtonStyle;	//! ��ť��ʽ
extern  GUIStyle EditStyle;		//! �༭����ʽ

void saveStyle();			//������ʽ
void restoreStyle();		//�ָ���ʽ

#endif // !DK_GUI_H_



