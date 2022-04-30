#include <iostream>
#include <conio.h>
#include <string>
#include <iomanip>
#include "Menues.h"
#include "MySpace.h"
#include "Account.h"
#include "globals.h"
#include "Hash/Hash.h"

using namespace std;
namespace width
{
    int id = 6, login = 15, hashed_password = 64, access = 7;
}


bool chooseOption(vector<void (*)()> args) {
    int choice;
    while (true)
    {
        choice = getch();
        choice-='0';
        if (choice == 0)
            return true;
        if (choice <= args.size() && choice > 0)
        {
            break;
        }

    }
    args[choice-1]();
    return false;

}
bool mainMenu() {

    std::cout<<"Main menu:\n"
               "1 - Sign in\n"
               "2 - Sign up\n"
               "0 - EXIT\n";
    bool b = chooseOption({signIn_select, signUp_select});
    return b;
}


void signIn_select() {
    string login;
    string password;
    system("cls");
    std::cout<<"signIn\n";
    cout<< "login: ";
    if(cin.peek() == '\n')
        cin.get();
    getline(cin, login);
    cout << "password: ";
    password = inputPassword();
    signIn(login, password);
}

void signUp_select() {
    std::cout<<"signUp\n";

    Account *acc = signUp();
    if(acc == nullptr)
        return;
    globals::db_accounts.add(*acc);
    cout<<"Done!\n";
    system("pause");
}

void userMenuAdmin()
{
    while(true)
    {
        system("cls");
        cout<<"Admin Menu:\n";
        cout<<"-----DB <Accounts>-----\n";
        cout<<"1 - Show\n2 - Add\n3 - Edit\n4 - Delete\n5 - Approve requests\n0 - Back\n";
        if(chooseOption({accounts::show_select, accounts::add_select, accounts::edit_select, accounts::delete_select, accounts::approveRequests_select}))
            return;
    }

}

void userMenuUser()
{
    system("cls");
    cout<<"User Menu:\n";
    system("pause");
}

#pragma region accounts
void accounts::show_select()
{
    system("cls");

    accounts::show();

    system("pause");

}

void accounts::approveRequests_select()
{
    while(true)
    {
        system("cls");
        if(globals::db_accounts.getAmountOfNotApproved() == 0)
        {
            cout << "There are no " << YELLOW << "unapproved" << DEFAULT_COLOR << " accounts" <<endl;
            system("pause");
            return;
        }

        cout.fill('=');
        cout << setw(width::id + width::login + width::hashed_password + width::access + 5) << '=' << endl;
        cout.fill(' ');

        cout << '|' << setw(width::id) << centerString("ID", width::id, ' ') << setw(1) << "|";
        cout << setw(width::login) << centerString("Login", width::login, ' ') << setw(1) << '|';
        cout << setw(width::hashed_password) << centerString("Hashed password", width::hashed_password, ' ') << setw(1) << '|';
        cout << setw(width::access) << centerString("Access", width::access, ' ') << setw(1) << '|' << endl;

        cout.fill('=');
        cout << setw(width::id + width::login + width::hashed_password + width::access + 5) << '=' << endl;
        cout.fill(' ');

        for(int id = 1; id <= globals::db_accounts.accounts.size();id++)
        {
            Account& acc = globals::db_accounts.accounts[id-1];
            if(!acc.is_approved)
            {
                cout << '|';
                cout << setw(width::id) << centerString(id < 10 ? ("0" + to_string(id)) : to_string(id), width::id, ' ')
                     << setw(1) << '|';
                cout << setw(width::login) << left << acc.login << setw(1) << '|';
                cout << setw(width::hashed_password) << left << acc.hashed_password << setw(1) << '|';
                cout << setw(width::access) << centerString(acc.access_level == 0 ? "Admin" : "User", width::access, ' ')
                     << setw(1) << '|' << endl;

                cout.fill('-');
                cout << setw(width::id + width::login + width::hashed_password + width::access + 5) << '-' << endl;
                cout.fill(' ');
            }

        }

        cout<<"1 - Reject\n2 - Approve\n0 - Back\n";
        if(chooseOption({accounts::rejectRequest, accounts::approveRequest}))
            return;
    }

}

