#include<iostream>
#include<vector>
#include<string>
#include<iomanip>
#include<sstream>
#include<algorithm>
using namespace std;
int p[10005][205];

int main()
{
    int n; cin >> n;
    int m;
    cin >> m;
    vector<int> like(m);
    for (int i = 0; i < m; i++)
    {
        cin >> like[i];
    }
    int l; cin >> l; vector<int> s(l);
    int num = 0;
    for (int i = 0; i < l; i++)
    {
        cin >> s[i];
        //填好第一行
        if (s[i]==like[0])
        {
            num++;
        }
        p[0][i] = num;
    }
    for (int i = 1; i < m; i++)
    {
        for (int j = 0; j < l; j++)
        {
        //填第一列
            if (j==0)
            {
                if (like[i] == s[0])
                {
                    p[i][0] = p[i - 1][0] + 1;
                }
                else
                    p[i][0] = p[i - 1][0];
            }
            else
            {
            //根据第一行和第一列吧剩下的填完
                if (s[j] == like[i])
                {
                    p[i][j] = p[i][j - 1] + 1;
                }
                else
                {
                    p[i][j] = max(p[i][j - 1], p[i - 1][j]);
                }
            }
        }
    }
    cout << p[m - 1][l - 1] << endl;
    return 0;
}
