#pragma once
#include <iostream>
#include <mysql.h>
class CFind
{
private:
    MYSQL* m_conn; // 这个通用变量都是通过创建变量的时候通过构造传入
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
    int Menu(); // 查询数据菜单
};

