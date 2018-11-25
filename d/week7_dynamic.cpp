#include <iostream>
#include <vector>
#define max 200
#define max2 10000
#define MAX(a,b) (((a)>(b))? (a) : (b))
using namespace std;
vector<int> favourite;
vector<int> rope;
int colornumber;
int number1;
int number2;
int main()
{


    favourite.reserve(max);
    rope.reserve(max2);
    cin>>colornumber;
    cin>>number1;
    for(int i=1; i<=number1; i++)
    {
        int j;
        cin>>j;
        favourite.push_back(j);
//        cout<<favourite[i-1];
    }


    cin>>number2;
    vector<vector<int> > cao(number1+1,vector<int>(number2+1,0));
    for(int i=1; i<=number2; i++)
    {
        int j;
        cin>>j;
        rope.push_back(j);
//        cout<<rope[i-1];
    }


    for(int i=1; i<=number1; i++)
        for(int j=1; j<=number2; j++)
    {
//        cout<<"i ="<<i<<"j = "<<j<<endl;
        if(favourite[i-1] == rope[j-1])
            cao[i][j] = MAX(cao[i-1][j],cao[i][j-1])+1;

        else
            cao[i][j] = MAX(cao[i-1][j],cao[i][j-1]);
//        cout<< cao[i][j];
    }

    cout<<cao[number1][number2];



    return 0;
}
