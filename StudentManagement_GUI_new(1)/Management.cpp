#include "Management.h"
#include<conio.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
using namespace std;
Management::Management()
{
	readFile("�û�����.txt");
	::loadimage(&m_bk, "980.jpg", Window::width(), Window::height());
	::settextstyle(20, 0, "����");
	//�����水ť��ʼ��
	menu_btns.emplace_back(new PushButton("�鿴ѧ��"));
	menu_btns.emplace_back(new PushButton("���ѧ��"));
	menu_btns.emplace_back(new PushButton("ɾ��ѧ��"));
	menu_btns.emplace_back(new PushButton("�޸�ѧ��"));
	menu_btns.emplace_back(new PushButton("����ѧ��"));
	menu_btns.emplace_back(new PushButton("�˳�ϵͳ"));
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->setFixedSize(250, 50);
		
		int bx = (Window::width() - menu_btns[i]->width())/2;

		int vspace = (Window::height() - menu_btns.size()* menu_btns[i]->height()) / 2;
		int by = vspace + i * menu_btns[i]->height();

		menu_btns[i]->move(bx,by);
	}

	//��ʼ���鿴ѧ���ı��
	m_showTable.reset(new Table);
	m_showTable->setRowCount(16);
	m_showTable->setHeader(m_header);
	updateShowTable();

	//�ñ�����
	m_showTable->move((Window::width()-m_showTable->width())/2, 40);	


	//���ѧ��
	m_addBtn.reset(new PushButton("���ӣ�", 730, 300, 80, 40));
	m_addEdit.reset(new LineEdit(400, 300, 300, 40));
	m_addEdit->setTitle("�������û��˺���");
	m_addEdit->setHitText("�밴��\n\t<�˺���	�û�����	����>\n��ʽ����ѧ����Ϣ");


	//ɾ��ѧ��
	m_delBtn.reset(new PushButton("ɾ��", 730, 300, 80, 40));
	m_delEdit.reset(new LineEdit(400, 300, 300, 40));
	m_delEdit->setTitle("������ɾ���û��˺���");
	m_delEdit->setHitText("������ɾ���û��˺���");

	m_delTable.reset(new Table);
	m_delTable->setHeader(m_header);
	m_delTable->move(m_delEdit->x(), m_delEdit->y() + 100);
	m_delTable->setRowCount(1);

	//�޸�
	m_modifyEdit.reset(new LineEdit(400, 300, 300, 40));
	m_modifyEdit->move((Window::width() - m_modifyEdit->width()) / 2, 260);
	int x = (Window::width() - 100*3)/2;
	for (int i = 0; i < 3; i++)
	{
		m_stuEdits.emplace_back(new LineEdit);
		m_stuEdits[i]->setFixedSize(100, 40);
		m_stuEdits[i]->move(x + i * m_stuEdits[i]->width() - 610, m_modifyEdit->y() + 50);
	}
	m_modifyIt = vec_stu.end();
}
void Management::run()
{
	//��ȡ�˵��ķ���ֵ
	m_op = Menu;
	Window::beginDraw();
	while (true)
	{
		Window::clear();
		drawBackground();
		
		if (Window::hasMsg())
		{
			switch (Window::getMsg().message)
			{
			case WM_KEYDOWN:	//��������
				//��ESC�˳�����������������
				if (Window::getMsg().vkcode == VK_ESCAPE)
				{
					m_op = Menu;
				}
				break;
			default:		//������
				enevtLoop();
				break;
			}
		}

		
		switch (m_op)
		{
		case Menu:
			m_op = menu();
			break;
		case Management::Display:
			display();
			break;
		case Management::Insert:
			add();
			break;
		case Management::Remove:
			erase();
			break;
		case Management::Modify:
			modify();
			break;
		case Management::Search:
			search();
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
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->show();
		menu_btns[i]->event();
		if (menu_btns[i]->isClicked())
		{
			return i;
		}
	}
	return Menu;
}

void Management::display()
{
	m_showTable->show();
}

void Management::add()
{
	const char* title = "�������û���Ϣ<�˺��� �û���Ϣ ����>";
	settextstyle(36, 0, "����");
	outtextxy((Window::width() - textwidth(title))/2, 150, title);

	m_addBtn->show();
	m_addEdit->show();
	auto str = m_addEdit->text();
	if (m_addBtn->isClicked() && !str.empty())
	{
		vec_stu.push_back(USER::fromString(str));

		std::replace(str.begin(), str.end(), ' ', '\t');
		m_showTable->insertData(str);
		m_addEdit->clear();
	}
}

void Management::erase()
{
	const char* title = "������Ҫɾ�����û��˺���";
	settextstyle(36, 0, "����");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);
	
	m_delBtn->show();
	m_delEdit->show();

	if(m_delTable->rowCount() !=0)
		m_delTable->show();

	auto& str = m_delEdit->text();
	if (m_delEdit->textChanged())
	{
		auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [=](const USER& stu)
			{
				return std::to_string(stu.username) == str;
			});
		if (it == vec_stu.end())
		{
			outtextxy(m_delEdit->x(), m_delEdit->y() + 50, std::string("�Բ���û���ҵ��˺���Ϊ" + str + "���û���Ϣ").data());
		}
		else
		{
			m_delTable->insertData(it->formatInfo());
			//std::cout << "count:" << m_delTable->rowCount() << std::endl;

		}
	}

	if (m_delBtn->isClicked())
	{
		auto it = std::remove_if(vec_stu.begin(), vec_stu.end(), [=](const USER& stu)
			{
				return std::to_string(stu.username) == str;
			});
		if (it != vec_stu.end())
		{
			m_delEdit->clear();
			m_delTable->clear();
		}
		vec_stu.erase(it, vec_stu.end());
		
		updateShowTable();
		m_op = Menu;
	}
	
}