void accounts::add_select()
{
    system("cls");
    Account *acc = signUp();
    if(acc == nullptr)
        return;
    int access_level;
    cout<<"Input access level of new account:\n0 - Admin\n1 - User\n";

    input(access_level, 0, 1);
    acc->access_level = access_level;
    acc->is_approved = true;
    globals::db_accounts.add(*acc);
    cout<<"Done!\n";
    system("pause");
}

void accounts::edit_select()
{
    while(true)
    {
        system("cls");
        if (globals::db_accounts.accounts.size() == 1)
        {
            cout << "There is only one " << GREEN << "Main Admin" << DEFAULT_COLOR << endl;
            return;
        }

        accounts::show();

        int idx;
        cout << "Choose account to " << CYAN << "edit" << DEFAULT_COLOR << endl;
        cout << "0 - BACK\n";
        input(idx, 2, globals::db_accounts.accounts.size(), {0});
        if (idx == 0)
            return;

        TO_POSITION(6, 0);
        CLEAR_TO_END();
        TO_POSITION(4, 0);
        CLEAR_LINE();

        Account &acc = globals::db_accounts.accounts[idx - 1];
        cout << '|';
        cout << setw(width::id) << centerString(idx < 10 ? ("0" + to_string(idx)) : to_string(idx), width::id, ' ')
             << setw(1) << '|';
        cout << setw(width::login) << left << acc.login << setw(1) << '|';
        cout << setw(width::hashed_password) << left << acc.hashed_password << setw(1) << '|';
        cout << setw(width::access) << centerString(acc.access_level == 0 ? "Admin" : "User", width::access, ' ')
             << setw(1) << '|';
        DOWN_LINES(2);

        int choice;
        cout << "Choose field to " << CYAN << "edit" << DEFAULT_COLOR << endl;
        cout << "1 - Login\n2 - Password\n3 - Access level\n0 - Back\n";
        bool is_back = false;
        while (true)
        {
            choice = getch();
            choice -= '0';
            if (choice == 0)
            {
                is_back = true;
                break;

            }
            if (choice <= 3 && choice > 0)
            {
                break;
            }

        }

        if(is_back)
            continue;

        TO_POSITION(6, 0);
        CLEAR_TO_END();

        switch (choice)
        {
            case 1:
            {
                string login;
                cout << "New login: ";
                if (cin.peek() == '\n')
                    cin.get();
                getline(cin, login);
                if (login.find(' ') != -1)
                {
                    cout << "Login can't contain spaces\n";
                    system("pause");
                    break;
                }
                if (globals::db_accounts.findByLogin(login) != -1)
                {
                    cout << "Login already exist\n";
                    system("pause");
                    break;
                }
                acc.login = login;
                cout << "Done!\n";
                break;
            }
            case 2:
            {
                string password;
                while (true)
                {
                    cout << "New password: \n";
                    cout << "Confirm password: ";
                    UP_LINE();
                    TO_COLUMN(15);
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
                string salt;
                acc.hashed_password = hashString(password, salt);
                acc.salt = salt;
                cout << "Done!\n";
                break;
            }
            case 3:
            {
                int access_level;
                cout<<"New access level of account:\n0 - Admin\n1 - User\n";

                input(access_level, 0, 1);
                acc.access_level = access_level;
                cout << "Done!\n";
                break;
            }
        }
        globals::db_accounts.save();
    }
}

void accounts::delete_select()
{
    while(true)
    {
        system("cls");
        if (globals::db_accounts.accounts.size() == 1)
        {
            cout << "There is only one " << GREEN << "Main Admin" << DEFAULT_COLOR << endl;
            return;
        }

        accounts::show();

        int idx;
        cout << "Choose account to " << RED << "DELETE" << DEFAULT_COLOR << endl;
        cout << "0 - BACK\n";
        input(idx, 2, globals::db_accounts.accounts.size(), {0});
        if (idx == 0)
            return;
        cout << "Do you really want to " << RED << "DELETE" << DEFAULT_COLOR << " this account? [y/n]\n";
        bool b;
        input(b);
        if (b)
            globals::db_accounts.deleteAccount(idx - 1);
        cout << "Done!\n";
        system("pause");
    }
}

void accounts::rejectRequest()
{
    UP_LINES(3);
    CLEAR_TO_END();
    cout << "Choose account to " << PINK << "reject" << DEFAULT_COLOR <<endl;
    int c;
    while(true)
    {
        input(c);
        if ((c < 1 || c > globals::db_accounts.accounts.size()) || globals::db_accounts.accounts[c-1].is_approved)
        {
            cout << "Incorrect input" << "\a\n";
            sleep(1);
            UP_LINES(2);
            CLEAR_TO_END();
        }
        else
        {
            cout << "Do you really want to " << PINK << "REJECT" << DEFAULT_COLOR << " this request and " << RED << "DELETE"<< DEFAULT_COLOR << " this account? [y/n]\n";
            bool b;
            input (b);
            if(!b)
                return;
            globals::db_accounts.deleteAccount(c - 1);
            cout<<"Done!\n";
            system("pause");
            break;
        }
    }
}

void accounts::approveRequest()
{
    UP_LINES(3);
    CLEAR_TO_END();
    cout << "Choose accounts to " << GREEN << "approve" << DEFAULT_COLOR <<endl;
    int c;
    while(true)
    {
        input(c);
        if ((c < 1 || c > globals::db_accounts.accounts.size()) || globals::db_accounts.accounts[c-1].is_approved)
        {
            cout << "Incorrect input" << "\a\n";
            sleep(1);
            UP_LINES(2);
            CLEAR_TO_END();
        }
        else
        {
            cout << "Do you really want to " << GREEN << "Approve" << DEFAULT_COLOR << " this account? [y/n]\n";
            bool b;
            input (b);
            if(!b)
                return;
            globals::db_accounts.approveAccount(c - 1);
            cout<<"Done!\n";
            system("pause");
            break;
        }
    }
}

void accounts::show()
{
    cout.fill('=');
    cout << setw(width::id + width::login + width::hashed_password + width::access + 5) << '=' << endl;
    cout.fill(' ');

    cout << '|' << setw(width::id) << centerString("ID", width::id, ' ') << setw(1) << "|";
    cout << setw(width::login) << centerString("Login", width::login, ' ') << setw(1) << '|';
    cout << setw(width::hashed_password) << centerString("Hashed password", width::hashed_password, ' ') << setw(1) << '|';
    cout << setw(width::access) << centerString("Access", width::access, ' ') << setw(1) << '|' << endl;

    cout.fill('=');
    cout << setw(width::id + width::login + width::hashed_password + width::access + 5) << '=' << endl;
    cout.fill(' ');

    for(int id = 2; id <= globals::db_accounts.accounts.size();id++)
    {
        Account& acc = globals::db_accounts.accounts[id-1];
        if(!acc.is_approved)
            cout << YELLOW;
        cout << '|';
        cout <<setw(width::id) << centerString(id < 10 ? ("0" + to_string(id)) : to_string(id), width::id, ' ')
             << setw(1) << '|';
        cout << setw(width::login) << left << acc.login << setw(1) << '|';
        cout << setw(width::hashed_password) << left << acc.hashed_password << setw(1) << '|';
        cout << setw(width::access) << centerString(acc.access_level == 0 ? "Admin" : "User", width::access, ' ')
             << setw(1) << '|' << endl;
        cout<<DEFAULT_COLOR;
        cout.fill('-');
        cout << setw(width::id + width::login + width::hashed_password + width::access + 5) << '-' << endl;
        cout.fill(' ');

    }
    cout<< YELLOW <<"Yellow" << DEFAULT_COLOR << " accounts are not approved\n";
}

#pragma endregion
