#pragma once
#include <fstream>
#include <vector>
#include "Student.h"
using namespace std;
class DB_students
{
public:
    DB_students(string file);
    string file;
    ifstream fin;
    ofstream fout;
    vector<Student> students;
    void update();
    void save();
    void add(Student& acc);
    void deleteStudent(int idx);
};