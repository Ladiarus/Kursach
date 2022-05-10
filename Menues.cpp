#include <iostream>
#include <conio.h>
#include <string>
#include <iomanip>
#include <algorithm>
#include "Menues.h"
#include "MySpace.h"
#include "Account.h"
#include "globals.h"
#include "Hash/Hash.h"

using namespace std;
namespace width
{
    int id = 6, login = 15, hashed_password = 64, access = 7;
    int name = 34, number = 8, debts = 7, average_mark = 5;
    //! INAD:IKG:LANG:HIST:POLIT ,  MATH:OOP:TRPO:PHYS:OAIP
    int credits[5] = {5, 3, 4, 4, 6};
    int exams[5] = {5, 3, 4, 4, 5};
    int sumStud()
    {
        int sum = 0;
        sum += name + number;
        sum += sumCredits();
        sum += sumExams();
        sum += average_mark;
        sum += debts;
        sum += id;
        return sum;
    }
    int sumCredits()
    {
        int sum=0;
        for(int i : credits)
        {
            sum += i;
        }
        return sum + 4;
    }
    int sumExams()
    {
        int sum=0;
        for(int i : exams)
        {
            sum += i;
        }
        return sum + 4;
    }
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
    system("cls");
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
        cout<<"1 - Show\n2 - Add\n3 - Edit\n4 - Delete\n5 - Approve requests\n\n";
        cout<<"-----DB <Students>-----\n";
        cout<<"6 - Show\n7 - Add\n8 - Edit\n9 - Delete\n0 - Back\n";
        if(chooseOption({accounts::show_select, accounts::add_select, accounts::edit_select, accounts::delete_select, accounts::approveRequests_select,
                         students::show_select, students::add_select, students::edit_select, students::delete_select}))
            return;
    }

}

void userMenuUser()
{
    system("cls");
    students::show_select();

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
            system("pause");
            return;
        }

        accounts::show();
        int idx;
        cout << "Choose account to " << CYAN << "edit" << DEFAULT_COLOR << endl;
        cout << "0 - BACK\n";
        input(idx, 2, globals::db_accounts.accounts.size(), {0});
        if (idx == 0)
            return;
        while (true)
        {
            system("cls");
            accounts::showTop();

            Account &acc = globals::db_accounts.accounts[idx - 1];
            cout << '|';
            cout << setw(width::id) << centerString(idx < 10 ? ("0" + to_string(idx)) : to_string(idx), width::id, ' ')
                 << setw(1) << '|';
            cout << setw(width::login) << left << acc.login << setw(1) << '|';
            cout << setw(width::hashed_password) << left << acc.hashed_password << setw(1) << '|';
            cout << setw(width::access) << centerString(acc.access_level == 0 ? "Admin" : "User", width::access, ' ')
                 << setw(1) << '|' << endl;

            cout.fill('=');
            cout << setw(width::id + width::login + width::hashed_password + width::access + 5) << '=' << endl;
            cout.fill(' ');


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

            if (is_back)
                break;

            UP_LINES(5);
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
                    cout << "New access level of account:\n0 - Admin\n1 - User\n";

                    input(access_level, 0, 1);
                    acc.access_level = access_level;
                    cout << "Done!\n";
                    break;
                }
            }
            globals::db_accounts.save();
        }
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
        cout << "Do you really want to " << RED << "DELETE " << DEFAULT_COLOR << globals::db_accounts.accounts[idx - 1].login << " [y/n]\n";
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
    accounts::showTop();

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

void accounts::showTop()
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
}

#pragma endregion

#pragma region students

void students::show_select()
{
    while(true)
    {
        system("cls");
        if(globals::db_students.students.size()==0)
        {
            cout << "Students database is empty\n";
            system("pause");
            return;
        }
        show();
        cout << "1 - Sort\n2 - Search\n3 - Individual task\n0 - Back\n";

        if(chooseOption({students::sort_select, students::search_select, students::individualTask_select}))
            return;
    }
}

void students::add_select()
{
    system("cls");
    string name, number;
    bool credits[5];
    int exams[5];
    cout << "Input name: ";
    name = inputName();

    cout << "Input number: ";
    number = inputNumber();

    cout << "Input credits:\n";
    inputCredits(credits);

    cout << "Input exams:\n";
    inputExams(exams);

    Student stud(name, number, credits, exams);

    globals::db_students.add(stud);
    cout << "Done!\n";
    system("pause");
}

