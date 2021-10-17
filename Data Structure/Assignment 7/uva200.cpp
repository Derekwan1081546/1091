#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;
vector<int> G[26]; // 比 A 大的字元都會被推入 G[0]，...
int visited[26] = {}; // 1 -> 正在被 DFS，2 -> 已經 DFS 過了
list<char> ret;
void dfs(int n)
{
    if (visited[n] == 1) return; // 碰到環
    visited[n] = 1; // 正在被 DFS

    // 如果 visited[i] != 2 表示還沒被 DFS 過
    for (auto& i : G[n]) if (visited[i] != 2) dfs(i);
    visited[n] = 2;

    ret.push_front(n + 'A');
}
int main()
{
    string str1, str2;
    cin >> str1;

    int mem[26] = {}; // 1 -> 沒有小於其他字元，2 -> 有小於其他字元
    while (cin >> str2 && str2 != "#")
    {
        int l = min(str1.length(), str2.length());
        for (int i = 0; i < l; i++)
        {
            if (!mem[str1[i] - 'A']) mem[str1[i] - 'A'] = 1;
            if (!mem[str2[i] - 'A']) mem[str2[i] - 'A'] = 1;

            if (str1[i] != str2[i])
            {
                G[str1[i] - 'A'].push_back(str2[i] - 'A');
                mem[str2[i] - 'A'] = 2;
                break;
            }
        }
        str1 = str2;
    }
    // 從沒有大於其他字元的字元開始 DFS
    for(int i=0;i<26;i++)
        if (mem[i] == 1) dfs(i);

    for (auto& ch : ret) cout << ch;
    cout << '\n';
	return 0;
}
