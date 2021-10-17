#include<iostream>
#include<queue>
using namespace std;
int main()
{
	int n, temp;
	priority_queue<int, vector<int>, greater<int>> p;
	while (cin >> n && n)
	{
		int output = 0;
		while (n--)
		{
			cin >> temp;
			p.push(temp);
		}
		while (p.size() > 1)
		{
			int a = p.top();
			p.pop();
			a += p.top();
			p.pop();
			output+= a;
			p.push(a);
		}
		cout << output <<'\n';
		p.pop();
	}
	return 0;
}