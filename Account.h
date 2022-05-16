#pragma once
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
class Account
{
public:

    Account(string login, string password, int access_level, bool is_approved);
    Account(){};
    string login;//логин
    string hashed_password;//хешированный пароль
    string salt;//соль для пароля
    int access_level=1;//уровень доступа
    bool is_approved= false;//подтвержденность

    friend std::istream &operator >> (std::istream &is, Account &f);
    friend std::ostream& operator <<(std::ostream &os, Account& f);
};