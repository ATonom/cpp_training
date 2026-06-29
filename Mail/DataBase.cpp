#include "DataBase.h"

bool DataBase::Init(std::string fileName)
{
    std::ifstream mailsList(fileName);
    if (!mailsList.is_open()) return false;
    
    std::string mailName;
    while (std::getline(mailsList, mailName))
    {
        //std::ifstream 
        std::cout << mailName << "\n";
    }
    
    return true;
}