void students::edit_select()
{
    while(true)
    {
        system("cls");

        if (globals::db_students.students.size() == 1)
        {
            cout << "There is no students" << endl;
            system("pause");
            return;
        }

        int idx;
        show();
        cout << "Choose Student to " << CYAN << "edit" << DEFAULT_COLOR << endl;
        cout << "0 - BACK\n";
        input(idx, 1, globals::db_students.students.size(), {0});
        if (idx == 0)
            return;

        while (true)
        {
            system("cls");
            showTop();

            Student &stud = globals::db_students.students[idx - 1];

            cout << '|' << setw(width::id)
                 << centerString(idx < 10 ? ("0" + to_string(idx)) : to_string(idx), width::id, ' ')
                 << setw(1) << '|';
            cout << setw(width::name) << left << stud.name << setw(1) << '|';
            cout << setw(width::number) << centerString(stud.number, width::number, ' ') << setw(1) << '|';
            cout << right;
            for (int i = 0; i < 5; i++)
            {
                bool b = stud.credits[i];
                int curr_w = width::credits[i];
                if (i == 4)
                    curr_w--;
                if (b)
                {
                    cout << GREEN;
                    cout << setw(curr_w) << 'P';
                }
                else
                {

                    cout << RED;
                    cout << setw(curr_w) << 'F';
                }
                if (i != 4)
                    cout << ' ';
                cout << DEFAULT_COLOR;
            }
            cout << " |";
            cout << DEFAULT_COLOR;
            for (int i = 0; i < 5; i++)
            {
                int x = stud.exams[i];
                int curr_w = width::exams[i];
                if (i == 4)
                    curr_w--;

                if (x > 4)
                {
                    cout << GREEN;
                }
                else if (x == 4)
                {
                    cout << YELLOW;
                }
                else
                {
                    cout << RED;
                }

                cout << setw(curr_w) << x;

                if (i != 4)
                    cout << ' ';
                cout << DEFAULT_COLOR;
            }
            cout << " |";
            cout << fixed << setw(width::average_mark) << setprecision(1) << stud.average_mark << setw(1) << "|";
            if (stud.debts == 0)
                cout << GREEN;
            cout << setw(width::debts) << stud.debts;
            cout << WHITE << '|';
            cout << DEFAULT_COLOR;
            cout << endl;

            cout.fill('=');
            cout << setw(width::sumStud() + 8) << '=' << endl;
            cout.fill(' ');

            int choice;
            cout << "Choose field to " << CYAN << "edit" << DEFAULT_COLOR << endl;
            cout << "1 - Name\n2 - Group\n3 - Credits\n4 - Exams\n0 - Back\n";
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
                if (choice <= 4 && choice > 0)
                {
                    break;
                }

            }

            if (is_back)
                break;

            UP_LINES(6);
            CLEAR_TO_END();


            switch (choice)
            {
                case 1:
                {
                    cout << "New name: ";
                    stud.name = inputName(stud.name);

                    break;
                }
                case 2:
                {
                    cout << "New group: ";
                    stud.number = inputNumber(stud.number);
                    break;
                }
                case 3:
                {
                    cout << "INAD passed  (old " << YELLOW << (stud.credits[0] ? 'y' : 'n') << DEFAULT_COLOR << ") [y/n] : ";
                    stud.credits[0] = inputBool();
                    cout << "\nIKG passed   (old " << YELLOW << (stud.credits[1] ? 'y' : 'n') << DEFAULT_COLOR << ") [y/n]: ";
                    stud.credits[1] = inputBool();
                    cout << "\nLANG passed  (old " << YELLOW << (stud.credits[2] ? 'y' : 'n') << DEFAULT_COLOR << ") [y/n]: ";
                    stud.credits[2] = inputBool();
                    cout << "\nHIST passed  (old " << YELLOW << (stud.credits[3] ? 'y' : 'n') << DEFAULT_COLOR << ") [y/n]: ";
                    stud.credits[3] = inputBool();
                    cout << "\nPOLIT passed (old " << YELLOW << (stud.credits[4] ? 'y' : 'n') << DEFAULT_COLOR << ") [y/n]: ";
                    stud.credits[4] = inputBool();
                    stud.update();
                    break;
                }
                case 4:
                {
                    cout << "Input MATH mark (old " << YELLOW << stud.exams[0] << DEFAULT_COLOR << "):\n";
                    input(stud.exams[0], 0, 10);
                    cin.ignore(1000, '\n');
                    cout << "Input OOP mark  (old " << YELLOW << stud.exams[1] << DEFAULT_COLOR << "):\n";
                    input(stud.exams[1], 0, 10);
                    cin.ignore(1000, '\n');
                    cout << "Input TRPO mark (old " << YELLOW << stud.exams[2] << DEFAULT_COLOR << "): \n";
                    input(stud.exams[2], 0, 10);
                    cin.ignore(1000, '\n');
                    cout << "Input PHYS mark (old " << YELLOW << stud.exams[3] << DEFAULT_COLOR << "):\n";
                    input(stud.exams[3], 0, 10);
                    cin.ignore(1000, '\n');
                    cout << "Input OAIP mark (old " << YELLOW << stud.exams[4] << DEFAULT_COLOR << "):\n";
                    input(stud.exams[4], 0, 10);
                    cin.ignore(1000, '\n');
                    stud.update();
                    break;
                }
            }
            globals::db_students.save();
            cout << "Done!\n";
            system("pause");
        }
    }
}

