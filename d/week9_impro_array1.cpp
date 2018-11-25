
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HuffNode
{
	int w;
	int lchild,rchild;
	int parent;
}HTNode;
typedef HTNode* HuffmanTree;


void HuffmanCoding(HuffmanTree &HT,int*w,int n)
{ if (n<=1) return;
int m=2*n-1;
HT=(HuffmanTree)malloc(sizeof(100000));
int i;
HuffmanTree p;
for(p=HT,i=1;i<=n;++i,++p,++w)
    {HTNode x ={*w,0,0,0};
     p[1] = x;}
     std::cout<<"1"<<std::endl;
for(;i<=m;++i,++p) *p={0,0,0,0};
 std::cout<<"1"<<std::endl;
int a=n-1;
int b=n;
int s1,s2;
for(i=n+1;i<=m;i++)
{ if(i==n+1) {s1=a;s2=b;}
else
{
 std::cout<<i<<std::endl;
if(HT[a-1].w<HT[b+1].w&&HT[a-2].w>=HT[b+1].w)
{s1=a-1;s2=b+1;a--;b++;}
if(HT[a-1].w>HT[b+1].w&&HT[b+2].w!=0&&HT[a-1].w>=HT[b+2].w)
{s1=b+1;s2=b+2;b=b+2;}
else{s1=a-2;s2=a-1;a=a-2;}
}
for(int q = 1; q<= m; q++)
    std::cout<<"µÚ"<<q<<"¸ö"<<HT[q].w<<std::endl;
HT[s1].parent=i;HT[s2].parent=i;
HT[i].lchild=s1;HT[i].rchild=s2;
HT[i].w=HT[s1].w+HT[s2].w;

}
}
int main()
{
    HuffmanTree HT = NULL;
    int w[11] = {8,7,5,4,2,0,0,0,0,0};
    HuffmanCoding(HT,w,5);
    return 0;

}
