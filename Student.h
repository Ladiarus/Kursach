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
    string name;
    bool credits[5];
    int exams[5];
    string number;
    int debts;
    double average_mark;

    void update();
    friend std::istream &operator >> (std::istream &is, Student &f);
    friend std::ostream& operator << (std::ostream &os, Student& f);
};

