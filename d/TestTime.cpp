#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <queue>
#include<windows.h>
#include"ads P3 Cversion(1).cpp"
#include "store.cpp"
#include <sstream>
#include <windows.h>
#include <memory.h>

#include <fstream>

using namespace std;


    typedef pair<int,int> P; //first是最短距离，second是顶点的编号
    int Distance[MAXV];
    UListGraph G = new Node[MAX_VERTEX];
    priority_queue<P,vector<P>,greater<P> > que;

const char *  FILE_RD = "F:\\USA-road-d.NY.gr";//原文件

const size_t WR_SIZE = 1024*1024*10;//每次读写的大小,此处为10M
void hugefile_rw()
{
    ifstream infile(FILE_RD);

    string s;int q = 0;
    while (getline(infile, s))
    {
        q++;
       if(s[0] != 'a')
         continue;
       else
        {
          char * x= new char[strlen(s.c_str())+1];
          strcpy(x, s.c_str());

          char *p;
          const char *d = " ";
          p = strtok(x,d);
          string o[4];
          int i =0;
           while(p)
         {
           o[i] = p;
           p=strtok(NULL,d);
           i++;
         }delete []x;
          int a = atoi(o[1].c_str());
          int b = atoi(o[2].c_str());
          int c = atoi(o[3].c_str());
          UListGraph_create(G,a,b,c);
          //cout<<a<<' '<<b<<' '<<c<<endl;
        }
    }

}
void prioTest(int i){



    for(int i = 0; i<MAXV; i++)
     {
         Distance[i] = infinity;
     }

    Distance[0] = 0;
    que.push(P(i,0)); //把起点推入队列
    while(!que.empty())
    {
        P p = que.top();
        que.pop();
        int v = p.second; //顶点的编号n
        if (Distance[v] < p.first) continue;
        for(int i = 0; i < G[v].indexList.size(); i++)
        {
            int e = (G[v].indexList)[i].second;
             cout<<i<<endl;


            if (Distance[i] > Distance[v] + e)
            {

                Distance[i] = Distance[v] + e;

             //   try
              //  {
              //      cout<<"size: "<<que.size()<<endl;
                  que.push(P(Distance[i],i));

              //  }
              /*  catch(std::range_error)
                {
                  cout<<"fucked"<<endl;
                }
                catch(std::bad_alloc)
                {
                  cout<<"fucked"<<endl;
                }
                */
            }
        }
    }


}
void FibTest(int i) {
	FibonacciHeap *que = NULL;

	que = Fibonacci_insert(que,0,i);

	for (int i = 0; i<MAXV; i++)
	{
		Distance[i] = infinity;
	}

	Distance[0] = 0;




	while (que->n) {

            int v = que->min->pos; //顶点的编号n
		int ads = que->min->num;
        Fibonacci_deletemin(que);

//             cout<<"num??: "<<Node->num<<endl;

		if (Distance[v] < ads) continue;
		for (int i = 0; i < G[v].indexList.size(); i++) {
			int e = (G[v].indexList)[i].second;

			if (Distance[i] > Distance[v] + e)
			{
				Distance[i] = Distance[v] + e;
//				Fibonacci_Node *Node = (Fibonacci_Node*)malloc(sizeof(Fibonacci_Node));
//				Node->num = Distance[i];
//				Node->pos = i;
//				Node->child = Node->left = Node->right = Node->p = NULL;
//				Node->degree = 0;

				que = Fibonacci_insert(que, Distance[i],i);



			}
		}
	}

}
void BioTest(int i)
{

    Binary_Node *a[1];
    a[1] = new Binary_Node;
    (*a[1]).num = 0;
    (*a[1]).pos = i;
    BinaryHeap* que = Binary_build(1,a);

    for(int i = 0; i<MAXV; i++)
     {
         Distance[i] = infinity;
     }

    Distance[0] = 0;



    while(0 != (*que).size)
    {
        Pbn p = Binary_FindMin(que);
        Binary_DeleteMin(que);

        int v = (*p).pos; //顶点的编号n
        int q = p->num;
        delete p;
        if (Distance[v] < q) continue;

        for(int i = 0; i < G[v].indexList.size(); i++)
        {
            int e = (G[v].indexList)[i].second;

            if (Distance[i] > Distance[v] + e)
            {
                Distance[i] = Distance[v] + e;

            //    try
            //    {
                    //cout<<"size: "<<(*que).size<<endl;
                Pbn p = new struct Binary_Node;
                p->num = Distance[i];
                p->pos = i;
                Binary_Insert(que,p);
            //    }
            /*    catch(std::range_error)
                {
                  cout<<"fucked"<<endl;
                }
                catch(std::bad_alloc)
                {
                  cout<<"fucked"<<endl;
                }
                */
            }
        }
    }



}
void PreOrderTraverse(Plp T)
{
   if(T)//如果当前节点不为空
   {
      cout<<T->num<<' ';   //先输出当前节点的值
      PreOrderTraverse(T->Left); //再调用自己到左节点
      PreOrderTraverse(T->Right);//最后到右节点
   }

   return;
}
void LefTest(int i)
{
    int a = 0;

    LeftistHeap *que = (LeftistHeap*)malloc(sizeof(LeftistHeap));
    que->num = 0;
    que->pos = i;
    que->Left = NULL;
    que->Right = NULL;
    que->Npl = 0;


    for(int i = 0; i<MAXV; i++)
     {
         Distance[i] = infinity;
     }

    Distance[0] = 0;


	int flag;
    while(que)
    {
 	    a++;
        int v = que->pos; //顶点的编号n
		int ads = que->num;
        if(a >= 6000)      PreOrderTraverse(que);

        que = Leftist_DeleteMin(que);
        if (Distance[v] < ads) continue;
        for(int i = 0; i < G[v].indexList.size(); i++)
        {
            int e = (G[v].indexList)[i].second;

            if (Distance[i] > Distance[v] + e)
            {
                Distance[i] = Distance[v] + e;

            //    try
            //    {
                    //cout<<"size: "<<(*que).size<<endl;
                Plp p =  (LeftistHeap*)malloc(sizeof(LeftistHeap));
                p->num = Distance[i];
                p->pos = i;
                p->Left = NULL;
                p->Right = NULL;
                p->Npl = 0;
             //   if(que != NULL)
                que = Leftist_insert(que,i,Distance[i]);
             //   cout<<"insert_ok"<<endl
             //   else
             //   que = p;
//                 if(que != NULL) cout<<1<<endl;
//                cout<<"que = ?: "<<(que == NULL)<<' '<<que->num<<' ' <<que->pos<<endl;
            //    }
            /*    catch(std::range_error)
                {
                  cout<<"fucked"<<endl;
                }
                catch(std::bad_alloc)
                {
                  cout<<"fucked"<<endl;
                }*/
            }
        }
    }


////
//    for(int i = 0; i<MAXV; i++) cout<<i<<' '<<Distance[i]<<endl;



}

