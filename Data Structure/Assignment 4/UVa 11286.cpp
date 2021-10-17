#include <algorithm>
#include <iostream>
#include <map>
using namespace std;
int courses[5];
int main()
{
	int n;
	while (cin >> n && n) 
	{
		map<long long, int> Map;
		int maxv = 1, count = 0;
		while(n--) 
		{
			for (int i = 0; i < 5; ++i)
				cin >> courses[i];
			sort(courses, courses + 5);
			long long value = 0;
			for (int i = 0; i < 5; ++i) {
				value *= 100;
				value += courses[i];
			}
			maxv = max(maxv, Map[value] += 1);
		}
		for (auto it = Map.begin(); it != Map.end(); ++it)//map<long long, int>::iterator
			if (it->second == maxv)
				count += maxv;
		cout << count << endl;
	}
	return 0;
}