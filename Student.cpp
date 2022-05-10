#include "Student.h"

using namespace std;

string replaceChars(string s, char a, char b)
{
    for(char & i : s)
    {
        if(i == a)
            i = b;
    }
    return s;
}

Student::Student(string name, string number, bool credits[5], int exams[5])
{
    this->name = name;
    this->number = number;
    for(int i = 0; i < 5; i++)
    {
        this->credits[i] = credits[i];
        this->exams[i] = exams[i];
    }

    update();
}

std::istream &operator>>(istream &is, Student &f)
{
    if(typeid(is) == typeid(ifstream))
    {
        string name;
        is >> name;
        f.name = replaceChars(name, '_', ' ');
        is >> f.number;
        for(bool &b : f.credits)
            is >> b;
        for(int &i : f.exams)
            is >> i;
    }
    f.update();
    return is;
}

std::ostream &operator<<(ostream &os, Student &f)
{
    if(typeid(os) == typeid(ofstream))
    {
        string name;
        os << endl;
        name = replaceChars(f.name, ' ', '_');
        os << name <<' ';
        os << f.number <<' ';
        for(bool i : f.credits)
            os << i << ' ';
        for(int i = 0; i < 5; i++)
        {
            os << f.exams[i];
            if(i != 4)
                os << ' ';
        }
    }
    f.update();
    return os;
}

void Student::update()
{
    average_mark = 0;
    debts = 0;
    for (int i : exams)
    {
        average_mark += i;
        if(i < 4)
            debts++;
    }
    average_mark /= 5;

    for(bool b : credits)
    {
        if(!b)
            debts++;
    }

}