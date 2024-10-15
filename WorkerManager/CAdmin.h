#pragma once
#include <string>
#include <mysql.h>
#include <iostream>
using namespace std; 

class CAdmin
{
private:
    int m_nPrior;// ���ȼ�s
    std::string m_sName; // �û���
    std::string m_sPass; // ����
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

