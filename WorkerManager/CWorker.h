#pragma once
#include <mysql.h>
#include <string>
#include "CSort.h"
#include "CFind.h"
#include <iomanip>
using namespace std; 

class CManager; 
class CWorker
{
private:
    friend CManager; 
    MYSQL* m_conn; 
    CSort m_sort;
    CFind m_find;
public:
    CWorker(MYSQL* conn); // 初始化成员变量
    void Browse(); 
    void Input(); 
    void Delete(); 
    void Modify(); 
    void Find(); 
    void Print(const char* bs); // 测试输出函数
};

