#pragma once
#include <string>
#include <mysql.h>
#include <iostream>
using namespace std; 

class CAdmin
{
private:
    int m_nPrior;// 优先级s
    std::string m_sName; // 用户名
    std::string m_sPass; // 密码
    MYSQL* m_conn;

private:
    void Input();
    void Print();
    void Delete();
    void ChPass();
    MYSQL_ROW CheckName(const char* name);
public:
    CAdmin(MYSQL* conn);
    bool Login(); 
    int Menu();
    void Main(); 
    int GetPriority() const; 
    const char* GetUName() const; 
};

