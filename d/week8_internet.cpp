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
    float d;    //Ŀ�����
    int n;      //����վ����

    int cmp(const void* A,const void* B)
    {
        Gas* aa = (Gas*)A;
        Gas* bb = (Gas*)B;
        return aa->dis > bb->dis;
    }

    float findMin(int i,float range,int &target){       //Ѱ�ҿɴﷶΧ�ڣ���������ѡ������˵ģ�����������ѡ�������һ��
        float maxDis = gas[i].dis + range;
        float minPrice = INF;
        for(int j=i+1;j<n;j++){
            if(gas[j].dis <= maxDis && gas[j].dis < d){   //���ڿɴﷶΧ�ڣ������յ�ǰ
                if(gas[j].price <= minPrice){        //������ѡ������˵�
                    minPrice = gas[j].price;
                    target = j;
                    if(minPrice < gas[i].price)break;        //����������ѡ�������һ��
                }
            }else{      //������Χ
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
            if(minPrice == INF){        //�ɴﷶΧ��û�м���վ��
                if(gas[i].dis+maxPerDis >= d){           //�ڵ��¼���վ�������͵��յ�
                    sum += ((d-gas[i].dis)/avg - left)*gas[i].price;
                    cout<< fixed << showpoint << setprecision(2)<<sum<<endl;
                }else{              //Impossible -> ������ �ܵ�������
                    cout<<"The maximum travel distance = "<<setiosflags(ios::fixed)<<setprecision(2)<<float(gas[i].dis+maxPerDis)<<endl;
                }
                break;
            }else if(minPrice <= gas[i].price){      //�ɴﷶΧ���и����� ����վ -> �Ӿ������ٵ���,�ܵ���һ������վ����
                float needAmount = (gas[target].dis-gas[i].dis)/avg;
                if(needAmount <= left){      //Ŀǰ������ֱ�ӵ����¸�������վ��ֱ��ǰ��
                    left = left - needAmount;
                }else{                      //����ֱ�ӵ������һ��ǡ���ܵ�����
                    sum += (needAmount-left)*gas[i].price;
                    left = 0;
                }
                i = target;
            }else{      //�ɴﷶΧֻ�м۸���ߵ�->������
                sum += (c-left)*gas[i].price;
                left = c - (gas[target].dis-gas[i].dis)/avg;
                i = target;
            }
        }
        system("PAUSE");
        return 0;
    }
