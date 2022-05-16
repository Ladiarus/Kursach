#pragma once
#include "DB_accounts.h"
#include "MySpace.h"

void mainFunc();//главная функция, вызываемая в main
void signIn(string login, string password);//вход
string inputPassword();//ввод пароля
Account* signUp();//регистрация
string inputNumber(string s = "");//ввод номера группы
string inputName(string s = "");//ввод фио студента
void *inputCredits(bool *arr);//ввод результатов зачетов
bool inputBool();//ввод результата зачета
void *inputExams(int *arr);//ввод результатов экзаменов