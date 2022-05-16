#pragma once
#include <fstream>
#include <vector>
#include "Account.h"

using namespace std;
class DB_accounts //класс для работы с аккаунтами
{
public:
    DB_accounts(string file);
    string file;
    ifstream fin;
    ofstream fout;
    vector<Account> accounts;
    void update();//обновить массив
    void save();//сохранить в файл
    void add(Account& acc);//добавить в массив
    int findByLogin(string login);//поиск в массиве по логину
    void deleteAccount(int idx);//удалить аккаунт
    void approveAccount(int idx);//подтвердить аккаунт
    int getAmountOfNotApproved();//получить количество не подтвержденных аккаунтов
};