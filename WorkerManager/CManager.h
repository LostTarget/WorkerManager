#pragma once
#include "CWorker.h"
#include "CAdmin.h"
#include <iostream>
#include <mysql.h>
#pragma comment(lib, "libmysql.lib")
using namespace std;

class CManager
{

private:
    // ����һ�����ӵı���
    MYSQL* conn;
    // ����������Ա
    CWorker m_worker{ conn }; // �����ǽ�conn��Ϊ��Ӧ��CWorker���캯���Ĵ���
    CAdmin m_admin{ conn };
private:
    // ˽�й���
    CManager();
    int Menu(); 

public:
    // ʹ�ö�������ģʽ
    static CManager& getInstance(); 
    bool ConnectDB();
    int Main();
    static void PrintError(const char* sSQL);
    static void PrintWorker(MYSQL_ROW row);
};

