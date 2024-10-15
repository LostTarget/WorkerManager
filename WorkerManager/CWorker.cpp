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
    cout << "��������Ա����id��";
    cin >> nNumb;
    row = m_find.FindNumb(nNumb);

    if (row)
    {
        cout << "��¼���id�Ѵ���:";
        CManager::PrintWorker(row);
        system("pause");
        return;
    }
    
    cout << "��������Ա��������������" << endl; 
    cin >> szName >> salary; 

    sprintf_s(szBuf, _countof(szBuf), "INSERT INTO account (id, name, balance) values (%d, '%s', %d)", nNumb, szName, salary); 

    const char* sSql = szBuf; 

    int n = mysql_query(m_conn, sSql); 

    if (n)
    {
        CManager::PrintError(sSql);
        return; 
    }  

    // ��ӡ���е�Ա��
    //Print(); 
}

// ɾ��Ա��
void CWorker::Delete()
{
    system("cls");
    MYSQL_ROW row;
    //while (m_find.Menu()); 
    int accountId = 0;
    cout << "��������Ҫɾ����id��" << endl;
    cin >> accountId;
    row = m_find.FindNumb(accountId);
    if (!row)
        CManager::PrintError("δ�ҵ���Ӧ����");

    cout << "��ȷ��Ҫɾ��������¼��?[y/n]";
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
    cout << "������Ҫ�޸ĵ�id�ţ�";
    cin >> nNumb;
    auto row = m_find.FindNumb(nNumb);
    if (!row)
    {
        puts("�������id�����ڣ�");
        system("pause");
        return;
    }
    CManager::PrintWorker(row);
    cout << "��ȷ��Ҫ�޸�������¼��?[y/n]";
    char c;
    cin >> c;
    if (c != 'Y' && c != 'y')
        return;

    cout << "��¼���µ����������ʣ�";

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
   // cout << "��������Ҫ��ѯ��id��" << endl;
   // cin >> accountId;
   // row = m_find.FindNumb(accountId); 
   // if (!row)
   //     CManager::PrintError("δ�ҵ���Ӧ����"); 

   // CManager::PrintWorker(row); 

   // system("pause"); 
}


// �ع�����������������
void CWorker::Print(const char* bs)
{
    system("cls");

    MYSQL_ROW row;
    MYSQL_RES* res;
    int t; 

    cout << setw(10) << left << "id" << setw(16) << "����" <<
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
