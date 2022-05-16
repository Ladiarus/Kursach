#include "DB_students.h"
#include "MySpace.h"

using namespace std;
DB_students::DB_students(string file) {
    this->file = file;
}

void DB_students::update() {
    students.clear();
    fout.close();
    fin.open(file);
    if(!fin.is_open())
    {
        fout.open(file);
        fout.close();
    }

    if(!isFileEmpty(fin))
    {
        while (!fin.eof())
        {
            Student stud;
            fin >> stud;
            students.push_back(stud);
        }
        fin.close();
    }
}

void DB_students::add(Student &stud) {
    students.push_back(stud);
    save();
}

void DB_students::save() {
    fin.close();
    fout.open(file);
    for(Student acc : students)
        fout<<acc;
    fout.close();
}

void DB_students::deleteStudent(int idx)
{
    students.erase(students.begin() + idx);
    save();
}