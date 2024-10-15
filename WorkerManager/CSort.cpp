#include "CSort.h"
#include "CWorker.h"

CSort::CSort(MYSQL* conn, CWorker* pWorker)
{
    m_conn = conn; 
    m_pWorker = pWorker; 
}

CSort::CSort()
{
}

int CSort::Menu()
{
    system("cls");
    puts("\n\n\t\t********************************");
    puts("\t\t*\t1����id����        *");
    puts("\t\t*\t2������������        *");
    puts("\t\t*\t3������������        *");
    //puts("\t\t*\t4������ְ��������    *");
    puts("\t\t*\t0���������˵�         *");
    puts("\t\t********************************");
    cout << "\t\t��ѡ��";
    int i = 0;
    cin >> i;
    if (i > 0 && i < 5)
    {
        static const char* bs[]{ "id","name","balance"};

        m_pWorker->Print(bs[i - 1]);
    }

    return i;
}
