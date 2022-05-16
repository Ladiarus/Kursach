#pragma once
#include <vector>
#include "Core.h"
#include "Student.h"
#include "globals.h"

bool mainMenu(); //главное меню

bool chooseOption(std::vector<void(*)()> args);//вспомогательная функция, обрабатывающая выбор, сделанный пользователем
/// функции, заканчивающиеся на _select, вызываются при выборе их пользователем
void signIn_select();//вход
void signUp_select();//регистрация
void userMenuAdmin();//меню админа
void userMenuUser();//меню пользователя
namespace accounts //пространство имен аккаунтов
{
    void show_select();//выбор показать
    void add_select();//выбор добавить
    void edit_select();//выбор изменить
    void delete_select();//выбор удалить
    void approveRequests_select();//выбор подтвердить запросы
    void rejectRequest();//отклонить запрос
    void approveRequest();//подтвердить запрос
    void show();//показать
    void showTop();//показать шапку
}
namespace students//пространство имен студентов
{
    void show_select();//выбор показать
    void add_select();//выбор добавить
    void edit_select();//выбор изменить
    void delete_select();//выбор удалить
    void show(vector<Student> &students = globals::db_students.students);//показать
    void showTop();//показать шапку
    void sort_select();//выбор сортировка
    void individualTask_select();//выбор индивидуальное задание
    void search_select();//выбор поиск
}
namespace width //заданные значение ширины столбцов таблиц
{
    extern int id, login, hashed_password, access;
    extern int name, number, credits[5], exams[5], debts, average_mark;
    extern int sumStud(), sumCredits(), sumExams();

}