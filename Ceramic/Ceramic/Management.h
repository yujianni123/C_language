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
	enum Operator //����
	{
		Display,
		Add,
		Delete,
		Search,
		Update,
		Menu=66,
		LoginManager // ������ö��ֵ
	};
public:
	Management();
	void run();//����������

	int menu();//�˵�

	void OpenFile();       //չʾ�����û���Ϣ

    void addStudent();      //���

	void deleteStudent();   //ɾ��

	void searchStudent();   //����

	void updateStudent();   //�޸�

	void drawBackground();
	void eventLoop();


	void readFile(const std::string& fileName);//��ȡ�ļ�
	void saveFile(const std::string& fileName);//�����ļ�

	void updateShowTable();

private:
	int m_op;
	IMAGE m_bk;

	std::vector<std::unique_ptr<PushButton>> menu_btns;

private://��ȡ�ļ��������û���Ϣ
	std::string m_header;//��ͷ�ļ�
	std::vector<USER> vec_use;

private:   //�鿴ѧ�����
	std::unique_ptr<Table>  m_showTable;
	std::unique_ptr<PushButton> m_addBtn;//���ѧ����ť
	std::unique_ptr<LineEdit> m_addEdit;

	std::unique_ptr<PushButton> m_delBtn;//ɾ��ѧ����ť
	std::unique_ptr<LineEdit> m_delEdit;
	std::unique_ptr<Table>  m_delTable;

	std::unique_ptr<PushButton> m_serBtn;//����ѧ����ť
	std::unique_ptr<LineEdit> m_serEdit;
	std::unique_ptr<Table>  m_serTable;


	std::unique_ptr<PushButton> m_modifyBtn;//�޸�ѧ��
	std::unique_ptr<LineEdit> m_modifyEdit;
	std::unique_ptr<Table>  m_modifyTable;

	std::vector<std::unique_ptr<LineEdit>> m_useEdits;
	bool isFind = false;//�ж��Ƿ��ҵ�

	std::vector<USER>::iterator m_modifyIt;//�޸Ĳ���ѧ��


};

