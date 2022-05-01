#pragma once
#include <vector>
#include "Core.h"
bool mainMenu();

bool chooseOption(std::vector<void(*)()> args);

void signIn_select();
void signUp_select();
void userMenuAdmin();
void userMenuUser();
namespace accounts
{
    void show_select();
    void add_select();
    void edit_select();
    void delete_select();
    void approveRequests_select();
    void rejectRequest();
    void approveRequest();
    void show();
}
namespace students
{
    void show_select();
    void add_select();
    void edit_select();
    void delete_select();
    void show();
}
namespace width
{
    extern int id, login, hashed_password, access;
    extern int name, number, credits[5], exams[5];
    extern int sumStud(), sumCredits(), sumExams();

}