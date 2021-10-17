#include <iostream>
#include <string>
#include<map>
#include <iomanip>
using namespace std;

int main()
{
	int c;
	string str;
	cin >> c;
	cin.ignore();
	getline(cin, str);
	while (c--)
	{
		double count = 0;
		string str;
		map<string, double>m;
		while (getline(cin, str) && !str.empty())
		{
			m[str]++;
			count++;
		}
		for (auto it = m.begin(); it != m.end(); ++it)
			cout << it->first << " " << setprecision(4) << fixed << it->second * 100 / count << '\n';

		if (c) cout << '\n';
	}
	return 0;
}