#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;
vector<int> G[26]; // �� A �j���r�����|�Q���J G[0]�A...
int visited[26] = {}; // 1 -> ���b�Q DFS�A2 -> �w�g DFS �L�F
list<char> ret;
void dfs(int n)
{
    if (visited[n] == 1) return; // �I����
    visited[n] = 1; // ���b�Q DFS

    // �p�G visited[i] != 2 ����٨S�Q DFS �L
    for (auto& i : G[n]) if (visited[i] != 2) dfs(i);
    visited[n] = 2;

    ret.push_front(n + 'A');
}
int main()
{
    string str1, str2;
    cin >> str1;

    int mem[26] = {}; // 1 -> �S���p���L�r���A2 -> ���p���L�r��
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
    // �q�S���j���L�r�����r���}�l DFS
    for(int i=0;i<26;i++)
        if (mem[i] == 1) dfs(i);

    for (auto& ch : ret) cout << ch;
    cout << '\n';
	return 0;
}
