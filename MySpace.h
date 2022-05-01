#pragma once
#include <iostream>
#include <unistd.h>
#include <vector>

#define RED "\033[31;1m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34;1m"
#define CYAN "\033[36;1m"
#define DEFAULT_COLOR "\033[m"
#define PINK "\033[35;1m"
#define BACKGROUND_GREY "\033[48;5;235m"
#define DEFAULT_BACKGROUND_COLOR "\033[40m"

#define CLEAR_LINE() (cout<<"\033[2K")
#define CLEAR_TO_END() (cout<<"\033[0J")
#define TO_COLUMN(num) (cout<<"\033["+to_string(num)+"G")
#define TO_POSITION(row, column) (cout<<"\033[" + to_string(row) + ";" + to_string(column) +"H")
#define CLEAR_LINE_TO_END() (cout<<"\033[0K")
#define UP_LINE() (cout << "\033[1A")
#define UP_LINES(x) (cout << "\033[" + to_string(x) + "F")
#define DOWN_LINES(x) (cout << "\033[" + to_string(x) + "E")
using namespace std;
template <typename T>
void input(T& a)
{
    while (true)
    {
        std::cin >> a;
        if (std::cin.fail() || (std::cin.peek() != '\n' && std::cin.peek() != ' ' && std::cin.peek() != '\t'))
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            cout << "Incorrect input"<<"\a\n";
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
void input(int& x, int a, int b);
void input(int& x, int a, int b, vector<int> additionalValues);
void input(double& x, double a, double b);
void input(bool& b);
std::string centerString(const std::string& s, int width, char fill_with);
bool isFileEmpty(std::ifstream& file);