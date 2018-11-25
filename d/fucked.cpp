#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <queue>
#include<windows.h>
#include"ads P3 Cversion(1).cpp"
#define MAXV 21000
using namespace std;
int main()
{
    Binary_Node *a[11];
    for (int i = 0; i<11 ;i++)
   {
    a[i] = new Binary_Node;
    (*a[i]).num = i;
    (*a[i]).pos = i;
   }
    BinaryHeap* que = Binary_build(10,a);
        for (int i=1; i<=que->size; i++)
         {
             cout<< "num"<<que->node[i]->num;
             cout<<" pos"<<que->node[i]->pos<<endl;
         }
     Pbn p = Binary_FindMin(que);
     Binary_DeleteMin(que);

        int v = (*p).pos; //¶¥µãµÄ±àºÅn
        cout<<"pop "<<v<<endl;
        cout<<" size = "<<(*que).size<<endl;
        cout<<" minlength = "<<(*p).num<<endl;
         p = Binary_FindMin(que);
          Binary_DeleteMin(que);
         for (int i=0; i<que->size; i++)
         {
             cout<< "num"<<que->node[i]->num;
             cout<<" pos"<<que->node[i]->pos<<endl;
         }


}
