#include <iostream>
#include <string.h>
#define MAXNUM 10
using namespace std;

void GoCheckAndUpdate(int TimeUsed, int ProblemSolved);
void dfs(int TimeUsed, int QuestionSolved, int WorkingProblem,int Accumulate);
static int LimitedTime = 0;
static int LimitedProblem = 0;
static int ReadTime = 0;

static string ProblemName[MAXNUM];
static int ProblemSolveTime[MAXNUM] = {0};
static int ProblemDebugTime[MAXNUM] = {0};

static int RoadWentAlready[MAXNUM] = {0};
static int CurrentProblemTime = 0;
static int CurrentProblemNumber = 0;
static int CurrentProblemId[MAXNUM] = {0};

static int FinalProblemTime = 0;
static int FinalProblemNumber = 0;
static int FinalProblemId[MAXNUM] = {0};

int main()
{
/*********************************/
    cin>>LimitedTime;
    while(LimitedTime != -1)
    {
     cin>>LimitedProblem>>ReadTime;
     for(int i=0; i<LimitedProblem; i++)
     {
         cin>>ProblemName[i]>>ProblemSolveTime[i]>>ProblemDebugTime[i];
     }
     for(int i=0; i<LimitedProblem; i++)
     {
         FinalProblemId[i] = 0;
     }
     FinalProblemNumber = FinalProblemTime = 0;
/*********************************/
//for(int i=0; i<LimitedProblem; i++)
//     {
//         cout<<ProblemName[i]<<ProblemSolveTime[i]<<ProblemDebugTime[i];
//     }
      for(int i=0; i<LimitedProblem; i++)
      {
//        cout<<"Begin with "<<i<<endl;
        RoadWentAlready[i] = 1;
        dfs(ReadTime,0,i,0);
        RoadWentAlready[i] = 0;
//        cout<<'\n';
      }
      cout<<"Total Time = "<<FinalProblemTime<<endl;

      for(int i=0; i<FinalProblemNumber; i++)
      {
        cout<<ProblemName[FinalProblemId[i]]<<endl;
      }

     cin>>LimitedTime;
    }




    return 0;
}
void GoCheckAndUpdate(int TimeUsed, int ProblemSolved)
{
//    cout<<"********************************out!!!!!****************"<<endl;

    if(ProblemSolved < FinalProblemNumber) return;
    if(ProblemSolved == FinalProblemNumber && TimeUsed >= FinalProblemTime) return;

    for(int i=0; i<ProblemSolved; i++)
    {
        FinalProblemId[i] = CurrentProblemId[i];
    }
    FinalProblemNumber = ProblemSolved;
    FinalProblemTime = TimeUsed;
//    cout<<FinalProblemNumber<<FinalProblemTime<<endl;

    return;
}
void dfs(int TimeUsed, int QuestionSolved, int WorkingProblem, int Accumulate)
{
    int ThisSubmitTime = TimeUsed + ProblemSolveTime[WorkingProblem];
    int ThisDebugChance = (ThisSubmitTime)/60;
    if(ThisSubmitTime % 60 == 0) ThisDebugChance--;
    int ThisACTime = ThisDebugChance * (ProblemDebugTime[WorkingProblem]) + ThisSubmitTime;
    int ThisTotalTime = ThisACTime + Accumulate +ThisDebugChance*20;
//cout<<"ThisSubmit"<<ThisSubmitTime<<endl
//        <<"Debug: "<<ThisDebugChance<<endl
//        <<"ThisAcTime: "<<ThisACTime<<endl
//        <<"TimeUsed: "<<TimeUsed<<endl
//        <<"ThisTotalTime: "<<ThisTotalTime<<endl
//        <<"ThisNumber"<<QuestionSolved<<endl;
    if(ThisACTime > LimitedTime * 60) {GoCheckAndUpdate(Accumulate,QuestionSolved);return;}

    if(QuestionSolved + 1 == LimitedProblem ) {CurrentProblemId[QuestionSolved] = WorkingProblem;GoCheckAndUpdate(ThisTotalTime,QuestionSolved+1);return;}

CurrentProblemId[QuestionSolved] = WorkingProblem;
    int i = 0;
    while(i < LimitedProblem)
    {
        if(!RoadWentAlready[i])
        {
//            cout<< "From "<<WorkingProblem<<" Going this way: "<<i<<endl;
//            cout<<'\n';
            RoadWentAlready[i] = 1;
            dfs(ThisACTime,QuestionSolved+1,i,ThisTotalTime);
            RoadWentAlready[i] = 0;
        }i++;
    }
    return;
}