void outofMem()
{
    std::cerr<< "Bad Bad Bad\n";
    std::abort();
}
int main()
{
    srand(time(0));
    std::set_new_handler(outofMem);

    for (int i = 0; i < MAX_VERTEX; ++i)  //填充顶点数组
    {
       G[i].data = -1;
    }

/****************************************************/
hugefile_rw();
double start,end;
int max = 260000,min = 1;
/****************************************************/
start = GetTickCount();
int a[4001];
int n = 4000;
for (int j=0; j<= n; j++)
    a[j] = rand()%(max-min+1) +min;
//
//start = GetTickCount();
//for (int i=0; i<= n; i++)
//FibTest(a[i]);
//end = GetTickCount();
//cout << "斐波那契堆：GetTickCount:" << end - start << endl;
//**************************************************
//start = GetTickCount();
//for (int i=0; i<= n; i++)
//LefTest(a[i]);
//end = GetTickCount();
//cout << "左式堆：GetTickCount:" << end-start << endl;
///****************************************************/
for (int i=0; i<= n; i++)
prioTest(a[i]);
end = GetTickCount();
cout << "标准堆：GetTickCount:" << end-start << endl;
///****************************************************/
//start = GetTickCount();
//for (int i=0; i<= n; i++){
//BioTest(a[i]);}
//end = GetTickCount();
//cout << "二项堆：GetTickCount:" << end-start << endl;
///****************************************************/


    return 0;
}
