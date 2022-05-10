#pragma once
#include <fstream>
#include <vector>
#include "Account.h"

using namespace std;
class DB_accounts {
public:
    DB_accounts(string file);
    string file;
    ifstream fin;
    ofstream fout;
    vector<Account> accounts;
    void update();
    void save();
    void add(Account& acc);
    int findByLogin(string login);
    void deleteAccount(int idx);
    void approveAccount(int idx);
    int getAmountOfNotApproved();
};