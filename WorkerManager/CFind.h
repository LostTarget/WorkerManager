#pragma once
#include <iostream>
#include <mysql.h>
class CFind
{
private:
    MYSQL* m_conn; // ���ͨ�ñ�������ͨ������������ʱ��ͨ�����촫��
private:
    void FindByNumb();
    void FindByName();
    void FindBySalary();
    void FindByDate();
    void DoSelect(const char* sSQL);
public:
    CFind(MYSQL* conn); 
    CFind();
    MYSQL_ROW FindNumb(int nNumb);
    int Menu(); // ��ѯ���ݲ˵�
};

