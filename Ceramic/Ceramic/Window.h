#pragma once
#include "Configure.h" // ȷ��ͷ�ļ�����ȷ
#include <windows.h>
#include <graphics.h>

class Window
{
public:
    Window(int w, int h, int flag); // ���캯������
    void setWindowTilte(const std::string& title);
    int exec(); // ȷ������������ȷ

    static int width(); // ȷ������������ȷ
    static int height(); // ȷ������������ȷ
    static void clear();
    static void beginDraw();
    static void flushDraw();
    static void endDraw();

    // ����������������
    inline static bool hasMsg() {
        return ::peekmessage(&m_msg/*, EM_MOUSE | EM_KEY*/);
    }

    inline static  ExMessage& getMsg() { return m_msg; } // �����﷨����

private:
    HWND m_handle; // ���ھ��
    inline static ExMessage m_msg; // �����Ϣ�ͼ�����Ϣ
};

//C++17֮ǰѧҪ��cpp�ļ�����������һ�²��� ExMessage Window::m_msg;

// ȷ�����ʵ��ĵط����幹�캯����������Ա����

