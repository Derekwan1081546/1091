#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;
int main(int argc, char* argv[])
{
	/*if (argc < 2)return 0;
	ifstream fin(argv[1], ios::binary);*/
	ifstream fin;
	fin.open("test1.bmp", ios::in | ios::binary);
	char output[2000];
	char c[2000];
	int a = 0;
	int n = 0;
	if (!fin) {
		cout << "open fail.\n";
		exit(1);
	}
	else
	{
		fin.read((char*)&output, sizeof(output));
		/*for (int i = 54; i < 1782; i++)
			cout << int(output[i]) << endl;*/
		for (int i = 54; i < 1782; i += 3)
		{
			if (output[i] == -1)
				c[n] = '0';
			else
				c[n] = '1';
			n++;
		}
		for (int j = 0; j < n; j += 8)
		{
			for (int k = 0; k < 9; k++)
			{
				if (c[j + k] == '1')
				{
					a += pow(2, 8 - k - 1);
				}
			}
			char b = a;
			a = 0;
			if (b < 32 || b > 126)
				break;
			cout << b;
		}
	}
	fin.close();
	return 0;
}