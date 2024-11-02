#pragma once
#include "Configure.h" // 确保头文件名正确
#include <windows.h>
#include <graphics.h>

class Window
{
public:
    Window(int w, int h, int flag); // 构造函数声明
    void setWindowTilte(const std::string& title);
    int exec(); // 确保返回类型正确

    static int width(); // 确保返回类型正确
    static int height(); // 确保返回类型正确
    static void clear();
    static void beginDraw();
    static void flushDraw();
    static void endDraw();

    // 按键操作和鼠标操作
    inline static bool hasMsg() {
        return ::peekmessage(&m_msg/*, EM_MOUSE | EM_KEY*/);
    }

    inline static  ExMessage& getMsg() { return m_msg; } // 修正语法错误

private:
    HWND m_handle; // 窗口句柄
    inline static ExMessage m_msg; // 鼠标消息和键盘消息
};

//C++17之前学要在cpp文件中这样定义一下才行 ExMessage Window::m_msg;

// 确保在适当的地方定义构造函数和其他成员函数

