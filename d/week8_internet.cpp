    #include <iostream>
    #include <fstream>
    #include <iomanip>
    using namespace std;

    ifstream fin("in.txt");
    #define cin fin


    struct Gas{
        float price;
        float dis;
    }gas[500];

    const int INF = 0x7fffffff;
    float d;    //目标距离
    int n;      //加油站个数

    int cmp(const void* A,const void* B)
    {
        Gas* aa = (Gas*)A;
        Gas* bb = (Gas*)B;
        return aa->dis > bb->dis;
    }

    float findMin(int i,float range,int &target){       //寻找可达范围内，若更贵则选择最便宜的；若更便宜则选择最近的一个
        float maxDis = gas[i].dis + range;
        float minPrice = INF;
        for(int j=i+1;j<n;j++){
            if(gas[j].dis <= maxDis && gas[j].dis < d){   //既在可达范围内，又在终点前
                if(gas[j].price <= minPrice){        //更贵则选择最便宜的
                    minPrice = gas[j].price;
                    target = j;
                    if(minPrice < gas[i].price)break;        //若更便宜则选择最近的一个
                }
            }else{      //超出范围
                break;
            }
        }
        return minPrice;
    }

    int main()
    {
        float c,avg;
        cin>>c>>d>>avg>>n;
        int i;
        for(i=0;i<n;i++){
            cin>>gas[i].price>>gas[i].dis;
        }
        qsort(gas,n,sizeof(Gas),cmp);

        if(n == 0 || gas[0].dis != 0){
            cout<<"The maximum travel distance = 0.00"<<endl;
            return 0;
        }
        float sum = 0.0;
        float left = 0.0;
        float maxPerDis = c*avg;
        int target;
        i=0;
        while(1)
        {
            float minPrice = findMin(i,maxPerDis,target);
            if(minPrice == INF){        //可达范围内没有加油站，
                if(gas[i].dis+maxPerDis >= d){           //在当下加油站加适量油到终点
                    sum += ((d-gas[i].dis)/avg - left)*gas[i].price;
                    cout<< fixed << showpoint << setprecision(2)<<sum<<endl;
                }else{              //Impossible -> 加满油 能到哪算哪
                    cout<<"The maximum travel distance = "<<setiosflags(ios::fixed)<<setprecision(2)<<float(gas[i].dis+maxPerDis)<<endl;
                }
                break;
            }else if(minPrice <= gas[i].price){      //可达范围内有更便宜 加油站 -> 加尽可能少的油,能到下一个便宜站即可
                float needAmount = (gas[target].dis-gas[i].dis)/avg;
                if(needAmount <= left){      //目前油量够直接到达下个更便宜站，直接前往
                    left = left - needAmount;
                }else{                      //不够直接到，则加一点恰好能到即可
                    sum += (needAmount-left)*gas[i].price;
                    left = 0;
                }
                i = target;
            }else{      //可达范围只有价格更高的->加满油
                sum += (c-left)*gas[i].price;
                left = c - (gas[target].dis-gas[i].dis)/avg;
                i = target;
            }
        }
        system("PAUSE");
        return 0;
    }
