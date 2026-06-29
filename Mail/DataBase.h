#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "Mail.h"

class DataBase
{
public:

    bool Init( std::string fileName);

    int Login();
private:
    std::vector<Mail> Mails;

    bool InitMail(std::string usetName);
    void CreateDefaultMailData();
};