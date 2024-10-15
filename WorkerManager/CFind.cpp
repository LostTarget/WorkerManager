#include "CFind.h"
#include "CManager.h"

// ������Ų�ѯ
void CFind::FindByNumb()
{
    MYSQL_ROW row;
    system("cls"); 
    cout << "������Ҫ���ҵ�id��" << endl; 
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

// �������ƹؼ��ֲ�ѯ��ģ����
void CFind::FindByName()
{
    system("cls"); 
    string name, sSQL; 
    cout << "�������ѯ�ؼ��֣�" << endl;
    cin >> name; 

    sSQL = "SELECT * FROM `account` WHERE `name` LIKE '%" + name + "%'"; 

    DoSelect(sSQL.c_str()); 
}

// ��ѯ����
void CFind::FindBySalary()
{
    system("cls");
    string sSQL; 
    int min, max;
    cout << "�������ѯ���ʷ�Χ��" << endl;
    cin >> min >> max;

    sSQL = "SELECT * FROM `account` WHERE `balance` BETWEEN " + to_string(min) +" AND " + to_string(max);

    DoSelect(sSQL.c_str()); 
}

void CFind::FindByDate()
{
    system("cls");
    string minDate, maxDate, sSQL;
    cout << "�������ѯ���ʷ�Χ(1999-11-11)��" << endl;
    cin >> minDate >> maxDate;

    sSQL = "SELECT * FROM `account` WHERE `entry_date` BETWEEN '" + minDate + "' AND '" + maxDate + "'";

    DoSelect(sSQL.c_str());
}

// ��ѯ��װ���
void CFind::DoSelect(const char* sSQL)
{
    MYSQL_ROW row; 
    MYSQL_RES* res; 

    int n = mysql_query(m_conn, sSQL); 

    if (n)
        CManager::PrintError(sSQL); 

    res = mysql_store_result(m_conn);  // ����û�в�ѯ���������row_count����Ϊ0

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
        // �ͷŽ����
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
    // ���Ҷ�Ӧ��ŵ�Ա��
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
    puts("\t\t*\t1����id����        *");
    puts("\t\t*\t2������������        *");
    puts("\t\t*\t3�������ʶβ���      *");
    puts("\t\t*\t4������ְ����ʱ��β���      *");
    puts("\t\t*\t0���������˵�        *");
    puts("\t\t********************************");
    cout << "\t\t��ѡ��";
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
