#pragma once
#include "Configure.h"
using unit32 = unsigned int;
class USER
{
public:
	//定义一个函数
	USER();
	USER(unit32 username,const std::string name,unit32 password);
	std::string formatInfo();     //格式化函数
	static USER fromString(const std::string& str);
public:
	//用户姓名 账号名 密码
	unit32 username;
	std::string name;
	unit32 password;
};

