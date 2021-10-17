#include<iostream>
#include<stack>
#include<queue>
using namespace std;
bool unload(stack<int>truck, queue<int>station[], int current, int q)
{
	return (!truck.empty() && (truck.top() == current || station[current].size() < q)); //���ư��檽��f�����ũάO�ӯ��I�� Queue �w��
}
int main()
{
	int n, s, q, t;
	cin >> t;
	while (t--)
	{
		stack<int>truck;
		queue<int>station[100];
		cin >> n >> s >> q;
		for (int i = 0; i < n; ++i)
		{
			int nc;
			cin >> nc;
			for (int j = 0; j < nc; ++j)
			{
				int target;
				cin >> target;
				station[i].push(target - 1);
			}
		}
		int current = 0, time = 0;
		while (true)
		{
			while (unload(truck, station, current, q))//���f
			{
				if (truck.top() != current)//�ثe�����I���O�f���n��F�����I
					station[current].push(truck.top());//��J�ӯ��I�� Queue ������
				truck.pop();//�Y�O�h�������U
				time++;
			}
			while (truck.size() < s && (!station[current].empty()))//�˳f,����truck���άO Queue ���ūh���X
			{
				truck.push(station[current].front());//�N���I�� Queue �����f���q�e�ݶ}�l���truck�W
				station[current].pop();
				time++;
			}
			bool clear = truck.empty();
			for (int i = 0; i < n && clear; ++i)clear &= station[i].empty();
			if (clear)break;
			current = (current + 1) % n;
			time += 2;
		}
		cout << time << '\n';
	}
	return 0;
}