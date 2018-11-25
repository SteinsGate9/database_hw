    #include <iostream>
    #include <string.h>
    #define MAXP 10
    using namespace std;

    int H=0,N,T0;
    int T[MAXP],D[MAXP];//T:题目完成时间 D:题目debug时间
    string problem_name[MAXP];
    int fin_pro_No[MAXP];//按顺序记录完成的题目序号
    bool pro_state[MAXP];//记录题目完成情况:true该题完成 false该题未完成
    int final_num;
    int final_pro_No[MAXP];
    int final_totalTime;

    void update_strategy(int num, int totalTime){
        //控制策略的选择
        if (num < final_num) return;//优先选择做出题数多的策略
        if (num == final_num && totalTime>=final_totalTime) return;//做出题数一样，选择时间少的
        //更新策略
        final_num = num;
        final_totalTime = totalTime;
        for (int i=0; i<num; i++) {
            final_pro_No[i]=fin_pro_No[i];
        }
    }

    //num:完成的题数
    //usedTime:用掉的时间
    //totalTime:成绩时间
    void dfs(int num, int usedTime, int totalTime){

        int first_submit_time = usedTime + T[fin_pro_No[num]];
        int debug_times = (first_submit_time - 1)/60;
        int next_usedTime = first_submit_time + debug_times * D[fin_pro_No[num]];
        int next_totalTime = totalTime + next_usedTime + debug_times*20;

        if (next_usedTime <= H*60) {//规定时间内能成功提交本题
            num ++;
            if (num < N) {//还有未完成的题
                for (int i =0; i<N; i++) {//尝试每个可走的岔路
                    if (!pro_state[i]) {
                        pro_state[i]=true;
                        fin_pro_No[num]=i;
                        dfs(num, next_usedTime, next_totalTime);
                        pro_state[i]=false;//===>剪枝
                        //不用num--，num是形参，每层的num都不一样
                    }
                }
            }
            else update_strategy(num, next_totalTime);//无题可做。找到一种策略，回到上一层===>
        }
        else update_strategy(num, totalTime);//超时。找到一种策略，回到上一层===>
    }

    int main(){
        cin >> H;
        while (H>0) {
            cin >> N >> T0;
            for (int i=0; i<N; i++) {
                cin >> problem_name[i] >> T[i] >> D[i];
            }
            //变量初始化
            final_num = 0;
            final_totalTime = ~(1 << 31);
            memset(final_pro_No,0,sizeof(final_pro_No));
            memset(fin_pro_No, 0, sizeof(fin_pro_No));
            memset(pro_state, false, sizeof(pro_state));

            for (int i=0; i<N; i++) {
                pro_state[i]=true;
                fin_pro_No[0]=i;
                dfs(0, T0, 0);//用掉的时间为读题时间，成绩时间为0
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
