#include "CManager.h"
#include <stdio.h>


int main()
{
    //SetConsoleOutputCP(CP_UTF8); 
    CManager& m = CManager::getInstance(); 
    m.Main(); 
    return 0; 
}