#pragma once
#include <fstream>
#include <vector>
#include "Student.h"
using namespace std;
class DB_students//класс для работы со студентами
{
public:
    DB_students(string file);
    string file;
    ifstream fin;
    ofstream fout;
    vector<Student> students;
    void update();//обновить массив
    void save();//сохранить в файл
    void add(Student& acc);//добавить в массив
    void deleteStudent(int idx);//удалить студента
};