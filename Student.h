#pragma once

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class Student
{
public:
    Student(string name, string number, bool credits[5], int exams[5]);
    Student(){};
    string name;//фио
    bool credits[5];//зачеты
    int exams[5];//оценуи экзаменов
    string number;//номер группы
    int debts;//задолженности
    double average_mark;//средний балл

    void update();//обновить информацию о студенте (посчитать средний балл и задолженности)
    friend std::istream &operator >> (std::istream &is, Student &f);
    friend std::ostream& operator << (std::ostream &os, Student& f);
};