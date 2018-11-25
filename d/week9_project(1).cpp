
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <random>
struct HuffNode
{
	int weight;
	HuffNode *Left,*Right;
};

struct Heap
{
	HuffNode **nodes;
	int size;
};

struct BinNode
{
	int flag;
	BinNode *Left,*Right;
};

void Insert(Heap *H,HuffNode *node);
HuffNode *DeleteMin(Heap *H);
HuffNode *BuildTree(Heap *H);
void BinTree_Delete(BinNode *T);
void HuffTree_Delete(HuffNode *T);
void BuildHeap(Heap *H, int N);

int Get_Wpl(HuffNode *H,int depth);
int check(BinNode *T,char *s);

int N;
char a[64];
int weight[64];

//int main()
//{
//	int N,weight[64],flag,wpl1,wpl2,loop,casenum;
//	char ch,s[64];
//	HuffNode *tmp;
//	Heap *H;
//	BinNode *T;
//	while(1)
//	{
//		casenum = 0;
//		scanf("%d",&N);
//		if(N == 0) break;
//		H = (Heap*)malloc(sizeof(Heap));
//		H->size = 0;
//		H->nodes = (HuffNode**)malloc((N * 2) * sizeof(HuffNode*));
//		H->nodes[0] = (HuffNode*)malloc(sizeof(HuffNode));
//		H->nodes[0]->weight = 0;
//		H->nodes[0]->Left = H->nodes[0]->Right = NULL;
//		for(int i = 1;i <= N;i++)
//		{
//			//scanf(" %c%d",&ch,&weight[i]);
//			tmp = (HuffNode*)malloc(sizeof(HuffNode));
//			tmp->weight = weight[i];
//			tmp->Left = tmp->Right = NULL;
//			H->nodes[i] = tmp;
//		}
//		H->size = N;
//		BuildHeap(H,N);
//		tmp = BuildTree(H);
//		wpl1 = Get_Wpl(tmp,0);
//        printf("%d",wpl1);
////		scanf("%d",&loop);
////		while(loop > 0)
////		{
////			casenum++;
////			wpl2 = 0;
////			flag = 0;
////			T = (BinNode*)malloc(sizeof(BinNode));
////			T->flag = 0;
////			T->Left = T->Right = NULL;
////            printf("%d",)
////			for(int i = 0;i < N;i++)
////			{
////				scanf(" %c %s",&ch,s);
////				wpl2 += strlen(s) * weight[i];
////				if(wpl2 > wpl1) flag = 1;
////				if(flag == 0) flag = check(T,s);
////			}
////			printf("Case %d:\n",casenum);
////			if(flag == 0) printf("Yes\n");
////			else printf("No\n");
////			BinTree_Delete(T);
////			loop--;
////		}
////		HuffTree_Delete(tmp);
////	}
//}
//}
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
void BuildHeap(Heap *H,int N)
{
    int i;
    for (i=H->size/2; i>0; i--)
    {
        PercDown(H, i);
    }
}
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

