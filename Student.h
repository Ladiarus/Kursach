#pragma once

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class Student
{
public:
    Student(string name, bool *credits, int *exams, string number);
    Student(){};
    string name;
    bool credits[5];
    int exams[5];
    string number;

    friend std::istream &operator >> (std::istream &is, Student &f);
    friend std::ostream& operator << (std::ostream &os, Student& f);
};
