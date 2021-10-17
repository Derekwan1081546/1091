#include<iostream>
#include<stack>
#include<queue>
using namespace std;
bool unload(stack<int>truck, queue<int>station[], int current, int q)
{
	return (!truck.empty() && (truck.top() == current || station[current].size() < q)); //重複執行直到貨車為空或是該站點的 Queue 已滿
}
int main()
{
	int n, s, q, t;
	cin >> t;
	while (t--)
	{
		stack<int>truck;
		queue<int>station[100];
		cin >> n >> s >> q;
		for (int i = 0; i < n; ++i)
		{
			int nc;
			cin >> nc;
			for (int j = 0; j < nc; ++j)
			{
				int target;
				cin >> target;
				station[i].push(target - 1);
			}
		}
		int current = 0, time = 0;
		while (true)
		{
			while (unload(truck, station, current, q))//卸貨
			{
				if (truck.top() != current)//目前的站點不是貨物要到達的站點
					station[current].push(truck.top());//放入該站點的 Queue 的尾端
				truck.pop();//若是則直接卸下
				time++;
			}
			while (truck.size() < s && (!station[current].empty()))//裝貨,直到truck滿或是 Queue 為空則跳出
			{
				truck.push(station[current].front());//將站點的 Queue 中的貨物從前端開始放到truck上
				station[current].pop();
				time++;
			}
			bool clear = truck.empty();
			for (int i = 0; i < n && clear; ++i)clear &= station[i].empty();
			if (clear)break;
			current = (current + 1) % n;
			time += 2;
		}
		cout << time << '\n';
	}
	return 0;
}