    #include <iostream>
    #include <vector>
    #include <cstring>
    #include <cstdlib>
    #include <cstdio>
    using namespace std;

    int main()
    {
        int N;
        cin>>N;
        int n;
        cin>>n;
        vector<int>a(n);
        for(int i=0;i<n;i++) cin>>a[i];
        int m;
        cin>>m;
        vector<int>b(m);
        for(int i=0;i<m;i++) cin>>b[i];
        vector<vector<int> >dp(n+1,vector<int>(m+1,0));
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                if(a[i-1]==b[j-1])
                {
                    dp[i][j]=max(dp[i][j-1]+1,dp[i-1][j]+1);
                }
                else
                {
                    dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
                }
            }
        }
        cout<<dp[n][m];
    }
