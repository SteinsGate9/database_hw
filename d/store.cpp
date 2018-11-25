#define MAXV 270000
#include<windows.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <queue>
#include<stdio.h>
#include<vector>
#include<iostream>
#define MAX_VERTEX 270000

 static int NUMMOD = 10000;
 static int infinity = 100000;



using namespace std;       //使用C++标准库中的vector来作为list，它实质就是一个顺序表


typedef int DataType;

typedef struct node
{
    DataType data;            //顶点数据
    vector<pair<int,int> > indexList;    //存储顶点邻接点索引的 表

}Node;


typedef Node* UListGraph;


/********************************/
void UListGraph_init(UListGraph*pGraph);
void UListGraph_create(UListGraph graph,int a,int b,int w);










void UListGraph_create(UListGraph graph,int a,int b, int w)
{

    if(-1 == graph[a].data)
    {
       graph[a].data = a;
    }
      (graph[a].indexList).push_back(pair<int,int>(b,w));


}


