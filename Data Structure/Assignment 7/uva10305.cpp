#include<iostream>
#include<vector>
#include<list>
using namespace std;
int mem[101]; // 0 -> 沒有被其他點連入，1 -> 被其他點連入
int visited[101];
vector<int> G[101];
list<int> ret;
void dfs(int n)
{
	if (visited[n])return;
	visited[n] = 1;
	for (auto& i : G[n]) dfs(i);
	ret.push_front(n);
}
int main()
{
	int n, m;
	while (cin >> n >> m && (n || m))
	{
		ret.clear();//initial
		fill(mem, mem + 101, 0);
		fill(visited, visited + 101, 0);
		fill(G, G + 101, vector<int>());
		for (int i = 0; i < m; i++)
		{
			int a, b;
			cin >> a >> b;
			G[a].push_back(b);
			mem[b] = 1;
		}
		for (int i = 1; i <= n; i++)
			if (!mem[i])
				dfs(i);
		cout << ret.front();
		for (auto it = ++ret.begin(); it != ret.end(); ++it)
			cout << " " << *it;
		cout << '\n';
	}
	return 0;
}