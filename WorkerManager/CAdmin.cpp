#include "CAdmin.h"
#include "CManager.h"

void CAdmin::Input()
{
	system("cls"); 
	int prior; 
	MYSQL_ROW row;
	string name, password, sSQL;

	cout << "请输入要添加的账户名：" << endl;
	cin >> name;

	row = CheckName(name.c_str()); 

	if (row)
	{
		cout << "用户名已存在，无法添加" << endl; 
		system("pause"); 
		return; 
	}

	cout << "请继续录入密码和权限(0、高级 1、普通)：";

	cin >> password >> prior;

	sSQL = "INSERT INTO `admin`(`name`, `password`, `prior`) VALUES ('" 
		+ name + "','" + password + "'," + to_string(prior) + ")";

	int n = mysql_query(m_conn, sSQL.c_str());

	if (n)
		CManager::PrintError(sSQL.c_str());

	cout << "添加用户成功" << endl;

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
		const char* p = (**row == '0') ? "高级" : "普通";
		cout << '\t' << p << endl;
	}
	//res ->row_count
	cout << "\t\t总共有 " << mysql_num_rows(res) << " 条记录" << endl;
	mysql_free_result(res);

	system("pause");
}

void CAdmin::Delete()
{
	MYSQL_ROW row;
	string sName,sSQL; 
	cout << "请输入要添加的账户名：" << endl;
	cin >> sName; 
	
	// 查询是否存在
	row = CheckName(sName.c_str()); 
	if (!row)
	{
		cout << "要删除的用户名不存在！" << endl;
		system("pause"); 
		return; 
	}

	sSQL = "DELETE FROM `admin` WHERE `name` = '" + sName + '\''; 

	int n = mysql_query(m_conn, sSQL.c_str()); 

	if (n)
		CManager::PrintError(sSQL.c_str()); 

	cout << "删除成功！" << endl; 

	system("pause"); 
}

void CAdmin::ChPass()
{
	system("cls"); 
	string newPass, nextPass,sSQL;
	cout << "请输入要修改的密码：" << endl; 
	cin >> newPass; 
	cout << "请再次输入要修改的密码：" << endl; 
	cin >> nextPass; 

	if (newPass != nextPass)
	{
		cout << "两次输入的密码不同，请重新修改" << endl;
		system("pause");
		return;
	}

	sSQL = "UPDATE `admin` SET `password` = '" + newPass + "' WHERE `name` = '" + m_sName +"'"; 

	int n = mysql_query(m_conn, sSQL.c_str());

	if (n)
		CManager::PrintError(sSQL.c_str());
	
	cout << "修改密码成功" << endl; 

	system("pause"); 
}

// 校验用户名是否存在
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
	puts("\t\t*\t1、浏览所有账号        *");
	puts("\t\t*\t2、添加账号            *");
	puts("\t\t*\t3、删除账号            *");
	puts("\t\t*\t4、修改密码            *");
	puts("\t\t*\t0、返回主菜单          *");
	puts("\t\t********************************");
	cout << "\t\t请选择：";
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

// 登陆函数
bool CAdmin::Login()
{
	MYSQL_ROW row; 
	MYSQL_RES* res; 
	string sName, sPass;
	cout << "请输入账号：";
	cin >> sName;
	cout << "请输入密码：";
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
		cout << "账号或密码错误！" << endl;
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

