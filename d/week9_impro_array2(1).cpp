#include <memory.h>
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <random>
#include <ctime>
#include <algorithm>
#include <limits.h>

#include "week9_project(3).cpp"

using namespace std;
void test (int n)
{
/***************测试数据初始化************/
    int *w = new int[n+1];
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i=1; i<=n; i++)
    {
// 均匀分布
//        std::uniform_int_distribution<> dis(1, 5);
//        w[i] = dis(gen);

// 正太分布
        std::normal_distribution<double> dis(10,10);
        std::lround(dis(rd));
        w[i] = pow(pow(dis(gen),2),0.5)+1;

// 泊松分布
//        std::poisson_distribution<int> dis(5);
//        w[i] = dis(gen)+1;
        //cout<<w[i]<<endl;
    }


    /*********************测试数组法***************************/
	double start,end;
    start = GetTickCount();
    HuffmanTree HT = (HuffmanTree)malloc(sizeof(HTNode)*n*2);
    //建队
    sort(w+1,w+n+1,cmp1);
    //建树+计算
    cout<< HuffmanCoding(HT,w+1,n) <<std::endl;
    end = GetTickCount();
    cout << "数组法：GetTickCount:" << end-start << endl;
    free(HT);

    /******************测试左式堆******************/
    int N = n,weight[64],flag,wpl2,loop,casenum;
    int wpl1;
    HuffNode *tmp;
    Leftist *tmp_L;
	Leftist **H1;
	casenum = 0;
	H1 = (Leftist**)malloc((N * 2) * sizeof(Leftist*));

	for(int i = 0;i < N;i++)
	{
		tmp = (HuffNode*)malloc(sizeof(HuffNode));
		tmp->weight = w[i + 1];
		tmp->Left = tmp->Right = NULL;
		H1[i] = (Leftist*)malloc(sizeof(Leftist));
		H1[i]->node = tmp;
		H1[i]->Left = H1[i]->Right = NULL;
		H1[i]->Npl = 0;
	}
	start = GetTickCount();
	H1[N] = BuildLeftist(H1,N);
	tmp_L = Leftist_Huff(H1[N],N);
	tmp = tmp_L->node;
	wpl1 = Get_Wpl(tmp,0);
	end = GetTickCount();

	printf("%d\n",wpl1);
    cout << "左式堆法：GetTickCount:" << end-start << endl;
    HuffTree_Delete(tmp);
    free(H1);
    /*******************测试小顶堆***************/
    start = GetTickCount();

	char ch,s[64];

	Heap *H;
	casenum = 0;
	H = (Heap*)malloc(sizeof(Heap));
	H->size = 0;
	H->nodes = (HuffNode**)malloc(N*sizeof(HuffNode**));
	H->nodes[0] = (HuffNode*)malloc(sizeof(HuffNode));
	H->nodes[0]->weight = 0;
	H->nodes[0]->Left = H->nodes[0]->Right = NULL;
	for(int i = 1;i <= N;i++)
	{
		tmp = (HuffNode*)malloc(sizeof(HuffNode));
		tmp->weight = w[i];
		tmp->Left = tmp->Right = NULL;
		H->nodes[i] = tmp;
	}
	H->size = N;
	BuildHeap(H,N);
	tmp = BuildTree(H);
	wpl1 = Get_Wpl(tmp,0);
    printf("%d\n",wpl1);
	end = GetTickCount();
    cout << "小顶堆法：GetTickCount:" << end-start << endl;
	HuffTree_Delete(tmp);
	free(H);
/************************************/
/************************************************/



}

int main()
{
	int n;
	int my[11] = {0,1000,5000,25000,100000,500000,1000000,2000000,3000000,5000000,1000000};
    test(500000);
}
