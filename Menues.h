#pragma once
#include <vector>
#include "Core.h"
#include "Student.h"
#include "globals.h"

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
    void showTop();
}
namespace students
{
    void show_select();
    void add_select();
    void edit_select();
    void delete_select();
    void show(vector<Student> &students = globals::db_students.students);
    void showTop();
    void sort_select();
    void individualTask_select();
    void search_select();
    void sort();
}
namespace width
{
    extern int id, login, hashed_password, access;
    extern int name, number, credits[5], exams[5], debts, average_mark;
    extern int sumStud(), sumCredits(), sumExams();

}