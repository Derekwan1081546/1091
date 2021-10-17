#include<iostream>
#include<stack>
#include<queue>
using namespace std;
int main()
{
	int n, val;
	while (cin >> n && n)
	{
		while (cin >> val && val)
		{
			stack<int>s;
			queue<int>q;
			q.push(val);
			for (int i = 1; i < n; i++)
			{
				cin >> val;
				q.push(val);
			}
			for (int i = 1; i <= n; i++)
			{
				s.push(i);
				while (!s.empty() && s.top() == q.front())
					s.pop(), q.pop();
			}
			cout << (s.empty() ? "Yes\n" : "No\n");
		}
		cout << '\n';
	}
	return 0;
}