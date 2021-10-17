#include<iostream>
#include<algorithm>
#include<string>
#include<sstream>
using namespace std;
int G[26][26] = {};
int visited[26] = {};
bool track;
string S;
void dfs(string ret)
{
    if (ret.length() == S.length()) 
    { 
        cout << ret[0];
        for (int i = 1; i < ret.size(); i++)
            cout << " " << ret[i];
        cout << '\n';
        track = true;
        return;
    } 
    for (int i = 0; i < S.size(); i++)
    {
        if (!visited[S[i] - 'A'])
        {
            int j = 0;
            for (; j < ret.size(); j++) if (G[S[i] - 'A'][ret[j] - 'A']) return;
            // back tracking
            visited[S[i] - 'A'] = 1;
            dfs(ret + S[i]);
            visited[S[i] - 'A'] = 0;
        }
    }
}
int main()
{
    int T;
    string str;
    cin >> T;
    cin.ignore();
    while (T--)
    {
        getline(cin, str); // avoid space
        // init
        track = false;
        fill(G[0], G[0] + 676, 0);
        fill(visited, visited + 26, 0);
        S.clear();
        // 讀取英文字母
        getline(cin, str);
        stringstream ss(str);
        while (ss >> str) S += str;
        sort(begin(S), end(S));
        getline(cin, str);
        ss.clear();
        ss.str(str);
        // 紀錄不能出現在 str[0] 前面的字元
        while (ss >> str) G[str[0] - 'A'][str[2] - 'A'] = 1;
        dfs("");
        if (!track) cout << "NO\n";
        if (T) cout << '\n';
    }
	return 0;
}
