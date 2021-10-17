#include<iostream>
#include<stack>
#include<queue>
using namespace std;
int main()
{
	int n, cmd, val;
	while (cin >> n)
	{
		//stack: first in last out;
		//queue: first in first out;
		//priority-queue: Always take out large elements first;
		bool S = true, Q = true, PQ = true;
		stack<int>s;
		queue<int>q;
		priority_queue<int>pq;
		while (n--)
		{
			cin >> cmd >> val;
			if (cmd == 1)
			{
				s.push(val);
				q.push(val);
				pq.push(val);
			}
			else
			{
				if (S)
				{
					if (!s.empty() && s.top() == val)s.pop();
					else
						S = false;
				}
				if (Q)
				{
					if (!q.empty() && q.front() == val)q.pop();
					else
						Q = false;
				}
				if (PQ)
				{
					if (!pq.empty() && pq.top() == val)pq.pop();
					else
						PQ = false;
				}
			}
		}
		if ((S && Q) || (S && PQ) || (Q && PQ)) cout << "not sure\n";
		else if (S) cout << "stack\n";
		else if (Q) cout << "queue\n";
		else if (PQ) cout << "priority queue\n";
		else cout << "impossible\n";
	}
	return 0;
}