#include <cstdio>
#include <cstring>
// configure
const int MAXN = 9;
const int MAXL = 20 + 1;
// global context
int H, N, t_0;
int T[MAXN], D[MAXN]; // solve times and debug times
char problem_name[MAXN][MAXL]; // names of problems
// global status
int problem_stack[MAXN]; // the finished problem stack
bool is_problem_in_stack[MAXN];
// final answer
int final_problem_order[MAXN];
int final_problem_finished;
int final_total_time;

void solution_merge(int finished, int total_time){
    if(finished < final_problem_finished) return;
    if(finished == final_problem_finished && total_time >= final_total_time) return;
    // better way: record the answer
    final_total_time = total_time;
    final_problem_finished = finished;
    for(int i = 0; i < finished; i++) final_problem_order[i] = problem_stack[i];
}

void dfs(int finished, int time_used, int total_time){
    // problem_stack[finished] is now working problem
    // problem_stack[0..., finished -1] is finished problem

    int first_submit_time = time_used + T[problem_stack[finished]];
    int debug_times = (first_submit_time - 1) / 60;
    int next_time_used = first_submit_time + debug_times * D[problem_stack[finished]];
    int next_total_time = total_time + next_time_used + debug_times * 20;

    if(next_time_used <= H * 60) {
        finished ++;
        if(finished < N){
            // find all unfinished problem
            for(int i = 0; i < N; i++){
                if(!is_problem_in_stack[i]){
                    is_problem_in_stack[i] = true; // push
                    problem_stack[finished] = i; // it cannot overflow
                    dfs(finished, next_time_used, next_total_time);
                    is_problem_in_stack[i] = false; // pop
                }
            }
        } else {
            // all problem has been finished
            solution_merge(finished, next_total_time);
        }
    } else {
        // time up
        solution_merge(finished, total_time);
    }
}

int main(){
    while(scanf("%d%d%d", &H, &N, &t_0) == 3){
        if(H < 0) break;
        for(int i = 0; i < N; i++){
            scanf("%s%d%d", problem_name[i], T + i, D + i);
        }

        // initialize the final answer
        final_total_time = ~(1 << 31);
        final_problem_finished = 0;
        memset(final_problem_order, 0, sizeof(final_problem_order));

        // state initialize
        memset(is_problem_in_stack, 0, sizeof(is_problem_in_stack));

        for(int i = 0; i < N; i++){
            is_problem_in_stack[i] = true; // push
            problem_stack[0] = i; // push the first problem
            dfs(0, t_0, 0); // start search
            is_problem_in_stack[i] = false; // pop
        }
        // print answer
        printf("Total Time = %d\n", final_total_time);
        for(int i = 0; i < final_problem_finished; i++)
            printf("%s\n", problem_name[final_problem_order[i]]);
    }
}
