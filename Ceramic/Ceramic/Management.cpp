#include "Management.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include "USER.h"
#include <algorithm>
using namespace std;

Management::Management()
{
	readFile("�û�����.txt");
	::loadimage(&m_bk, "980.jpg", getwidth(), getheight());
	::settextstyle(20, 0, "����");
	//�����水ť��ʼ��
	menu_btns.emplace_back(new PushButton("��Ա����"));
	menu_btns.emplace_back(new PushButton("�����û�"));
	menu_btns.emplace_back(new PushButton("ɾ���û�"));
	menu_btns.emplace_back(new PushButton("�����û�"));
	menu_btns.emplace_back(new PushButton("�޸��û�"));
	menu_btns.emplace_back(new PushButton("�˳�ϵͳ"));

	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->setFixedSize(250, 50);

		int bx = (Window::width() - menu_btns[i]->width()) / 2;

		int vspace = (Window::height() - menu_btns.size() * menu_btns[i]->height()) / 2;
		int by = vspace + i * menu_btns[i]->height();

		menu_btns[i]->move(bx, by);
	}

	//	��ʼ���鿴�û��ı��
	m_showTable.reset(new Table);
	m_showTable->setRowCount(16);
	m_showTable->setHeader(m_header);
	updateShowTable();
	
	//�ñ�����
	m_showTable->move((Window::width() - m_showTable->width())/ 2, 40);

	//����û�
	m_addBtn.reset(new PushButton("���ӣ�",730,300,80,40));
	m_addEdit.reset(new LineEdit(400,300,300,40));
	m_addEdit->setTitle("�������û���Ϣ��");
	m_addEdit->setHitText("�밴��\n\t<�û����� �˺��� ����>\n��ʽ����ѧ����Ϣ");


	//ɾ���û�
	m_delBtn.reset(new PushButton("ɾ����", 730, 300, 80, 40));
	m_delEdit.reset(new LineEdit(400, 300, 300, 40));
	m_delEdit->setTitle("������Ҫɾ���û�������");
	m_delEdit->setHitText("������Ҫɾ���û�����");
	
	m_delTable.reset(new Table);
	m_delTable->setHeader(m_header);
	m_delTable->move(m_delEdit->x(), m_delEdit->y() + 100);
	m_delTable->setRowCount(1);

	//�����û�
	m_serBtn.reset(new PushButton("���ң�", 730, 300, 80, 40));
	m_serEdit.reset(new LineEdit(400, 300, 300, 40));
	m_serEdit->setTitle("������Ҫ�����û�������");
	m_serEdit->setHitText("������Ҫ�����û�����");

	//�޸��û�
	m_modifyBtn.reset(new PushButton("�޸ģ�",730, 300, 300, 40));
	m_modifyEdit.reset(new LineEdit(400, 300, 300, 40));
	m_modifyEdit->setTitle("������Ҫ�޸��û�������");
	m_modifyEdit->setHitText("������Ҫ�޸��û�����");

	m_modifyEdit->move((Window::width() - m_showTable->width()) / 2+150, 250);
	int x = ((Window::width() - 100 * 3 / 2));
	for (int i = 0; i < 3;i++) {
		m_useEdits.emplace_back(new LineEdit);
		m_useEdits[i]->setFixedSize(100, 40);
		m_useEdits[i]->move(x + i * m_useEdits[i]->width()-610, m_modifyEdit->y() + 50);
	}
	m_modifyIt = vec_use.end();
	
}

void Management::run()
{
	int op =Menu; 
	Window::beginDraw();//�������
	while (true)
	{
		Window::clear();
		drawBackground();
		if (Window::hasMsg())
		{
			switch (Window::getMsg().message)//�жϰ����Ƿ���ESC
			{
			case WM_KEYDOWN://��ESC�˳�������������
				if (Window::getMsg().vkcode == VK_ESCAPE) {
					m_op = Menu;
				}
				break;
			default://������
				eventLoop();
				break;
			}
		}
		
		switch (m_op)
		{
		case Management::Display:
			OpenFile();
			break;
		case Management::Add:
			addStudent();
			break;
		case Management::Delete:
			deleteStudent();
			break;
		case Management::Search:
			searchStudent();
			break;
		case Management::Update:
			updateStudent();
			break;
		case Menu:
			m_op = menu();
			break;
		default:
			saveFile("�û���Ϣ.txt");
			exit(666);
			break;
		}
		Window::flushDraw();
		Window::getMsg().message = 0;
	}
	
	Window::endDraw();
}

int Management::menu()
{
	for (int  i = 0; i < menu_btns.size(); i++)
	{

		menu_btns[i]->show();
		menu_btns[i]->event();
		if (menu_btns[i]->isClicked()) {
			//if (i == 5) {
			//	return LoginManager;// ������ö��ֵ
			//}
			return i;
		}
	}
    return Menu;
}

void Management::OpenFile()
{
	m_showTable->show();
}

void Management::addStudent()
{
	const char* title = "�������û���Ϣ<�û����� �˺��� ����>:";
	settextstyle(20, 0, "����");
	outtextxy((Window::width()-textwidth(title))/2,150,title);

	m_addBtn->show();
	m_addEdit->show();
	auto str = m_addEdit->text();
	if (m_addBtn->isClicked() && !str.empty()) {

		vec_use.push_back(USER::fromString(str));

		std::replace(str.begin(), str.end(), ' ', '\t');
		m_showTable->insertData(str);
		m_addEdit->clear();
	}
}

