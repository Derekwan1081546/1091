#include<iostream>
#include<string>
#include<vector>
#include<stack>
using namespace std;
vector<stack<char>> v;
void AddToStack (char ch)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (ch <= v[i].top())
        {
            v[i].push(ch);
            return;
        }
    }
    v.push_back(stack<char>());
    v.back().push(ch);
}
int main()
{
    int cnt = 0;
    char ch;
    string input;
    while (cin >> input && input != "end")
    {
        v.clear();
        for (int i = 0; i < input.size(); i++)
        {
            ch = input[i];
            AddToStack(ch);
        }
        cout << "Case " << ++cnt << ": " << v.size() << '\n';
    }

	return 0;
}