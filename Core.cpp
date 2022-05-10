#include <string>
#include <conio.h>
#include "Core.h"
#include "Menues.h"
#include "globals.h"
#include "Hash/Hash.h"

using namespace std;
void mainFunc()
{
    system("");
    globals::db_accounts.update();
    globals::db_students.update();
    while(true)
    {
        if (mainMenu())
            return;
        system("cls");
    }
}

string inputPassword()
{
    string password;
    while(true)
    {
        char c = getch();
        if(c == 13) // Enter
        {
            if(password.length()!=0)
                break;
        }
        else if(c == 8) // Backspace
        {
            if(password.length()!=0)
            {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else if(c != 32)
        {
            password+=c;
            cout<<'*';
        }
    }
    cout<<endl;
    return password;
}

void signIn(string login, string password)
{
    //globals::db_accounts.update();
    int idx = globals::db_accounts.findByLogin(login);
    Account & acc = globals::db_accounts.accounts[idx];
    if(idx == -1 || acc.hashed_password != hashString(password, acc.salt))
    {
        cout << "Incorrect login or password\n";
        system("pause");
        return;
    }
    else
    {
        if(!acc.is_approved)
        {
            cout << "Account doesn't approved by administrator\n";
            system("pause");
            return;
        }
        if(acc.access_level == 0)
        {
            userMenuAdmin();
        }
        else
        {
            userMenuUser();
        }
    }
}

Account *signUp()
{
    string password, login;
    cout<<"Enter login: ";
    if(cin.peek()=='\n')
        cin.get();
    getline(cin, login);
    if(login.find(' ') != -1)
    {
        cout << "Login can't contain spaces\n";
        system("pause");
        return nullptr;
    }
    if(globals::db_accounts.findByLogin(login)!=-1)
    {
        cout<<"Login already exist\n";
        system("pause");
        return nullptr;
    }

    while(true)
    {
        cout << "Enter password: \n";
        cout << "Confirm password: ";
        UP_LINE();
        TO_COLUMN(17);
        password = inputPassword();
        TO_COLUMN(19);
        if (password == inputPassword())
        {
            break;
        }
        cout << "Passwords are different\n";
        system("pause");
        UP_LINES(4);
        CLEAR_TO_END();
    }

    Account* acc = new Account(login, password, 1, false);
    return acc;

}

string inputNumber(string s)
{
    cout << s;
    while(true)
    {

        char c = getch();

        if (c == 13) // Enter
        {
            if (s.length() == 6)
                break;
        }
        else if (c == 8) // Backspace
        {
            if (s.length() != 0)
            {
                cout << "\b \b";
                s.pop_back();
            }
        }
        else if (isdigit(c) && s.length() <= 5)
        {
            s += c;
            cout << c;
        }
    }
    cout<<endl;
    return s;
}

string inputName(string s)
{
    cout << s;
    while(true)
    {
        char c = getch();
        if(c == 13) // Enter
        {
            if(s.length()>=6)
                break;
        }
        else if(c == 8) // Backspace
        {
            if(s.length()!=0)
            {
                cout << "\b \b";
                s.pop_back();
            }
        }
        else if(isalpha(c) || (s.length() != 0 && s[s.length()-1] != ' ' && c == ' '))
        {
            s+=c;
            cout << c;
        }
    }
    cout<<endl;
    return s;
}

bool inputBool()
{
    while(true)
    {
        char c = getch();
        if (c == 'y')
        {
            cout << 'y';
            return true;
        }
        else if (c == 'n') // Backspace
        {
            cout << 'n';
            return false;
        }
    }
}

void *inputCredits(bool *arr)
{
    cout << "INAD passed [y/n]: ";
    arr[0] = inputBool();
    cout << "\nIKG passed [y/n]: ";
    arr[1] = inputBool();
    cout << "\nLANG passed [y/n]: ";
    arr[2] = inputBool();
    cout << "\nHIST passed [y/n]: ";
    arr[3] = inputBool();
    cout << "\nPOLIT passed [y/n]: ";
    arr[4] = inputBool();
    cout << endl;
    return arr;
}

void *inputExams(int *arr)
{
    cout << "Input MATH mark:\n";
    input(arr[0], 0, 10);
    cin.ignore(1000,'\n');
    cout << "Input OOP mark:\n";
    input(arr[1], 0, 10);
    cin.ignore(1000,'\n');
    cout << "Input TRPO mark: \n";
    input(arr[2], 0, 10);
    cin.ignore(1000,'\n');
    cout << "Input PHYS mark:\n";
    input(arr[3], 0, 10);
    cin.ignore(1000,'\n');
    cout << "Input OAIP mark:\n";
    input(arr[4], 0, 10);
    cin.ignore(1000,'\n');
    cout << endl;
    return arr;
}