#include <iomanip>
#include "Account.h"
#include "Hash/Hash.h"

using namespace std;

Account::Account(string login, string password, int access_level, bool is_approved)
{
    string salt;
    this->access_level = access_level;
    this->hashed_password = hashString(password, salt);
    this->login = login;
    this->is_approved = is_approved;
    this->salt = salt;
}

std::istream &operator>>(istream &is, Account &f) {
    string login, password;
    if(typeid(is) == typeid(ifstream))
    {
        string hashed_password, salt;
        bool is_approved;
        int access_level;
        is >> login;
        is >> hashed_password;
        is >> salt;
        is >> access_level;
        is >> is_approved;
        f.login = login;
        f.hashed_password = hashed_password;
        f.salt = salt;
        f.access_level = access_level;
        f.is_approved = is_approved;
    }
    else
    {

        cout<<"Enter login: ";
        is >> login;
        cout<<"Enter password: ";
        is >> password;
        string salt;
        f.login = login;
        f.hashed_password = hashString(password, salt);
        f.salt = salt;
    }
    return is;
}

std::ostream &operator<<(ostream &os, Account &f) {
    if(typeid(os) == typeid(ofstream))
    {
        os << endl;
        os << f.login <<' ';
        os << f.hashed_password <<' ';
        os << f.salt <<' ';
        os << f.access_level << ' ';
        os << f.is_approved;

    }
    return os;
}
