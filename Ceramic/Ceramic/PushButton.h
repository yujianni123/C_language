#pragma once//类的继承
#include "BasicWidget.h"
#include "Configure.h"
#include <graphics.h> // 包含EasyX图形库头文件
#include <conio.h>

class PushButton :
    public BasicWidget
{
public:
    PushButton(const std::string& text = "Button", int x = 0, int y = 0, int w = 180, int h = 56);
    void show() override;
    

    
private:
    std::string m_text;
private:
   
};