void students::delete_select()
{
    while(true)
    {
        system("cls");
        show();
        int idx;
        cout << "Choose student to " << RED << "DELETE" << DEFAULT_COLOR << endl;
        cout << "0 - BACK\n";
        input(idx, 1, globals::db_students.students.size(), {0});
        if (idx == 0)
            return;
        cout << "Do you really want to " << RED << "DELETE " << DEFAULT_COLOR << globals::db_students.students[idx - 1].name << " [y/n]\n";
        bool b;
        input(b);
        if (b)
            globals::db_students.deleteStudent(idx - 1);
        cout << "Done!\n";
        system("pause");
    }
}

void students::show(vector<Student> &students)
{
    showTop();

    int idx=1;
    bool is_back = false;
    for(Student &stud : students)
    {
        if(idx % 2==0)
        {
            cout << BACKGROUND_GREY;
            is_back = true;
        }
        else
        {
            cout << DEFAULT_BACKGROUND_COLOR;
            is_back = false;
        }

        cout << '|' << setw(width::id) << centerString(idx < 10 ? ("0" + to_string(idx)) : to_string(idx), width::id, ' ')
             << setw(1) << '|';
        cout << setw(width::name) << left << stud.name << setw(1) << '|';
        cout << setw(width::number) << centerString(stud.number, width::number, ' ') << setw(1) << '|';
        cout << right;
        for(int i = 0; i < 5; i++)
        {
            bool b = stud.credits[i];
            if(is_back)
                cout << BACKGROUND_GREY;
            int curr_w = width::credits[i];
            if(i == 4)
                curr_w--;
            if(b)
            {
                cout << GREEN;
                cout << setw(curr_w) << 'P';
            }
            else
            {

                cout << RED;
                cout << setw(curr_w) << 'F';
            }
            if(i != 4)
                cout << ' ';
            cout << DEFAULT_COLOR;
        }
        if(is_back)
            cout << BACKGROUND_GREY;
        cout << " |";
        cout << DEFAULT_COLOR;
        for(int i = 0; i < 5; i++)
        {
            int x = stud.exams[i];
            if(is_back)
                cout << BACKGROUND_GREY;
            int curr_w = width::exams[i];
            if(i == 4)
                curr_w--;

            if(x > 4)
            {
                cout << GREEN;
            }
            else if(x == 4)
            {
                cout << YELLOW;
            }
            else
            {
                cout << RED;
            }

            cout << setw(curr_w) << x;

            if(i != 4)
                cout << ' ';
            cout << DEFAULT_COLOR;
        }
        if(is_back)
            cout << BACKGROUND_GREY;
        cout << " |";
        cout << fixed <<setw(width::average_mark) << setprecision(1) << stud.average_mark << setw(1) << "|";
        if(stud.debts == 0)
            cout << GREEN;
        cout <<setw(width::debts) << stud.debts;
        cout << WHITE <<'|';
        cout << DEFAULT_COLOR;
        cout << endl;
        idx++;
    }
    cout.fill('=');
    cout << setw( width::sumStud() + 8) << '=' << endl;
    cout.fill(' ');
}

void students::showTop()
{
    cout.fill('=');
    cout << setw( width::sumStud() + 8) << '=' << endl;
    cout.fill(' ');

    //! INAD:IKG:LANG:HIST:POLIT ,  MATH:OOP:TRPO:PHYS:OAIP

    cout << right <<'|' <<setw(width::id + 1) << '|' << setw(width::name + 1) << '|' << setw(width::number + 1) << '|'
         << setw(width::sumCredits()) << centerString("Credits", width::sumCredits(), ' ') << '|'
         << setw(width::sumExams()) << centerString("Exams", width::sumExams(), ' ') << '|'
         << setw(width::average_mark + 1) << '|' << setw(width::debts +1 ) << '|' << endl;

    cout << '|' << setw(width::id) << centerString("ID", width::id, ' ') << setw(1) << '|';
    cout << setw(width::name) << centerString("Name", width::name, ' ') << setw(1) << '|';
    cout << setw(width::number) << centerString("Group#", width::number, ' ') << setw(1) << '|';

    cout << setw(width::credits[0]) << "INAD" << setw(1) << ':';
    cout << setw(width::credits[1]) << "IKG" << setw(1) << ':';
    cout << setw(width::credits[2]) << "LANG" << setw(1) << ':';
    cout << setw(width::credits[3]) << "HIST" << setw(1) << ':';
    cout << left << setw(width::credits[4]) << "POLIT" << setw(1) << '|';

    cout << right << setw(width::exams[0]) << "MATH" << setw(1) << ':';
    cout << setw(width::exams[1]) << "OOP" << setw(1) << ':';
    cout << setw(width::exams[2]) << "TRPO" << setw(1) << ':';
    cout << setw(width::exams[3]) << "PHYS" << setw(1) << ':';
    cout << left << setw(width::exams[4]) << "OAIP" << setw(1) << '|' << right;

    cout << setw(width::average_mark) << centerString("Avg", width::average_mark, ' ') << setw(1) << '|';
    cout << setw(width::debts) << centerString("Debts", width::debts, ' ') << setw(1) << '|' << endl;

    cout.fill('=');
    cout << setw(width::sumStud() + 8) << '=' << endl;
    cout.fill(' ');
}

