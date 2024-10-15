#include "CAdmin.h"
#include "CManager.h"

void CAdmin::Input()
{
	system("cls"); 
	int prior; 
	MYSQL_ROW row;
	string name, password, sSQL;

	cout << "������Ҫ��ӵ��˻�����" << endl;
	cin >> name;

	row = CheckName(name.c_str()); 

	if (row)
	{
		cout << "�û����Ѵ��ڣ��޷����" << endl; 
		system("pause"); 
		return; 
	}

	cout << "�����¼�������Ȩ��(0���߼� 1����ͨ)��";

	cin >> password >> prior;

	sSQL = "INSERT INTO `admin`(`name`, `password`, `prior`) VALUES ('" 
		+ name + "','" + password + "'," + to_string(prior) + ")";

	int n = mysql_query(m_conn, sSQL.c_str());

	if (n)
		CManager::PrintError(sSQL.c_str());

	cout << "����û��ɹ�" << endl;

	system("pause"); 
}

void CAdmin::Print()
{
	system("cls"); 

	MYSQL_RES* res; 
	MYSQL_ROW row; 

	string sSQL = "SELECT * FROM admin";

	int n = mysql_query(m_conn, sSQL.c_str());

	if (n)
	{
		CManager::PrintError(sSQL.c_str());
		return;
	}

	res = mysql_store_result(m_conn);

	if (!res->row_count)
	{
		CManager::PrintError(sSQL.c_str()); 
		return;
	}

	int nCols = mysql_num_fields(res);
	while (row = mysql_fetch_row(res))
	{
		int i = 0;
		cout << '\t';
		while (++i < nCols)
			cout << '\t' << *row++;
		const char* p = (**row == '0') ? "�߼�" : "��ͨ";
		cout << '\t' << p << endl;
	}
	//res ->row_count
	cout << "\t\t�ܹ��� " << mysql_num_rows(res) << " ����¼" << endl;
	mysql_free_result(res);

	system("pause");
}

void CAdmin::Delete()
{
	MYSQL_ROW row;
	string sName,sSQL; 
	cout << "������Ҫ��ӵ��˻�����" << endl;
	cin >> sName; 
	
	// ��ѯ�Ƿ����
	row = CheckName(sName.c_str()); 
	if (!row)
	{
		cout << "Ҫɾ�����û��������ڣ�" << endl;
		system("pause"); 
		return; 
	}

	sSQL = "DELETE FROM `admin` WHERE `name` = '" + sName + '\''; 

	int n = mysql_query(m_conn, sSQL.c_str()); 

	if (n)
		CManager::PrintError(sSQL.c_str()); 

	cout << "ɾ���ɹ���" << endl; 

	system("pause"); 
}

void CAdmin::ChPass()
{
	system("cls"); 
	string newPass, nextPass,sSQL;
	cout << "������Ҫ�޸ĵ����룺" << endl; 
	cin >> newPass; 
	cout << "���ٴ�����Ҫ�޸ĵ����룺" << endl; 
	cin >> nextPass; 

	if (newPass != nextPass)
	{
		cout << "������������벻ͬ���������޸�" << endl;
		system("pause");
		return;
	}

	sSQL = "UPDATE `admin` SET `password` = '" + newPass + "' WHERE `name` = '" + m_sName +"'"; 

	int n = mysql_query(m_conn, sSQL.c_str());

	if (n)
		CManager::PrintError(sSQL.c_str());
	
	cout << "�޸�����ɹ�" << endl; 

	system("pause"); 
}

// У���û����Ƿ����
MYSQL_ROW CAdmin::CheckName(const char* name)
{
	MYSQL_RES* res; 
	MYSQL_ROW row;
	string sSQL = "SELECT * FROM `admin` WHERE `name` = '" + string(name) + '\''; 

	int n = mysql_query(m_conn, sSQL.c_str()); 

	if (n)
	{
		CManager::PrintError(sSQL.c_str());
		return nullptr; 
	}
	
	res = mysql_store_result(m_conn); 

	if (!res->row_count)
	{
		return nullptr; 
	}

	row = mysql_fetch_row(res); 

	mysql_free_result(res); 

	system("pause"); 
	return row;
}

CAdmin::CAdmin(MYSQL* conn): m_conn(conn)
{
}

int CAdmin::Menu()
{
	system("cls");
	puts("\n\n\t\t********************************");
	puts("\t\t*\t1����������˺�        *");
	puts("\t\t*\t2������˺�            *");
	puts("\t\t*\t3��ɾ���˺�            *");
	puts("\t\t*\t4���޸�����            *");
	puts("\t\t*\t0���������˵�          *");
	puts("\t\t********************************");
	cout << "\t\t��ѡ��";
	int i = 0;
	cin >> i;
	switch (i)
	{
	case 1:
		Print();
		break;
	case 2:
		Input();
		break;
	case 3:
		Delete();
		break;
	case 4:
		ChPass();

	}
	return i;
}

void CAdmin::Main()
{
	while (Menu()); 
}

// ��½����
bool CAdmin::Login()
{
	MYSQL_ROW row; 
	MYSQL_RES* res; 
	string sName, sPass;
	cout << "�������˺ţ�";
	cin >> sName;
	cout << "���������룺";
	cin >> sPass;

	string sSQL = "SELECT * FROM admin WHERE name=\'" + sName
		+ "\' AND BINARY password=\'" + sPass + '\'';

	int n = mysql_query(m_conn, sSQL.c_str()); 

	if (n)
	{
		CManager::PrintError(sSQL.c_str());
		return false; 
	}

	res = mysql_store_result(m_conn); 

	if (!res->row_count)
	{
		cout << "�˺Ż��������" << endl;
		return false;
	}

	row = mysql_fetch_row(res); 

	m_nPrior = atoi(row[2]);
	m_sName = row[0]; 
	m_sPass = row[1]; 

	mysql_free_result(res); 
    return true;
}

int CAdmin::GetPriority() const
{
    return m_nPrior;
}

const char* CAdmin::GetUName() const
{
    return m_sName.c_str();
}

