#include<iostream>
#include<list>
#include<string>
using namespace std;
int main()
{
	string input;
	while (getline(cin, input))
	{
		list<char> output;
		auto it = output.begin();//list<char>::iterator
		for (int i = 0; i < input.size(); ++i)
		{
			if (input[i] == '[')
				it = output.begin();
			else if (input[i] == ']')
				it = output.end();
			else
				output.insert(it, input[i]);
		}
		for (it = output.begin(); it != output.end(); ++it)cout << *it;
		cout << endl;
	}
	return 0;
}
