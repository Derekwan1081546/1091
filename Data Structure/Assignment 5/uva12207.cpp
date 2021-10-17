#include <iostream>
#include <list>
using namespace std;
int main() 
{
    int p, c, n, t = 0;
    char cmd;
    list<int> mlist;
    list<int>::iterator it;
    while (cin >> p >> c && (p || c))
    {
        mlist.clear();
        for (int i = 1; i <= min(p,c); i++) mlist.push_back(i);
        it = mlist.begin();
        cout << "Case " << ++t << ":" << endl;
        while (c--)
        {
            cin >> cmd;
            if (cmd == 'N')
            {
                cout << mlist.front() << endl;
                mlist.push_back(mlist.front());
                mlist.pop_front();
            }
            else
            {
                cin >> n;
                mlist.remove(n);//if (n<=1000) 會WA 可能執行「E 1001 E 1002 E 1001」 會出現兩個1001 
                mlist.push_front(n);
            }
        }
    }
    return 0;
}