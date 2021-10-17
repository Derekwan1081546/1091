#include <iostream>
#include <vector>
#include<queue>
using namespace std;
int main() 
{
	int n;
	cin >> n;
	while (n--)
	{
		int b, sg, sb, tmp;
		cin >> b >> sg >> sb;
		priority_queue<int> G, B;
		while (sg--) cin >> tmp, G.push(tmp);
		while (sb--) cin >> tmp, B.push(tmp);
		while (!G.empty() && !B.empty())
		{
			vector<int> battle;
			for (int i = 0; i < b; ++i)
			{
				if (G.empty() || B.empty()) break;
				battle.push_back(G.top() - B.top());
				G.pop(), B.pop();
			}
			for (int i = 0; i < battle.size(); i++)
			{
				if (battle[i] > 0) G.push(battle[i]);
				else if (battle[i] < 0) B.push(-battle[i]);
			}
		}
		if (G.empty() && B.empty()) cout << "green and blue died\n";
		else
		{
			if (!G.empty())
			{
				cout << "green wins\n";
				while (!G.empty()) cout << G.top() << '\n', G.pop();
			}
			else
			{
				cout << "blue wins\n";
				while (!B.empty()) cout << B.top() << '\n', B.pop();
			}
		}
		if (n) cout << '\n';
	}
	return 0;
}