int Get_Wpl(HuffNode *H,int depth)
{
	if(H->Left||H->Right)
	{
//		if(Get_Wpl(H->Left,depth + 1) + Get_Wpl(H->Right,depth + 1) < 0)printf("%d\n",Get_Wpl(H->Left,depth + 1) + Get_Wpl(H->Right,depth + 1));
		return Get_Wpl(H->Left,depth + 1) + Get_Wpl(H->Right,depth + 1);
	} 
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

HuffNode *BuildTree(Heap *H)
{
	int size = H->size;
	HuffNode *tmp,*tmp1,*tmp2;
	for(int i = 1;i < size;i++)
	{
//		printf("%d\n",H->size);
		tmp = (HuffNode*)malloc(sizeof(HuffNode));
		tmp1 = DeleteMin(H);
		tmp2 = DeleteMin(H);
//		printf("%d\n",H->size);
		tmp->Left = tmp1;
		tmp->Right = tmp2;
		tmp->weight = tmp1->weight + tmp2->weight;
		Insert(H,tmp);
//		printf("%d\n",H->size);
	}
	return H->nodes[1];
}

int check(BinNode *T,char *s)
{
	for(int i = 0;i < strlen(s);i++)
	{
		if(T->flag == 1)
		{
			return 1;
		}
		if(s[i] == '0')
		{
			if(T->Left == NULL)
			{
				BinNode *tmp = (BinNode*)malloc(sizeof(BinNode));
				tmp->Left = tmp->Right = NULL;
				tmp->flag = 0;
				T->Left = tmp;
			}
			T = T->Left;
		}
		else
		{
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
	if(T->flag || T->Left || T->Right)
	{
		return 1;
	}
	T->flag = 1;
	return 0;
}

struct Leftist
{
	HuffNode *node;
	int Npl;
	Leftist *Left,*Right;
};

Leftist *BuildLeftist(Leftist **H,int n);
Leftist *merge(Leftist *A, Leftist *B);
Leftist *merge1(Leftist *A, Leftist *B);
Leftist *DeleteMin(Leftist *A);
Leftist *Leftist_Huff(Leftist *A,int n);
void LeftistDelete(Leftist *T);
Leftist *merge4(Leftist **H);

Leftist *BuildLeftist(Leftist **H,int n)
{
	int front = 0,rear = n - 1;
	Leftist *tmp[2*n];
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
Leftist *Leftist_Huff(Leftist *A,int N)
{
	HuffNode *tmp,*tmp1,*tmp2;
	Leftist *tmp_l[4],*temp;
	for(int i = 1;i < N;i++)
	{
		tmp = (HuffNode*)malloc(sizeof(HuffNode));
		tmp1 = A->node;
		if(A->Left && (!A->Right ||(A->Left->node->weight < A->Right->node->weight))) 
		{	
			tmp2 = A->Left->node;
			tmp_l[1] = A->Left->Left;
			tmp_l[2] = A->Left->Right;
			tmp_l[3] = A->Right;
			free(A->Left);
			free(A);
		}
		else
		{
			tmp2 = A->Right->node;
			tmp_l[1] = A->Right->Left;
			tmp_l[2] = A->Right->Right;
			tmp_l[3] = A->Left;
			free(A->Right);
			free(A);
		}
		tmp->Left = tmp1;
		tmp->Right = tmp2;
		tmp->weight = tmp1->weight + tmp2->weight;
		tmp_l[0] = (Leftist*)malloc(sizeof(Leftist));
		tmp_l[0]->Left = tmp_l[0]->Right = NULL;
		tmp_l[0]->node = tmp;
		tmp_l[0]->Npl = 0;
		//sort
		for(int i = 0;i < 3;i++)
		{
			for(int j = 0;j < 3 - i;j++)
			{
				if(tmp_l[j + 1] && (!tmp_l[j] || tmp_l[j]->node->weight > tmp_l[j + 1]->node->weight))
				{
					temp = tmp_l[j];
					tmp_l[j] = tmp_l[j + 1];
					tmp_l[j + 1] = temp;
				}
			}
		}
		A = merge4(tmp_l);
	/*	A = merge(tmp_l[0],tmp_l[1]);
		A = merge(A,tmp_l[2]);
		A = merge(A,tmp_l[3]);*/
//		printf("good\n");
	}
//	if(A->Left == NULL && A->Right == NULL) printf("great!");
//	printf("%d\n",A->node->Right->Left->weight);
	return A;
}

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


Leftist *merge4(Leftist **H)
{
	if(H[1] == NULL) return H[0];
	Leftist *head = H[0],*temp;
	H[0] = head->Right;
		for(int i = 0;i < 3;i++)
		{
			for(int j = 0;j < 3 - i;j++)
			{
				if(H[j + 1] && (!H[j] || H[j]->node->weight > H[j + 1]->node->weight))
				{
					temp = H[j];
					H[j] = H[j + 1];
					H[j + 1] = temp;
				}
			}
		}
	head->Right = merge4(H);
	if(!head->Left||head->Left->Npl < head->Right->Npl)
	{
		temp = head->Left;
		head->Left = head->Right;
		head->Right = temp;
	}
	if (head->Right) head->Npl = head->Right->Npl + 1;
	else head->Npl = 0;
	return head;
}
