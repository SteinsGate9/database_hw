#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <random>

#define infinity 2147483647

//HuffNode structure
struct HuffNode
{
	long long int weight;
	HuffNode *Left,*Right;
};

//BinHeap structure
struct Heap
{
	HuffNode **nodes;
	int size;
};

//BinTree structure
struct BinNode
{
	int flag;
	BinNode *Left,*Right;
};

//free memory
void BinTree_Delete(BinNode *T);
void HuffTree_Delete(HuffNode *T);

//function for BinHeap
void BuildHeap(Heap *H, int N);
void Insert(Heap *H,HuffNode *node);
HuffNode *DeleteMin(Heap *H);
void PercDown(Heap *H, int i);

//build Huffman Tree with BinHeap
HuffNode *BuildTree(Heap *H);

//for calculating wpl
int Get_Wpl(HuffNode *H,int depth);

//check prefix codes
int check(BinNode *T,char *s);

//for build heap
void PercDown(Heap *H, int i)
{
    int Tmp;
    int child;
    for (Tmp=((H->nodes[i])->weight); 2*i <= H->size; i= child)
    {
        child= i*2;
        if (child!=H->size && H->nodes[child+1]->weight < H->nodes[child]->weight )
        {
            child++;
        }
        if (Tmp > H->nodes[child]->weight)
        {
            H->nodes[i]->weight = H->nodes[child]->weight;
        }
        else
            break;
    }
    H->nodes[i]->weight=Tmp;
}

//build tree by percolate down
void BuildHeap(Heap *H,int N)
{
    int i;
    for (i=H->size/2; i>0; i--)
    {
        PercDown(H, i);
    }
}

//free memory recursively
void BinTree_Delete(BinNode *T)
{
	if(!T->Left && !T->Right)
	{
		free(T);
	}
	else
	{
		if(T->Left) BinTree_Delete(T->Left);
		if(T->Right) BinTree_Delete(T->Right);
	}
}

//free memory recursively
void HuffTree_Delete(HuffNode *H)
{
	if(!H->Left && !H->Right)
	{
		free(H);
	}
	else
	{
		if(H->Left) HuffTree_Delete(H->Left);
		if(H->Right) HuffTree_Delete(H->Right);
	}
}

//calculate wpl recursively
int Get_Wpl(HuffNode *H,int depth)
{
	if(H->Left||H->Right) return Get_Wpl(H->Left,depth + 1) + Get_Wpl(H->Right,depth + 1);
	else return depth * H->weight;
}

void Insert(Heap *H,HuffNode *node)
{
	int i;
	for(i = ++H->size;H->nodes[i / 2]->weight > node->weight;i/=2)
	{
		H->nodes[i] = H->nodes[i / 2];
	}
	H->nodes[i] = node;
}

HuffNode *DeleteMin(Heap *H)
{
	int i,child;
	HuffNode *Min,*Last;
	Min = H->nodes[1];
	Last = H->nodes[H->size--];
	for(i = 1;i * 2 <= H->size;i = child)
	{
		child = i * 2;
		if(child != H->size && H->nodes[child + 1]->weight < H->nodes[child]->weight) child++;
		if(Last->weight > H->nodes[child]->weight) H->nodes[i] = H->nodes[child];
		else break;
	}
	H->nodes[i] = Last;
	return Min;
}

//for checking prefix codes
int check(BinNode *T,char *s)
{
	for(int i = 0;i < strlen(s);i++)
	{
		//if flag = 1, there is an element in this node, which means some string is the prefix code of s
		if(T->flag == 1)
		{
			return 1;
		}
		//if the i-th bit is 0, then go to left branch
		if(s[i] == '0')
		{
			//if T doesn't have left child, generate a new node
			if(T->Left == NULL)
			{
				BinNode *tmp = (BinNode*)malloc(sizeof(BinNode));
				tmp->Left = tmp->Right = NULL;
				tmp->flag = 0;
				T->Left = tmp;
			}
			T = T->Left;
		}
		//if the i-th bit is 1, then go to left branch
		else
		{
			//if T doesn't have left child, generate a new node
			if(T->Right == NULL)
			{
				BinNode *tmp = (BinNode*)malloc(sizeof(BinNode));
				tmp->Left = tmp->Right = NULL;
				tmp->flag = 0;
				T->Right = tmp;
			}
			T = T->Right;
		}
	}
	//if flag = 1, there is an element in this node, which means some string is the same as s
	//if T has left or right child, s is the prefix node of some string
	if(T->flag || T->Left || T->Right)
	{
		return 1;
	}
	T->flag = 1;
	return 0;
}

//leftist heap structure
struct Leftist
{
	HuffNode *node;
	int Npl;
	Leftist *Left,*Right;
};

//function for heap
Leftist *BuildLeftist(Leftist **H,int n);
Leftist *merge(Leftist *A, Leftist *B);
Leftist *merge1(Leftist *A, Leftist *B);
Leftist *DeleteMin(Leftist *A);

//build Huffman Tree with leftist heap
Leftist *Leftist_Huff(Leftist *A,int n);

//free memory
void LeftistDelete(Leftist *T);

//for merge 4 leftist heap
Leftist *merge4(Leftist **H,int flag);

