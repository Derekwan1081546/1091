#include<iostream>
#include<stack>
#include<string>
#include<list>
#include<sstream>
using namespace std;
int main()
{
	stack<char>s;
	list<char>list;
	int n;
	cin >> n;
	cin.ignore();
	while (n--)
	{
		list.clear();
		s = stack<char>();
		string str;
		getline(cin, str);
		if (str == " ")cout << "Yes" << endl;
		/*else if (str.size() % 2 == 0)
		{

			
		}
		else
			cout << "No" << endl;*/

		/*s.push(str[0]);
			list.push_back(str[0]);*/
		for (int i = 0; i < str.size(); i++)
		{
			s.push(str[i]);
			list.push_back(str[i]);
			/*if (s.size() == 0)
			{
				s.push(str[i + t]);
				list.push_back(str[i + t]);
			}
			else if (s.top() == '(' || s.top() == '[')
			{

				s.push(str[i + t]);
				list.push_back(str[i + t]);

			}*/
			if (s.top() == ')')
			{
				list.pop_back();
				if (list.empty())break;
				if (list.back() == '(')
				{
					s.pop();
					s.pop();
					list.pop_back();
				}
			}
			else if (s.top() == ']')
			{
				list.pop_back();
				if (list.empty())break;
				if (list.back() == '[')
				{
					s.pop();
					s.pop();
					list.pop_back();
				}
			}
			else if (s.top() == ' ')
			{
				list.pop_back();
				s.pop();
			}
		}
		if (!s.empty())
			cout << "No" << endl;
		else
			cout << "Yes" << endl;
	}
	return 0;
}
