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
#define infinity 100000000000000
#include "week9_project.cpp"

using namespace std;
int cmp1(int a,int b)
{
    return a>b;
}
typedef struct HuffNode1
{
	long long int w;
	int lchild,rchild;
	int parent;
	int hehe;
}HTNode;
typedef HTNode* HuffmanTree;
/****************算wpl*****************/
int Get_Wpl(HTNode H,HuffmanTree HT,int depth)
{
	if(H.lchild != 0||H.rchild != 0) return Get_Wpl(HT[H.lchild],HT,depth + 1) + Get_Wpl(HT[H.rchild],HT,depth + 1);
	else return depth * H.w;
}
int  HuffmanCoding(HuffmanTree &HT,int*w,int n)
{
/****************初始化*****************/
if (n<=1) return -1;
int m=2*n-1;
int i;
HT[0] = {infinity,0,0,0};
HuffmanTree p = HT;
for(i=1;i<=n;++i){p[i] ={w[i-1],0,0,0};}
for(i=i;i<=m;++i) p[i]={infinity,0,0,0};
int a=n-1;
int b=n;
int s1,s2;
/****************算法*****************/

for(i=n+1;i<=m;i++)
{
    if(i==n+1) {s1=a;s2=b;a--;b++;}
    else
    {

        if(a!=0&&HT[a].w == HT[b].w || HT[a].w<HT[b].w&&HT[a-1].w>=HT[b].w ||   HT[a].w<HT[b+1].w&&HT[a].w>HT[b].w  )
        {
            s1 = a; s2 = b;a--;b++;
        }
        else if( HT[a].w<HT[b].w && HT[a-1].w<HT[b].w )
        {
            s1 = a; s2 = a-1; a-=2;
        }
        else if( HT[a].w>HT[b].w && HT[a].w>=HT[b+1].w )
        {
            s1 = b;s2 = b+1; b+=2;
        }
    }

    HT[s1].parent=i;HT[s2].parent=i;
    HT[i].lchild=s1;HT[i].rchild=s2;
    HT[i].w=HT[s1].w+HT[s2].w;

}

//    std::cout<<i<<std::endl;
//    for(int q = 1; q<= m; q++)
//    std::cout<<"第"<<q<<"个"<<HT[q].w<<std::endl;
 return Get_Wpl(HT[m],HT,0);


}
void test (int n)
{
    int *w = new int[n+1];
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i=1; i<=n; i++)
    {
        std::uniform_int_distribution<> dis(1, 1000);
        w[i] = dis(gen);
    }


 double start,end;
/************************************************/

    start = GetTickCount();
    HuffmanTree HT = (HuffmanTree)malloc(sizeof(HTNode)*n*2);
    cout<<"array good"<<endl;
    sort(w+1,w+n+1,cmp1);
    cout<< HuffmanCoding(HT,w+1,n) <<std::endl;
    end = GetTickCount();
    cout << "数组法：GetTickCount:" << end-start << endl;
    free(HT);

/************************************************/
    start = GetTickCount();
    int N = n,weight[64],flag,wpl1,wpl2,loop,casenum;
	char ch,s[64];
	HuffNode *tmp;
	Heap *H;
	BinNode *T;
		casenum = 0;
		H = (Heap*)malloc(sizeof(Heap));
		H->size = 0;
		H->nodes = (HuffNode**)malloc(N*sizeof(HuffNode**));
		H->nodes[0] = (HuffNode*)malloc(sizeof(HuffNode));
		H->nodes[0]->weight = 0;
		H->nodes[0]->Left = H->nodes[0]->Right = NULL;
		for(int i = 1;i <= N;i++)
		{
			//scanf(" %c%d",&ch,&weight[i]);
			tmp = (HuffNode*)malloc(sizeof(HuffNode));
			tmp->weight = w[i];
			tmp->Left = tmp->Right = NULL;
			H->nodes[i] = tmp;
		}
		cout<<"heap good"<<endl;
		H->size = N;
		BuildHeap(H,N);
		tmp = BuildTree(H);
		wpl1 = Get_Wpl(tmp,0);
        printf("%d\n",wpl1);
    end = GetTickCount();
    cout << "小顶堆法：GetTickCount:" << end-start << endl;

    for (int i = 1; i<= N; i++)
    {
        if(H->nodes[i] != NULL)
        free(H->nodes[i]);
    }
    free(H);
//
/************************************/
//	char ch,s[64];
//	HuffNode *tmp;
  start = GetTickCount();
	Leftist *tmp_L;
	//Heap *H;
	Leftist **H1;
//	BinNode *T;
//	while(1)
//	{
		casenum = 0;
//		scanf("%d",&N);
//		if(N == 0) break;
		H1 = (Leftist**)malloc((N * 2) * sizeof(Leftist*));
		cout<<"left good"<<endl;
		for(int i = 0;i < N;i++)
		{
		//	scanf(" %c%d",&ch,&weight[i]);
			tmp = (HuffNode*)malloc(sizeof(HuffNode));
			tmp->weight = w[i + 1];
			tmp->Left = tmp->Right = NULL;
			H1[i] = (Leftist*)malloc(sizeof(Leftist));
			H1[i]->node = tmp;
			H1[i]->Left = H1[i]->Right = NULL;
			H1[i]->Npl = 0;
		}
		cout<<"left good2"<<endl;
		H1[N] = BuildLeftist(H1,N);
		cout<<"left good2"<<endl;
	// printf("H[N] = %d\n",H1[N]->node->weight);
		tmp_L = Leftist_Huff(H1[N],N);
		tmp = tmp_L->node;
	//	printf("H[N] = %d\n",H[N]->node->weight);
		wpl1 = Get_Wpl(tmp,0);
		printf("%d\n",wpl1);
    end = GetTickCount();
    cout << "左式堆法：GetTickCount:" << end-start << endl;


//
//    for (int i=1; i<=n; i++)
//    {
//        cout<<i<<" "<<w[i]<<endl;
//    }
}

int main()
{
    test(5000000);
}
