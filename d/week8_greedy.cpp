#include<iostream>
#include<vector>
#include<algorithm>
#include <iomanip>
using namespace std;
#define max1 1000
#define max2 300000
#define max3 20
#define max4 500


typedef pair <int,double> GasStation;
bool comp(const GasStation &a, const GasStation &b)
{
     return a.first < b.first;
}
int main()
{cout.setf(ios::fixed);
	int Cmax;
	int Distance;
	int Davg;
 	int GasStations;
    double where;
    double cost = 0;
    double tank = 0;
    vector <GasStation> x;
    x.reserve(max4);

    cin>>Cmax>>Distance>>Davg>>GasStations;
    for(int i=0; i<GasStations; i++)
    {
    	double priceperunit;
    	int miles;

    	cin>>priceperunit>>miles;
    	x.push_back(GasStation(miles,priceperunit));
    }
     sort(x.begin(),x.end(),comp);
   //  for (int i = 0; i<x.size();i++)
   //  cout<<x[i].second<<'\t'<<x[i].first<<endl;
        int q = 0;
        for(int i=0; i<GasStations; i = q)
        {
            where = x[i].first;
            if(i+1<GasStations&&x[i].second > x[i+1].second && x[i+1].first - x[i].first <= Cmax*Davg )//有更便宜的
            {
             if(tank >=(x[i+1].first-x[i].first)*1.0/Davg )
             {
                 tank -= (x[i+1].first-x[i].first)*1.0/Davg;
             }
             else
             {
                 cost += ((x[i+1].first-x[i].first)*1.0/Davg - tank)*x[i].second ;
                 tank = 0;
             }


               q = i+1;
           //    cout<<"now find first cheaper from: "<<i<<"to: "<<q<<endl;
          //  cout <<"cost = "<<cost <<endl;
            }
            else
            {  double m = 100000;
               int g = i;
               int p = 0;
               for(int j=i+1; j<GasStations&&(x[j].first - x[i].first <= Cmax*Davg); j++)
               {
                   if(x[j].second < x[i].second)
                   {
                       p = 1;
                       g = j;
                       break;
                   }
                   if(x[j].second < m&&x[j].second >= x[i].second) {m = x[j].second;g = j;
                 //  cout<<"here is "<<m<<"   "<<j<<endl;
                   }
               }
               if(p == 1)//有便宜的,加到
               {
                   if(tank >=(x[g].first-x[i].first)*1.0/Davg )
               {
                 tank -= (x[g].first-x[i].first)*1.0/Davg;
               }
             else
             {
                 cost += ((x[g].first-x[i].first)*1.0/Davg - tank)*x[i].second ;
                 tank = 0;
             }


                    q = g;
                  //  cout<<"now find cheaper from: "<<i<<"to: "<<q<<endl;
//cout <<"cost = "<<cost <<endl;
               }
               if(p == 0 && g != i)//找最便宜的,加满
               {
                   if(Distance - where > Cmax*Davg)
             {
                   cost += (Cmax-tank)*(x[i].second);
                   tank = Cmax-(x[g].first-x[i].first)*1.0/Davg;
                   q = g;
             }
             else
             {
                  if(tank >=(Distance - where)*1.0/Davg )
                 {
                   ;
                 }
             else{
                cost += ((Distance - where)*1.0/Davg-tank)*(x[i].second);
                 }
                      cout<<setprecision(2)<<cost<<endl;
                      break;

             }


                   //cout<<"now find expensive but cheap from: "<<i<<"to: "<<q<<endl;
               // cout <<"cost = "<<cost <<endl;
               }
               if(p == 0 && g == i)
               {
                   if(Distance - where <= Cmax*Davg)
                   {
                      //cout<<"now:"<<i<<endl;
                  if(tank >=(Distance - where)*1.0/Davg )
                 {
                   ;
                 }
             else{
                cost += ((Distance - where)*1.0/Davg-tank)*(x[i].second);
                 }

                      cout<<setprecision(2)<<cost<<endl;
                      break;
                   }
                   else
                   {
                     //  cout<<"now:"<<i<<endl;
                       where += Cmax*Davg;
                       cout<<setprecision(2)<<"The maximum travel distance = "<<where<<endl;
                       break;
                   }
               }
            }
        }






	return 0;
}

