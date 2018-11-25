    #include <iostream>
    #include <string.h>
    #define MAXP 10
    using namespace std;

    int H=0,N,T0;
    int T[MAXP],D[MAXP];//T:��Ŀ���ʱ�� D:��Ŀdebugʱ��
    string problem_name[MAXP];
    int fin_pro_No[MAXP];//��˳���¼��ɵ���Ŀ���
    bool pro_state[MAXP];//��¼��Ŀ������:true������� false����δ���
    int final_num;
    int final_pro_No[MAXP];
    int final_totalTime;

    void update_strategy(int num, int totalTime){
        //���Ʋ��Ե�ѡ��
        if (num < final_num) return;//����ѡ������������Ĳ���
        if (num == final_num && totalTime>=final_totalTime) return;//��������һ����ѡ��ʱ���ٵ�
        //���²���
        final_num = num;
        final_totalTime = totalTime;
        for (int i=0; i<num; i++) {
            final_pro_No[i]=fin_pro_No[i];
        }
    }

    //num:��ɵ�����
    //usedTime:�õ���ʱ��
    //totalTime:�ɼ�ʱ��
    void dfs(int num, int usedTime, int totalTime){

        int first_submit_time = usedTime + T[fin_pro_No[num]];
        int debug_times = (first_submit_time - 1)/60;
        int next_usedTime = first_submit_time + debug_times * D[fin_pro_No[num]];
        int next_totalTime = totalTime + next_usedTime + debug_times*20;

        if (next_usedTime <= H*60) {//�涨ʱ�����ܳɹ��ύ����
            num ++;
            if (num < N) {//����δ��ɵ���
                for (int i =0; i<N; i++) {//����ÿ�����ߵĲ�·
                    if (!pro_state[i]) {
                        pro_state[i]=true;
                        fin_pro_No[num]=i;
                        dfs(num, next_usedTime, next_totalTime);
                        pro_state[i]=false;//===>��֦
                        //����num--��num���βΣ�ÿ���num����һ��
                    }
                }
            }
            else update_strategy(num, next_totalTime);//����������ҵ�һ�ֲ��ԣ��ص���һ��===>
        }
        else update_strategy(num, totalTime);//��ʱ���ҵ�һ�ֲ��ԣ��ص���һ��===>
    }

    int main(){
        cin >> H;
        while (H>0) {
            cin >> N >> T0;
            for (int i=0; i<N; i++) {
                cin >> problem_name[i] >> T[i] >> D[i];
            }
            //������ʼ��
            final_num = 0;
            final_totalTime = ~(1 << 31);
            memset(final_pro_No,0,sizeof(final_pro_No));
            memset(fin_pro_No, 0, sizeof(fin_pro_No));
            memset(pro_state, false, sizeof(pro_state));

            for (int i=0; i<N; i++) {
                pro_state[i]=true;
                fin_pro_No[0]=i;
                dfs(0, T0, 0);//�õ���ʱ��Ϊ����ʱ�䣬�ɼ�ʱ��Ϊ0
                pro_state[i]=false;
            }

            cout << "Total Time = " << final_totalTime << endl;
            for (int i=0; i<final_num; i++) {
                cout << problem_name[final_pro_No[i]] << endl;
            }

            cin >> H;
        }

        return 0;
    }
