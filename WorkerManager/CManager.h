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
    // 定义一个连接的变量
    MYSQL* conn;
    // 定义两个成员
    CWorker m_worker{ conn }; // 这里是将conn作为对应的CWorker构造函数的传参
    CAdmin m_admin{ conn };
private:
    // 私有构造
    CManager();
    int Menu(); 

public:
    // 使用饿汉单例模式
    static CManager& getInstance(); 
    bool ConnectDB();
    int Main();
    static void PrintError(const char* sSQL);
    static void PrintWorker(MYSQL_ROW row);
};

