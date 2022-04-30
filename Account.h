#pragma once
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
class Account {
public:

    Account(string login, string password, int access_level, bool is_approved);
    Account(){};
    string login;
    string hashed_password;
    string salt;
    int access_level=1;
    bool is_approved= false;

    friend std::istream &operator>>(std::istream &is, Account &f);
    friend std::ostream& operator <<(std::ostream& output, Account& f);
};


