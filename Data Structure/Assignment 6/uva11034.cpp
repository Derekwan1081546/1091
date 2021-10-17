#include<iostream>
#include<queue>
using namespace std;
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int l, m;
		cin >> l >> m;
		queue<int>q[2];
		string s;
		int tmp;
		for (int i = 0; i < m; ++i)
		{
			cin >> tmp >> s;
			s == "left" ? q[0].push(tmp) : q[1].push(tmp);// 0 for left, 1 for right
		}
		int count = 0, current = 0;
		while (!q[0].empty() || !q[1].empty())//兩邊都空則跳出
		{
			int length = l * 100;
			while (!q[current].empty() && q[current].front() <= length)
			{
				length -= q[current].front();
				q[current].pop();
			}
			current ^= 1;//XOR
			++count;
		}
		cout << count << '\n';
	}
	return 0;
}