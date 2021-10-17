#include<iostream>
#include<vector>
using namespace std;
vector<int> adj;
vector<bool> visited, dfsv;
int dfs(int now)
{
	if (dfsv[now])return 0;
	visited[now] = dfsv[now] = true;
	return 1 + dfs(adj[now]);
}
int main()
{
	int T, cn = 1;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		adj.assign(n + 1, 0);
		for (int i = 0; i < n; i++)
		{
			int l, a;
			cin >> l >> a;
			adj[l] = a;
		}
		visited.assign(n + 1, false);
		int output = 0, max = -1, ret = 0;
		for (int i = 1; i <= n; i++)
		{
			if (visited[i] == false)
			{
				dfsv.assign(n + 1, false);
				output = dfs(i);
				if (output > max)
					max = output, ret = i;
			}
		}
		cout << "Case " << cn++ << ": " << ret << '\n';
	}
	return 0;
}