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

Student::Student(string name, bool *credits, int *exams, string number)
{
    this->name = name;
    this->number = number;
    *this->credits = credits;
    *this->exams = *exams;
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
        for(int i : f.exams)
            os << i << ' ';
    }
    return os;
}



