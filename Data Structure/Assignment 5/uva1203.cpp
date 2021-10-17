#include<iostream>
#include<queue>
using namespace std;

struct Register
{
	int num;
	int period;
	int time;
	bool operator<(const Register& r)const
	{
		return (time > r.time || (time == r.time && num > r.num));
	}
};

int main()
{
	priority_queue<Register> output;
	string in;
	int num, time;
	while (cin >> in && in != "#")
	{
		cin >> num >> time;
		output.push({ num,time,time });
	}
	cin >> num;
	for (int i = 0; i < num; i++)
	{
		Register temp = output.top();
		output.pop();
		cout << temp.num << '\n';
		output.push({ temp.num,temp.period,temp.time + temp.period });
	}
	return 0;
}