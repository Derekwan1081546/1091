#include <iostream>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;
int main() 
{
	int n;
	cin >> n;
	while (n--)
	{
		int t, tmp, l = 0, r = 0, ret = 0;
		vector<int> v;
		set<int> s;
		cin >> t;
		while (t--)
		{
			cin >> tmp;
			while (s.count(tmp)) s.erase(v[l++]);
			s.insert(tmp);
			v.push_back(tmp);//emplace_back
			ret = max(r - l + 1, ret);
			r++;
		}
		cout << ret << '\n';
	}
}