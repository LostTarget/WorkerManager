#pragma once
#include <mysql.h>
#include <iostream>
using namespace std;

class CWorker;  // 这里不能在引入类的头文件，会导致重复包含，所以这里就使用指针来调用对应的方法
class CSort
{
private:
    MYSQL* m_conn; 
    CWorker* m_pWorker{};
public:
    CSort(MYSQL* conn, CWorker* pWorker); 
    CSort();

    int Menu(); // 排序菜单
};

