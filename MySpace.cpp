#include"MySpace.h"
#include <cstdlib>
#include <fstream>


using namespace std;

void input(int& x, int a, int b)
{
    while (true)
    {
        input(x);
        if (x < a || x > b)
        {
            cout << "Incorrect input [ " + to_string(a) + ", " + to_string(b) + " ]\n"<<"\a";
            cin.ignore(1000, '\n');
            sleep(1);
            CLEAR_LINE();
            UP_LINE();
            CLEAR_LINE();
            UP_LINE();
            CLEAR_LINE();
        }
        else
        {
            return;
        }
    }
}
void input(double& x, double a, double b)
{
    while (true)
    {
        input(x);
        if (x < a || x > b)
        {
            cout << "Incorrect input [ " + to_string(a) + ", " + to_string(b) + " ]\n"<<"\a";
            cin.ignore(1000, '\n');
            sleep(1);
            CLEAR_LINE();
            UP_LINE();
            CLEAR_LINE();
            UP_LINE();
            CLEAR_LINE();
        }
        else
        {
            return;
        }
    }
}
void input(bool& b)
{
    char c;
    while (true)
    {
        input(c);
        if (c != 'y' && c != 'n')
        {
            cout << "Incorrect input [ y / n ]\n"<<"\a";
            sleep(1);
            CLEAR_LINE();
            UP_LINE();
            CLEAR_LINE();
            UP_LINE();
            CLEAR_LINE();
        }
        else
        {
            b = c == 'y';
            return;
        }
    }
}

string centerString(const string &s, int width, char fill_with)
{
    string ret_str;
    int x = (width - s.length())/2;
    for (int i = 0; i < x; i++)
    {
        ret_str += fill_with;
    }
    ret_str += s;
    for (int i = ret_str.length() ; i < width; i++)
    {
        ret_str += fill_with;
    }
    return ret_str;
}

void input(int &x, int a, int b, vector<int> additionalValues)
{
    while (true)
    {
        input(x);
        if ((x < a || x > b) && (std::find(additionalValues.begin(), additionalValues.end(), x) == additionalValues.end()))
        {
            cout << "Incorrect input [ " + to_string(a) + ", " + to_string(b) + " ]\n"<<"\a";
            sleep(1);
            CLEAR_LINE();
            UP_LINE();
            CLEAR_LINE();
            UP_LINE();
            CLEAR_LINE();
        }
        else
            return;
    }
}

bool isFileEmpty(ifstream &file)
{
    return file.peek() == std::ifstream::traits_type::eof();
}

string to_upper(string s)
{
    for(char &c : s)
    {
        c = toupper(c);
    }
    return s;
}