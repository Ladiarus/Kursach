#include <string>
#include "DB_accounts.h"
#include "MySpace.h"

using namespace std;

DB_accounts::DB_accounts(string file) {
    this->file = file;
}
Account& createMainAdmin()
{
    Account *acc = new Account("admin", "admin", 0, true);
    return *acc;
}

void DB_accounts::update() {
    accounts.clear();
    fout.close();
    fin.open(file);
    if(!fin.is_open())
    {
        fout.open(file);
        fout.close();
    }
    if(isFileEmpty(fin))
    {
        fin.close();
        this->add(createMainAdmin());
        fin.open(file);
    }
    while(!fin.eof())
    {
        Account acc;
        fin>>acc;
        accounts.push_back(acc);
    }
    fin.close();
}

void DB_accounts::add(Account &acc) {
    accounts.push_back(acc);
    save();
}

void DB_accounts::save() {
    fin.close();
    fout.open(file);
    for(Account acc : accounts)
        fout<<acc;
    fout.close();
    //update();
}

int DB_accounts::findByLogin(string login) {
    for(int i = 0; i < accounts.size(); i++)
    {
        if(accounts[i].login == login)
        {
            return i;
        }
    }
    return -1;
}

void DB_accounts::deleteAccount(int idx)
{
    accounts.erase(accounts.begin() + idx);
    save();
}

int DB_accounts::getAmountOfNotApproved()
{
    int sum = 0;
    for(auto& acc : accounts)
    {
        if(!acc.is_approved)
            sum++;
    }
    return sum;
}

void DB_accounts::approveAccount(int idx)
{
    accounts.at(idx).is_approved = true;
    save();
}