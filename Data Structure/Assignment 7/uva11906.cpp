#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int r, c, m, n, w;
void dfs(int x, int y, vector<vector<int>>& map)
{
	if (x < 0 || x >= r || y < 0 || y >= c || map[x][y] == -1)return;
	if (map[x][y]++ != 0)return;// �p�G��e���I�w�g�����U���L���ܴN�u�n�W�[�i�H�����e���I�����ƧY�i
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
		//0�S���L,>=1���L,-1����(���ਫ)
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
		if (map[0][0] == 0)++even;// �Y (0, 0) �u���b�@�}�l���ɭԨ���L�A�N�� even
		cout << "Case " << ++Case << ": " << even << " " << odd << '\n';
	}
	return 0;
}
