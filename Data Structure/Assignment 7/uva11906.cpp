#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int r, c, m, n, w;
void dfs(int x, int y, vector<vector<int>>& map)
{
	if (x < 0 || x >= r || y < 0 || y >= c || map[x][y] == -1)return;
	if (map[x][y]++ != 0)return;// 如果當前的點已經有往下走過的話就只要增加可以走到當前的點的次數即可
	int _x = m,_y = n;
	for (int i = 0; i < 2; i++)
	{
		dfs(x + _x, y + _y,map);
		dfs(x - _x, y - _y, map);
		if (_x && _y)
		{
			dfs(x + _x, y - _y, map);
			dfs(x - _x, y + _y, map);
		}
		if (_x == _y)break;
		swap(_x, _y);
	}
}
int main()
{
	int T, Case = 0;
	cin >> T;
	while (T--)
	{
		cin >> r >> c >> m >> n >> w;
		//0沒走過,>=1走過,-1有水(不能走)
		vector<vector<int>> map(r, vector<int>(c));
		for (int i = 0; i < w; i++)
		{
			int x, y;
			cin >> x >> y;
			map[x][y] = -1;
		}
		dfs(0, 0, map);
		--map[0][0];
		int odd = 0, even = 0;
		for (int i = 0; i < map.size(); i++)
		{
			for (int j = 0; j < map[i].size(); j++)
			{
				if (map[i][j] > 0) map[i][j] % 2 == 1 ? ++odd : ++even;	
			}
		}
		if (map[0][0] == 0)++even;// 若 (0, 0) 只有在一開始的時候走到過，代表為 even
		cout << "Case " << ++Case << ": " << even << " " << odd << '\n';
	}
	return 0;
}
