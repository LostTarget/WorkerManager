#include "CFind.h"
#include "CManager.h"

// 根据序号查询
void CFind::FindByNumb()
{
    MYSQL_ROW row;
    system("cls"); 
    cout << "请输入要查找的id：" << endl; 
    int nNumb; 
    cin >> nNumb; 

    row = FindNumb(nNumb); 

    if (!row)
    {
        CManager::PrintError("Not Found!");
        
    }
    else
    {
        CManager::PrintWorker(row);
    }
 
    system("pause"); 
}

// 根据名称关键字查询（模糊）
void CFind::FindByName()
{
    system("cls"); 
    string name, sSQL; 
    cout << "请输入查询关键字：" << endl;
    cin >> name; 

    sSQL = "SELECT * FROM `account` WHERE `name` LIKE '%" + name + "%'"; 

    DoSelect(sSQL.c_str()); 
}

// 查询工资
void CFind::FindBySalary()
{
    system("cls");
    string sSQL; 
    int min, max;
    cout << "请输入查询工资范围：" << endl;
    cin >> min >> max;

    sSQL = "SELECT * FROM `account` WHERE `balance` BETWEEN " + to_string(min) +" AND " + to_string(max);

    DoSelect(sSQL.c_str()); 
}

void CFind::FindByDate()
{
    system("cls");
    string minDate, maxDate, sSQL;
    cout << "请输入查询工资范围(1999-11-11)：" << endl;
    cin >> minDate >> maxDate;

    sSQL = "SELECT * FROM `account` WHERE `entry_date` BETWEEN '" + minDate + "' AND '" + maxDate + "'";

    DoSelect(sSQL.c_str());
}

// 查询封装语句
void CFind::DoSelect(const char* sSQL)
{
    MYSQL_ROW row; 
    MYSQL_RES* res; 

    int n = mysql_query(m_conn, sSQL); 

    if (n)
        CManager::PrintError(sSQL); 

    res = mysql_store_result(m_conn);  // 这里没有查询到，里面的row_count数据为0

    if (!res->row_count)
    {
        CManager::PrintError(sSQL);
    } 
    else
    {
        while (row = mysql_fetch_row(res))
        {
            CManager::PrintWorker(row);
        }
        // 释放结果集
        mysql_free_result(res);
    }

    system("pause"); 
}

CFind::CFind(MYSQL* conn)
{
    m_conn = conn; 
}

CFind::CFind()
{
}

MYSQL_ROW CFind::FindNumb(int nNumb)
{
    MYSQL_ROW row;
    MYSQL_RES* res;
    char szBuf[256]{ 0 };
    sprintf_s(szBuf, _countof(szBuf), "SELECT * FROM account WHERE id = %d;", nNumb);
    const char* sSql = szBuf;
    // 查找对应编号的员工
    if (mysql_query(m_conn, sSql))
    {
        CManager::PrintError(sSql);
        return nullptr;
    }

    res = mysql_store_result(m_conn);

    if (!res)
        CManager::PrintError(sSql);

    row = mysql_fetch_row(res);
    return row;
}

int CFind::Menu()
{
    system("cls");
    puts("\n\n\t\t********************************");
    puts("\t\t*\t1、按id查找        *");
    puts("\t\t*\t2、按姓名查找        *");
    puts("\t\t*\t3、按工资段查找      *");
    puts("\t\t*\t4、按入职日期时间段查找      *");
    puts("\t\t*\t0、返回主菜单        *");
    puts("\t\t********************************");
    cout << "\t\t请选择：";
    int i = 0;
    cin >> i;
    switch (i)
    {
    case 1:
        FindByNumb();
        break;
    case 2:
        FindByName();
        break;
    case 3:
        FindBySalary();
        break;
    case 4:
        FindByDate();
        break; 
    }
    return i;
}
