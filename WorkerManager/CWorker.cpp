#include "CWorker.h"
#include "CManager.h"

CWorker::CWorker(MYSQL* conn)
{
    m_conn = conn; 
    m_sort = CSort(conn, this); 
    m_find = CFind(conn); 
}

void CWorker::Browse()
{
    while (m_sort.Menu());
    //Print(); 
}

void CWorker::Input()
{
    system("cls"); 
    MYSQL_ROW row;
    char szBuf[256]{ 0 }; 
    char szName[56]{ 0 }; 
    int salary = 0; 

    int nNumb = 0;
    cout << "请输入新员工的id：";
    cin >> nNumb;
    row = m_find.FindNumb(nNumb);

    if (row)
    {
        cout << "你录入的id已存在:";
        CManager::PrintWorker(row);
        system("pause");
        return;
    }
    
    cout << "请输入新员工的姓名、工资" << endl; 
    cin >> szName >> salary; 

    sprintf_s(szBuf, _countof(szBuf), "INSERT INTO account (id, name, balance) values (%d, '%s', %d)", nNumb, szName, salary); 

    const char* sSql = szBuf; 

    int n = mysql_query(m_conn, sSql); 

    if (n)
    {
        CManager::PrintError(sSql);
        return; 
    }  

    // 打印所有的员工
    //Print(); 
}

// 删除员工
void CWorker::Delete()
{
    system("cls");
    MYSQL_ROW row;
    //while (m_find.Menu()); 
    int accountId = 0;
    cout << "请输入您要删除的id：" << endl;
    cin >> accountId;
    row = m_find.FindNumb(accountId);
    if (!row)
        CManager::PrintError("未找到对应的列");

    cout << "你确定要删除这条记录吗?[y/n]";
    char c;
    cin >> c;
    if (c != 'Y' && c != 'y')
        return;

    string sSql = "Delete from account where id = " + to_string(accountId); 

    int n = mysql_query(m_conn, sSql.c_str()); 

    if (n)
        CManager::PrintError(sSql.c_str()); 


    //Print(); 
}

void CWorker::Modify()
{
    int nNumb = 0;
    cout << "请输入要修改的id号：";
    cin >> nNumb;
    auto row = m_find.FindNumb(nNumb);
    if (!row)
    {
        puts("你输入的id不存在！");
        system("pause");
        return;
    }
    CManager::PrintWorker(row);
    cout << "你确定要修改这条记录吗?[y/n]";
    char c;
    cin >> c;
    if (c != 'Y' && c != 'y')
        return;

    cout << "请录入新的姓名、工资：";

    int salary; 
    string name, sSql; 

    cin >> name >> salary; 

    sSql = "UPDATE account SET name = '" + name + "',balance = " + to_string(salary) + " WHERE id = " + to_string(nNumb);

    int n = mysql_query(m_conn, sSql.c_str()); 

    if (n)
    {
        CManager::PrintError(sSql.c_str());
        return; 
    }
        
    //Print(); 
}

void CWorker::Find()
{
   // system("cls"); 
   // MYSQL_ROW row;
    while (m_find.Menu()); 
   // int accountId = 0;
   // cout << "请输入您要查询的id：" << endl;
   // cin >> accountId;
   // row = m_find.FindNumb(accountId); 
   // if (!row)
   //     CManager::PrintError("未找到对应的列"); 

   // CManager::PrintWorker(row); 

   // system("pause"); 
}


// 重构输出，按照排序输出
void CWorker::Print(const char* bs)
{
    system("cls");

    MYSQL_ROW row;
    MYSQL_RES* res;
    int t; 

    cout << setw(10) << left << "id" << setw(16) << "姓名" <<
        setw(12) << "balance" << "entry_date" << endl;

    string sSQL = "SELECT * FROM account ";
    if (bs)
    {
        sSQL += "ORDER BY "; 
        sSQL += bs; 
    }  

    //printf("%p\r\n", m_conn); 

    if (mysql_query(m_conn, sSQL.c_str()))
    {
        CManager::PrintError(sSQL.c_str());
        return; 
    }

    res = mysql_store_result(m_conn); 

    if (!res)
    {
        CManager::PrintError(sSQL.c_str());
        return; 
    }

    while (row = mysql_fetch_row(res))
    {
        CManager::PrintWorker(row);
    }
    system("pause"); 
}
