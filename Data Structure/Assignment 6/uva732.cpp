#include<iostream>
#include<stack>
#include<string>
using namespace std;
string str, target;
stack<char> s;
void dfs(int i1, int i2, string ret)
{   
    if (i2 == target.length())
    {
        cout << ret << '\n';
        return;
    }

    if (i1 < str.length())
    {
        s.push(str[i1]);
        dfs(i1 + 1, i2, ret + (ret.empty() ? "i" : " i"));
        s.pop();
    }

    if (!s.empty() && s.top() == target[i2])
    {
        char tmp = s.top();
        s.pop();
        dfs(i1, i2 + 1, ret + (ret.empty() ? "o" : " o"));
        s.push(tmp);
    }
}
int main()
{
    while (cin >> str >> target)
    {
        s = stack<char>();
        cout << "[\n";
        //if (str.length() == target.length() && !str.empty())
        dfs(0, 0, "");
        cout << "]\n";
    }
    return 0;
}