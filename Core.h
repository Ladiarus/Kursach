#pragma once
#include "DB_accounts.h"
#include "MySpace.h"

void mainFunc();
void signIn(string login, string password);
string inputPassword();
Account* signUp();
string inputNumber(string s = "");
string inputName(string s = "");
void *inputCredits(bool *arr);
bool inputBool();
void *inputExams(int *arr);