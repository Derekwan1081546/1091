#include<iostream>
#include<vector>
#include<string>
using namespace std;
void dfs(vector<vector<char>>graph, char m, char t, int k, vector<int> candle, int steps)
{
	if (steps && steps % k == 0)
	{
		cout << t << " ";
		candle[t - 'A'] = 1;
	}
	auto& v = graph[m - 'A'];//vector<char>
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] != t && !candle[v[i] - 'A'])
		{
			steps++;
			dfs(graph, v[i], m, k, candle, steps);
			return;
		}
	}
	cout << "/" << m << '\n';
}
int main()
{
	string s;
	while (cin >> s && s != "#")
	{
		int k;
		char m, t;
		cin >> m >> t >> k;
		// 讀取資料並建立圖
		vector<vector<char>>graph(26);
		for (int i = 0; i < s.size();)
		{
			if (s[i] == ':')
			{
				int j = i + 1;
				while (s[j] != ';' && s[j] != '.')
					graph[s[i - 1] - 'A'].push_back(s[j++]);
				i = j + 1;
			}
			else i++;
		}
		int steps = 0;
		vector<int>candles(26);
		dfs(graph, m, t, k, candles, steps);
	}
	return 0;
}