#pragma once
#include "BasicWidget.h"//�̳���
#include "Configure.h"
#include <vector>
#include "PushButton.h"
class Table :
    public BasicWidget
{
public:
    Table(int row = 0, int col = 0);
    ~Table();
    void setRowCount(int row);
    int rowCount()const { return m_datas.size(); }//��ȡ����
    int colCount()const { return m_cols; }
    void setColCount(int col);
    void setHeader(const std::string& header);
    void insertData(const std::string& data);


    void show();
    void drawTableGrid();//���Ʊ��
    void drawButton();
    void drawTableData();//���Ʊ������
    void drawHeader();
    static std::vector<std::string> split(std::string str, char separator='\t');

    void updatePage();
    
    void event()override;

    void clear() { m_datas.clear(); }

private:
    int m_rows;
    int m_cols;

    //���ӵĿ�Ⱥ͸߶�
    int m_gridW;
    int m_gridH;

    //���ֵĿ�Ⱥ͸߶�
    int m_tw;
    int m_th;

    std::string m_header;
    std::vector<std::string> m_datas;

private:                       //��ҳ����
    int m_curPage;   //��ǰҳ
    int m_maxPage;   //���ҳ��
    int m_extraData; //����������һҳ�����һҳʣ���������

    PushButton* m_prevBtn;
    PushButton* m_nextBtn;
    PushButton* m_firstBtn;
    PushButton* m_lastBtn;
                   
};

