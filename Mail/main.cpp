#include <iostream>

#include "DataBase.h"

int  main()
{
    DataBase Base;
    std::cout << Base.Init("DB/MailsList.txt");
    
    return 0;
}