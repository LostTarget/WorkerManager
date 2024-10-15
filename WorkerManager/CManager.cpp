#include "CManager.h"

CManager& CManager::getInstance()
{
    // TODO: 在此处插入 return 语句
    static CManager instance; // 这快利用了局部的static的性质，它这里是不会释放的
    return instance;
}

int CManager::Main()
{
	// 加载主页面
	if (!ConnectDB())
	{
		cout << "连接数据库失败" << endl;
		return -1; 
	}
	// 定义一个标志
	bool flag = 0; 

	while (flag = !m_admin.Login());
	if (flag)
		return -1; 

	// 主菜单
	while (Menu()); 

	// 关闭连接
	mysql_close(conn);
    return 0;
}

void CManager::PrintError(const char* sSQL)
{
	printf("SQL语句错误：%s\n %u: %s\n", sSQL, mysql_errno(getInstance().conn),
		mysql_error(getInstance().conn));
}

void CManager::PrintWorker(MYSQL_ROW row)
{
	cout << setw(10) << left << row[0] << setw(16) << row[1] <<
		setw(12) << row[2] << row[3] << endl;
}

CManager::CManager()
{
	// 初始化这三个对象
	conn = mysql_init(NULL);
	m_worker = CWorker(conn); 
	m_admin = CAdmin(conn); 
}

int CManager::Menu()
{
	system("cls"); // 清屏
	int nPrior = m_admin.GetPriority();
	const char* p = m_admin.GetPriority() ? "普通" : "高级";
	cout << "\n\n\t\t当前账号：" << m_admin.GetUName() << "【" << p << "】" << endl;
	puts("\t\t********************************");
	puts("\t\t*\t1、浏览所有信息        *");
	puts("\t\t*\t2、添加信息            *");
	puts("\t\t*\t3、删除信息            *");
	puts("\t\t*\t4、修改信息            *");
	puts("\t\t*\t5、查找信息            *");
	if (nPrior)
		puts("\t\t*\t6、密码修改            *");
	else
		puts("\t\t*\t6、账号管理            *");
	puts("\t\t*\t0、退出                *");
	puts("\t\t********************************");
	cout << "\t\t请选择：";
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
    //host参数可以用："localhost",".","192.168.0.88","127.0.0.1","teacher"
    if (mysql_real_connect(conn, "localhost", "root", "damu", "db1", 0, NULL, 0) == NULL)
    {
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        return false;
    }
    mysql_query(conn, "set names gb2312");
    return true;
}
