#pragma once
#include "Window.h"
#include <vector>
#include "PushButton.h"
#include "User.h"
#include "Table.h"
#include<memory>
#include "LineEdit.h"
class Management
{
	enum Operator //操作
	{
		Display,
		Add,
		Delete,
		Search,
		Update,
		Menu=66,
		LoginManager // 添加这个枚举值
	};
public:
	Management();
	void run();//启动管理类

	int menu();//菜单

	void OpenFile();       //展示所有用户信息

    void addStudent();      //添加

	void deleteStudent();   //删除

	void searchStudent();   //查找

	void updateStudent();   //修改

	void drawBackground();
	void eventLoop();


	void readFile(const std::string& fileName);//读取文件
	void saveFile(const std::string& fileName);//保存文件

	void updateShowTable();

private:
	int m_op;
	IMAGE m_bk;

	std::vector<std::unique_ptr<PushButton>> menu_btns;

private://读取文件，保存用户信息
	std::string m_header;//表头文件
	std::vector<USER> vec_use;

private:   //查看学生表格
	std::unique_ptr<Table>  m_showTable;
	std::unique_ptr<PushButton> m_addBtn;//添加学生按钮
	std::unique_ptr<LineEdit> m_addEdit;

	std::unique_ptr<PushButton> m_delBtn;//删除学生按钮
	std::unique_ptr<LineEdit> m_delEdit;
	std::unique_ptr<Table>  m_delTable;

	std::unique_ptr<PushButton> m_serBtn;//查找学生按钮
	std::unique_ptr<LineEdit> m_serEdit;
	std::unique_ptr<Table>  m_serTable;


	std::unique_ptr<PushButton> m_modifyBtn;//修改学生
	std::unique_ptr<LineEdit> m_modifyEdit;
	std::unique_ptr<Table>  m_modifyTable;

	std::vector<std::unique_ptr<LineEdit>> m_useEdits;
	bool isFind = false;//判断是否找到

	std::vector<USER>::iterator m_modifyIt;//修改查找学生


};

