#include "CManager.h"

CManager& CManager::getInstance()
{
    // TODO: �ڴ˴����� return ���
    static CManager instance; // ��������˾ֲ���static�����ʣ��������ǲ����ͷŵ�
    return instance;
}

int CManager::Main()
{
	// ������ҳ��
	if (!ConnectDB())
	{
		cout << "�������ݿ�ʧ��" << endl;
		return -1; 
	}
	// ����һ����־
	bool flag = 0; 

	while (flag = !m_admin.Login());
	if (flag)
		return -1; 

	// ���˵�
	while (Menu()); 

	// �ر�����
	mysql_close(conn);
    return 0;
}

void CManager::PrintError(const char* sSQL)
{
	printf("SQL������%s\n %u: %s\n", sSQL, mysql_errno(getInstance().conn),
		mysql_error(getInstance().conn));
}

void CManager::PrintWorker(MYSQL_ROW row)
{
	cout << setw(10) << left << row[0] << setw(16) << row[1] <<
		setw(12) << row[2] << row[3] << endl;
}

CManager::CManager()
{
	// ��ʼ������������
	conn = mysql_init(NULL);
	m_worker = CWorker(conn); 
	m_admin = CAdmin(conn); 
}

int CManager::Menu()
{
	system("cls"); // ����
	int nPrior = m_admin.GetPriority();
	const char* p = m_admin.GetPriority() ? "��ͨ" : "�߼�";
	cout << "\n\n\t\t��ǰ�˺ţ�" << m_admin.GetUName() << "��" << p << "��" << endl;
	puts("\t\t********************************");
	puts("\t\t*\t1�����������Ϣ        *");
	puts("\t\t*\t2�������Ϣ            *");
	puts("\t\t*\t3��ɾ����Ϣ            *");
	puts("\t\t*\t4���޸���Ϣ            *");
	puts("\t\t*\t5��������Ϣ            *");
	if (nPrior)
		puts("\t\t*\t6�������޸�            *");
	else
		puts("\t\t*\t6���˺Ź���            *");
	puts("\t\t*\t0���˳�                *");
	puts("\t\t********************************");
	cout << "\t\t��ѡ��";
	int i = 0;
	cin >> i;

	switch (i)
	{
		case 1:
			//m_work.m_sort.Menu();
			m_worker.Browse();
			break;
		case 2:
			m_worker.Input();
			break;
		case 3:
			m_worker.Delete();
			break;
		case 4:
			m_worker.Modify();
			break;
		case 5:
			m_worker.Find();
			break;
		case 6:
			m_admin.Main(); 
			break;
			//m_admin.Main();
	}
	return i;
}

bool CManager::ConnectDB()
{
    if (conn == NULL)
    {
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        return false;
    }
    //host���������ã�"localhost",".","192.168.0.88","127.0.0.1","teacher"
    if (mysql_real_connect(conn, "localhost", "root", "damu", "db1", 0, NULL, 0) == NULL)
    {
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        return false;
    }
    mysql_query(conn, "set names gb2312");
    return true;
}
