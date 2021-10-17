#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;

vector<vector<int>> G;
vector<int> low, dfn;
int Time, bcn, n, m;

void DFS(int u, int parent)
{
	low[u] = dfn[u] = ++Time;

	for (auto& v : G[u])
	{
		if (dfn[v])
		{
			if(parent!=v) low[u] = min(low[u], dfn[v]);
			continue;
		}

		DFS(v, u);
		low[u] = min(low[u], low[v]);

		if (low[v] > dfn[u]) ++bcn;
	}

}

void solve()
{
	if (bcn == 1)
	{
		cout << "0\n";
		return;
	}

	map<int, int> m;

	for (int u = 1; u <= n; ++u)
	{
		m[low[u]] += 0;
		for (auto& v : G[u])
		{
			if (low[u] != low[v]) ++m[low[u]];
		}
	}
	int ans = 0;

	for (auto& [_, i] : m)
	{
		if (i == 0) ans += 2;
		else if (i == 1) ans += 1;
	}

	cout << (ans + 1) / 2 << "\n";
}

int main()
{
	while (cin >> n >> m)
	{
		G.assign(n + 1, vector<int>());
		low.assign(n + 1, 0);
		dfn.assign(n + 1, 0);
		Time = bcn = 0;

		int x, y;
		for (int i = 0; i < m; ++i)
		{
			cin >> x >> y;
			G[x].push_back(y);
			G[y].push_back(x);
		}

		for (int i = 1; i <= n; ++i) if (!dfn[i]) DFS(i, -1), ++bcn;

		solve();
	}

	return 0;
}

/*
3 2
1 2
2 3
10
11
1 2
2 3
3 1
3 7
4 5
5 6
6 4
7 9
6 3
9 8
7 8

1
2
*/