void Management::deleteStudent()
{
	const char* title = "������Ҫɾ���û����˺���:";
	settextstyle(20, 0, "����");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

	m_delBtn->show();
	m_delEdit->show();
	

	if (m_delTable->rowCount() != 0)
		m_delTable->show();

	auto& str = m_delEdit->text();
	if (m_delEdit->textChanged()) {
		auto it = std::find_if(vec_use.begin(), vec_use.end(), [=](const USER& use) {
			return std::to_string(use.username)==str;
		});
		if (it == vec_use.end()) {
			outtextxy(m_delEdit->x(), m_delEdit->y() + 50, std::string("�Բ���û���ҵ��û����Ϊ" + str + "���û���Ϣ").data());
		}
		else {
			m_delTable->insertData(it->formatInfo());
			//std::cout << "count" << m_delTable->rowCount() << std::endl;
		}
		
	}

	if (m_delBtn->isClicked()) {
		auto it = std::remove_if(vec_use.begin(), vec_use.end(), [=](const USER& use) {
			return std::to_string(use.username) == str;
			});
		if (it != vec_use.end()) {
			m_delEdit->clear();
			m_delTable->clear();
		}
		vec_use.erase(it, vec_use.end());
		updateShowTable();
		
		m_op = Menu;
		
	}
}

void Management::searchStudent()
{
	const char* title = "������Ҫ���ҵ��û��ı��:";
	settextstyle(20, 0, "����");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

	m_serBtn->event();
	m_serEdit->event();

}

void Management::updateStudent()
{
	const char* title = "������Ҫ�޸��û��ı��:";
	settextstyle(20, 0, "����");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

	m_modifyEdit->show();
	if (isFind) {
		for (auto& e : m_useEdits) {
			e->show();
		}
	}

	

	if (m_modifyEdit->textChanged()) {
		auto& str = m_modifyEdit->text();
		std::stringstream ss(str);

		uint32_t username;
		ss >> username;

		auto it = std::find_if(vec_use.begin(), vec_use.end(), [=](const USER& use) {
			return use.username == username;
			});
		if (it == vec_use.end()) {
			m_modifyIt = vec_use.end();
			isFind = false;
		}
		else {
			m_useEdits[0]->setText(std::to_string(it->username));
			m_useEdits[1]->setText(it->name);
			m_useEdits[2]->setText(std::to_string(it->password));

			isFind = true;
			m_modifyIt = it;
		}

	}

	if (isFind && m_modifyIt != vec_use.end())//�޸��û���Ϣ����
	{
		for (int i = 0; i < m_useEdits.size(); i++) {
			if (m_useEdits[i]->textChanged()) {
				switch (i) {
				case 0:
					m_modifyIt->username = atoi(m_useEdits[i]->text().data());
					break;
				case 1:
					m_modifyIt->name = m_useEdits[i]->text();
					break;
				case 2:
					m_modifyIt->password = atoi(m_useEdits[i]->text().data());
					break;
				default:
					break;
				}
				updateShowTable();
			}
		}
	}
}


void Management::drawBackground()
{
	::putimage(0, 0, &m_bk);
}

void Management::eventLoop()
{
	m_showTable->event();

	m_addBtn->event();
	m_addEdit->event();

	m_delBtn->event();
	m_delEdit->event();
	m_delTable->event();

	m_serBtn->event();
	m_serEdit->event();

	
	m_modifyBtn->event();
	/*m_modifyEdit->event();
	m_modifyTable->event();*/

	for (auto& e : m_useEdits) {
		e->event();
	}
}

void Management::readFile(const std::string& fileName)
{
	fstream read(fileName, ios::in);
	if (!read.is_open()) {
		return;
	}
	//��ȡ��ͷ
	char buf[1024] = { 0 };
	read.getline(buf, 1024);
	m_header = buf;//�����ͷ��Ϣ


	//��ȡ����
	while (!read.eof()) {
		char data[1024] = { 0 };
		read.getline(data, 1024);
		//��������
		if (strlen(data) == 0)
			break;
		//��ʽ����ȡ
		USER use;
		stringstream ss(data);
		ss >> use.username >> use.name >> use.password;
		vec_use.push_back(use);

		//cout << use.username << use.name << use.password << endl;//���,ÿ���һ����һ��
	}

	read.close();
}

void Management::saveFile(const std::string& fileName)
{
	fstream write(fileName, ios::out | ios::trunc);
	if (!write.is_open()) {
		cerr << fileName << "file open failed" << endl;
		return;
	}
	//д��ͷ
	m_header += "\n";
	write.write(m_header.c_str(), m_header.size());

	// д����
	for (auto& val : vec_use) {
		std::string info = val.formatInfo();
		write.write(info.c_str(),info.size());
	}

	write.close();
}

void Management::updateShowTable()
{
	m_showTable->clear();
	for (auto& val : vec_use) {
		m_showTable->insertData(val.formatInfo());
	}
}