//build leftist with queue, whose time complexity is O(n)
Leftist *BuildLeftist(Leftist **H,int n)
{
	int front = 0,rear = n - 1;
	Leftist **tmp;
	tmp = (Leftist**)malloc(2*n*sizeof(Leftist*));
	for(int i = 0;i < n;i++)
	{
		tmp[i] = H[i];
	}
	Leftist *A,*B;
	while(rear!=front)
	{
		A = tmp[front++];
		B = tmp[front++];
		A = merge(A,B);
		tmp[++rear] = A;
	}
	return A;
}

Leftist *merge(Leftist *A, Leftist *B)
{
	if(A == NULL) return B;
	if(B == NULL) return A;
	if(A->node->weight < B->node->weight) return merge1(A,B);
	else return merge1(B,A);
}
Leftist *merge1(Leftist *A, Leftist *B)
{
	Leftist *tmp;
	if(A->Left == NULL) A->Left = B;
	else
	{
		A->Right = merge(A->Right,B);
		if(A->Left->Npl < A->Right->Npl)
		{
			tmp = A->Right;
			A->Right = A->Left;
			A->Left = tmp;
		}
		A->Npl = A->Right->Npl + 1;
	}
	return A;
}
Leftist *Deletemin(Leftist *A)
{
	if(A == NULL)
	{
		return NULL;
	}
	Leftist *B = A->Left;
	Leftist *C = A->Right;
	free(A);
	return merge(B,C);
}

//build Huffman Tree with leftist heap
Leftist *Leftist_Huff(Leftist *A,int N)
{
	HuffNode *tmp,*tmp1,*tmp2;
	Leftist *tmp_l[4],*temp;//tmp_l[0]:new node tmp_l[1]¡¢tmp_l[2]:the children of the second smallest node tmp_l[3]:the sibling of the second smallest node
	for(int cnt = 1;cnt < N;cnt++)
	{
		tmp = (HuffNode*)malloc(sizeof(HuffNode));//new node
		tmp1 = A->node;
		//for finding the second smallest node
		if(A->Left && (!A->Right ||(A->Left->node->weight < A->Right->node->weight)))
		{
			tmp2 = A->Left->node;
			tmp_l[1] = A->Left->Left;
			tmp_l[2] = A->Left->Right;
			tmp_l[3] = A->Right;
			free(A->Left);//delete the second smallest node
			free(A);//delete the smallest node
		}
		else
		{
			tmp2 = A->Right->node;
			tmp_l[1] = A->Right->Left;
			tmp_l[2] = A->Right->Right;
			tmp_l[3] = A->Left;
			free(A->Right);//delete the second smallest node
			free(A);//delete the smallest node
		}
		//attach the two nodes to the new node
		tmp->Left = tmp1;
		tmp->Right = tmp2;
		tmp->weight = tmp1->weight + tmp2->weight;
		tmp_l[0] = (Leftist*)malloc(sizeof(Leftist));
		tmp_l[0]->Left = tmp_l[0]->Right = NULL;
		tmp_l[0]->node = tmp;
		tmp_l[0]->Npl = 0;

		//find min_node of tmp_l
		Leftist *min = tmp_l[0];
		int min_item = 0;
		int min_weight;
		if(tmp_l[0])  min_weight = tmp_l[0]->node->weight;
		else min_weight = infinity;//if NULL,set infinity
		for(int i = 1;i < 4;i++)
		{
			if((tmp_l[i] && min_weight > tmp_l[i]->node->weight))
			{
				min_weight = tmp_l[i]->node->weight;
				min_item = i;
			}
		}
		A = merge4(tmp_l,min_item);
	}
	return A;
}

//free memory recursively
void LeftistDelete(Leftist *T)
{
	if(!T) return;
	if(!T->Left && !T->Right)
	{
		if(T->node) delete(T->node);
		delete(T);
	}
	else
	{
		if(T->Left) LeftistDelete(T->Left);
		if(T->Right) LeftistDelete(T->Right);
	}
}

//merge four heaps recursively
Leftist *merge4(Leftist **H,int flag)
{
	//if three nodes are NULL in array H, return the non_null one
	int judge = 0;
	for(int i = 0;i < 4;i++)
	{
		if(i != flag && !H[i]) judge++;
	}
	if(judge == 3) return H[flag];

	Leftist *head = H[flag],*temp,*min;
	int min_item;
	int min_weight;
	//update the array
	H[flag] = head->Right;

	//find min_node of H
	min = H[0];
	min_item = 0;
	if(H[0])  min_weight = H[0]->node->weight;
	else min_weight = infinity;
	for(int i = 1;i < 4;i++)
	{
		if((H[i] && min_weight > H[i]->node->weight))
		{
			min_weight = H[i]->node->weight;
			min_item = i;
		}
	}
	head->Right = merge4(H,min_item);

	//keep the property of the leftist heap
	if(!head->Left||head->Left->Npl < head->Right->Npl)
	{
		temp = head->Left;
		head->Left = head->Right;
		head->Right = temp;
	}
	//update the npl
	if (head->Right) head->Npl = head->Right->Npl + 1;
	else head->Npl = 0;
	return head;
}

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
long long int Get_Wpl(HTNode H,HuffmanTree HT,int depth)
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
	return Get_Wpl(HT[m],HT,0);


}
