#include <iostream>
#include <set>
using namespace std;
int main() 
{
	int n;
	while (cin >> n && n)
	{
		long long sum = 0;
		multiset<int> bills;
		for (int i = 0; i < n; i++)
		{
			int num, tmp;
			cin >> num;
			for (int j = 0; j < num; j++)
			{
				cin >> tmp;
				bills.insert(tmp);
			}
			auto hit = --bills.end(), lot = bills.begin();
			sum += (*hit) - (*lot);
			bills.erase(hit); bills.erase(lot);
		}
		cout << sum << '\n';
	}
	return 0;
}