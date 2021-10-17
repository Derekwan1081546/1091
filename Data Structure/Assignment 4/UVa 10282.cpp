#include <iostream>
#include <map>
#include <string>
#include <sstream>
using namespace std;
int main()
{
    map<string, string>m;
    string line;
    while (getline(cin, line), line != "")
    {
        stringstream ss(line);
        string foreign, english;
        ss >> english >> foreign;
        m[foreign] = english;
    }
    while (getline(cin, line))
    {
        m.find(line) == m.end() ? cout << "eh" << '\n' : cout << m[line] << '\n';
    }
    return 0;
}