#include<iostream>
#include<algorithm>
#include<climits>
#include<queue>
using namespace std;
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n, t, m;
		cin >> n >> t >> m;
		queue<pair<int, int>>q[2];
		vector<int> arriveTime(m);
		int tmp;
		string s;
		for (int i = 0; i < m; i++)
		{
			cin >> tmp >> s;
			s == "left" ? q[0].emplace(i, tmp) : q[1].emplace(i, tmp);
		}
		int time = 0, current = 0;
		while (!q[0].empty() || !q[1].empty())
		{
			int closest = INT_MAX;
			if (!q[0].empty())closest = q[0].front().second;
			if (!q[1].empty())closest = min(closest, q[1].front().second);
			time = max(time, closest);
			int boatsize = 0;
			while (!q[current].empty() && boatsize < n && q[current].front().second <= time)
			{
				arriveTime[q[current].front().first] = time + t;
				q[current].pop();
				++boatsize;
			}
			current ^= 1;
			time += t;
		}
		for (int i = 0; i < arriveTime.size(); i++)
			cout << arriveTime[i] << '\n';
		if (T)cout << '\n';
	}
	return 0;
}