void students::sort_select()
{
    system("cls");
    cout << "Choose sort field:\n";
    cout << "1 - Name\n2 - Group\n3 - Average mark\n4 - Debts\n0 - Back\n";

    char choice;
    while (true)
    {
        choice = getch();
        choice -= '0';
        if (choice == 0)
        {
            return;

        }
        if (choice <= 4 && choice > 0)
        {
            break;
        }
    }

    vector<Student> v = globals::db_students.students;

    switch (choice)
    {
        case 1:
            sort(v.begin(), v.end(), [](Student& a, Student& b) ->bool {return a.name < b.name;});
            break;
        case 2:
            sort(v.begin(), v.end(), [](Student& a, Student& b) ->bool {return a.number < b.number;});
            break;
        case 3:
            sort(v.begin(), v.end(), [](Student& a, Student& b) ->bool {return a.average_mark > b.average_mark;});
            break;
        case 4:
            sort(v.begin(), v.end(), [](Student& a, Student& b) ->bool {return a.debts < b.debts;});
            break;
    }
    system("cls");
    show(v);
    system("pause");

}

void students::individualTask_select()
{
    vector<Student> v = globals::db_students.students;
    sort(v.begin(), v.end(), [](Student& a, Student& b) ->bool {return a.debts > b.debts;});
    vector<Student> gr;
    string group;
    double sum = 0;
    while(true)
    {
        system("cls");
        show(v);
        cout << "Input group number: ";
        group = inputNumber();

        for (Student &stud: v)
        {
            if (stud.number == group)
            {
                gr.push_back(stud);
                sum += stud.average_mark;
            }
        }

        if (gr.empty())
        {
            cout << "Group does not exist\n";
            system("pause");
        }
        else
            break;
    }
    system("cls");
    show(gr);
    cout << "Group " << group << " average mark: " << sum / gr.size() << endl;
    system("pause");
}

void students::search_select()
{
    while(true)
    {
        system("cls");
        cout << "Choose search field:\n";
        cout << "1 - Name\n2 - Group\n3 - Average mark\n4 - Debts\n0 - Back\n";

        char choice;
        while (true)
        {
            choice = getch();
            choice -= '0';
            if (choice == 0)
            {
                return;

            }
            if (choice <= 4 && choice > 0)
            {
                break;
            }
        }
        string s;
        double a, b;
        vector<Student> v;
        switch (choice)
        {
            case 1:
                cout << "Input name: ";
                if(cin.peek()=='\n')
                    cin.get();
                getline(cin, s);
                for (Student &stud: globals::db_students.students)
                {
                    if (to_upper(stud.name).find(to_upper(s))!=-1)
                        v.push_back(stud);
                }
                break;
            case 2:
                cout << "Input group: ";
                s = inputNumber();
                for (Student &stud: globals::db_students.students)
                {
                    if (stud.number == s)
                        v.push_back(stud);
                }
                break;
            case 3:
                cout << "Input min average mark\n";
                input(a, 0.0, 10.0);
                cin.ignore(10000, '\n');
                cout << "Input max average mark\n";
                input(b, a, 10.0);
                cin.ignore(10000, '\n');
                for (Student &stud: globals::db_students.students)
                {
                    if (stud.average_mark >= a && stud.average_mark <= b)
                        v.push_back(stud);
                }
                break;
            case 4:
                cout << "Input debts amount: ";
                input(a, 0, 10);
                cin.ignore(10000, '\n');
                for (Student &stud: globals::db_students.students)
                {
                    if (stud.debts == a)
                        v.push_back(stud);
                }
                break;
        }

        system("cls");
        if (v.size() == 0)
            cout << "There is nothing to show\n";
        else
            show(v);
        system("pause");
    }
}


#pragma endregion