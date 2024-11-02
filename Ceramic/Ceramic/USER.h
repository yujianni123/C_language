#pragma once
#include "Configure.h"
using unit32 = unsigned int;
class USER
{
public:
	//����һ������
	USER();
	USER(unit32 username,const std::string name,unit32 password);
	std::string formatInfo();     //��ʽ������
	static USER fromString(const std::string& str);
public:
	//�û����� �˺��� ����
	unit32 username;
	std::string name;
	unit32 password;
};

