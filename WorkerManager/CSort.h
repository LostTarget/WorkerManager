#pragma once
#include <mysql.h>
#include <iostream>
using namespace std;

class CWorker;  // ���ﲻ�����������ͷ�ļ����ᵼ���ظ����������������ʹ��ָ�������ö�Ӧ�ķ���
class CSort
{
private:
    MYSQL* m_conn; 
    CWorker* m_pWorker{};
public:
    CSort(MYSQL* conn, CWorker* pWorker); 
    CSort();

    int Menu(); // ����˵�
};