void Management::modify()
{
	const char* title = "������Ҫ�޸ĵ��û��˺���";
	settextstyle(36, 0, "����");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

	m_modifyEdit->show();
	
	if (isFind)
	{
		for (auto& e : m_stuEdits)
		{
			e->show();
		}
	}


	if (m_modifyEdit->textChanged())
	{
		auto& str = m_modifyEdit->text();
		std::stringstream ss(str);
		uint32_t username;
		ss >> username;

		auto it =  std::find_if(vec_stu.begin(), vec_stu.end(), [=](const USER& stu)
			{
				return stu.username == username;
			});
		if (it == vec_stu.end())
		{
			m_modifyIt = vec_stu.end();
			isFind = false;
		}
		else
		{
			m_stuEdits[0]->setText(std::to_string( it->username));
			m_stuEdits[1]->setText(it->name);
			m_stuEdits[2]->setText(std::to_string(it->password));

			isFind = true;
			m_modifyIt = it;
		}
	}

	if (isFind && m_modifyIt != vec_stu.end())
	{
		for (int i = 0;i<m_stuEdits.size();i++)
		{
			if (m_stuEdits[i]->textChanged())
			{
				switch (i)
				{
				case 0:
					m_modifyIt->username = atoi(m_stuEdits[i]->text().data());
					break;
				case 1:
					m_modifyIt->name = m_stuEdits[i]->text();
					break;
				case 2:
					m_modifyIt->password = atoi(m_stuEdits[i]->text().data());
					break;
				default:
					break;
				}
				updateShowTable();
			}
		}
	}


}

void Management::search()
{
	outtextxy(0, 0, "search");
	cout << "search" << endl;
}

void Management::drawBackground()
{
	::putimage(0, 0, &m_bk);
}

void Management::enevtLoop()
{
	m_showTable->event();

	m_addBtn->event();
	m_addEdit->event();

	m_delBtn->event();
	m_delEdit->event();
	m_delTable->event();

	m_modifyEdit->event();

	for (auto& e : m_stuEdits)
	{
		e->event();
	}

}

void Management::readFile(const std::string& fileName)
{
	fstream read(fileName, ios::in);
	if (!read.is_open())
	{
		return;
	}
	//��ȡ��ͷ
	char buf[1024] = { 0 };
	read.getline(buf, 1024);
	m_header = buf;

	//��ȡ����
	while (!read.eof())
	{
		char data[1024] = { 0 };
		read.getline(data, 1024);
		//��������
		if (strlen(data) == 0)
			break;
		//��ʽ����ȡ
		USER stu;
		stringstream  ss(data);
		ss >> stu.username >> stu.name >> stu.password;
		vec_stu.push_back(stu);

		//cout << stu.number << stu.name << stu.grade << stu.math << stu.chinese << stu.english << endl;;
	}
	read.close();
}

void Management::saveFile(const std::string& fileName)
{
	fstream write(fileName, ios::out | ios::trunc);
	if (!write.is_open())
	{
		cerr << fileName << "file open failed" << endl;
		return;
	}


	//д��ͷ
	m_header += "\n";
	write.write(m_header.c_str(), m_header.size());

	//д����
	for (auto& val : vec_stu)
	{
		std::string info = val.formatInfo();
		write.write(info.c_str(), info.size());
	}

	write.close();
}

void Management::updateShowTable()
{
	m_showTable->clear();
	for (auto& val : vec_stu)
	{
		m_showTable->insertData(val.formatInfo());
	}
}
