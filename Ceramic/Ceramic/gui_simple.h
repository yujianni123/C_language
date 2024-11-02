#pragma once


#include "gui.h"
#include <time.h>
#include <stdint.h>

/** ��ȡ��DK_lib���ʼ��������������ʱ�䣬��λΪ���� */
uint32_t DK_GetTicks();

/** �ȴ�ָ���ĺ�����(����) */
void DK_Delay(uint32_t ms);

/** �������[0~1]֮��ĸ����� */
float DK_Rand0_1();

/** �������[min~max)֮������� */
int	  DK_RandRange(int min, int max);

/**
 * ֡�ʿ���.
 */
struct FrameRate
{
	float fps;					/*!> ֡��*/
	uint32_t startTicks;		/*!> ÿ֡�ʿ�ʼ�ĺ���*/
	uint32_t frameTicks;		/*!> ÿ֡ʵ��С�ŵĺ���*/
};
void DK_StartFrame(FrameRate* pthis);		/*>! ÿ֡��ʼǰ���� */
void DK_EndFrame(FrameRate* pthis);			/*>! ÿ֡����ʱ���� */
void DK_SetFPS(FrameRate* pthis, float fps);	/*>! ����֡�� ��:1000/60 */

void setOnInit(void (*on_render)(void* arg));
void setOnClean(void (*on_render)(void* arg));
/**
 * ������Ⱦ�ص������л�ͼ�����������ڴ˺����н���.
 * �ص������Ĳ������û�ͨ��setUserData���������.
 */
void setOnRender(void (*on_render)(void* arg));

/**
 * ���ø��»ص�.
 */
void setOnUpdate(void (*on_update)(void* arg));

/**
 * ������Ϣ����ص�.
 */
void setOnHandleMsg(void (*on_handleMsg)(void* arg, ExMessage* msg));

/**
 * ���ûص������û�����.
 */
void setUserData(void* arg);

/**
 * ��ʼ��gui������������.
 */
HWND createWindow(int w, int h, int flags = EX_SHOWCONSOLE);
/**
 * �˳�gui�����رմ���.
 */
void quit();
/**
 * ������Ϣѭ��.
 */
void messageLoop();




