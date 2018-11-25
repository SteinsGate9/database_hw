#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define maxsize 10000

struct LeftistHeap
{
	int num;
	int pos;
	LeftistHeap *Left;
	LeftistHeap *Right;
	int Npl;
};

LeftistHeap *Leftist_build(int n,int *a,int *b);
LeftistHeap *Leftist_insert(LeftistHeap *A,int a,int b);
LeftistHeap *Leftist_merge(LeftistHeap *A,LeftistHeap *B);
LeftistHeap *Leftist_deletemin(LeftistHeap *A);

LeftistHeap *Leftist_build(int n,int *a,int *b)
{
	LeftistHeap *A = NULL;
	for(int i = 0;i < n;i++)
	{
		A = Leftist_insert(A,a[i],b[i]);
	}
	return A;
}

LeftistHeap *Leftist_insert(LeftistHeap *A,int a,int b)
{
	LeftistHeap *B = (LeftistHeap *)malloc(sizeof(LeftistHeap));
	B->Left = NULL;
	B->Right = NULL;
	B->pos = a;
	B->num = b;
	B->Npl = 0;
	LeftistHeap *C = Leftist_merge(A,B);
	return C;
}

static LeftistHeap *merge1(LeftistHeap *A, LeftistHeap *B);
LeftistHeap *Leftist_merge(LeftistHeap *A,LeftistHeap *B)
{
	if (A == NULL)  return B;	
	if (B == NULL)  return A;	
	if (A->num < B->num )  return merge1(A,B);
	else return merge1(B,A);
}
static LeftistHeap *merge1(LeftistHeap *A, LeftistHeap *B)
{
	if (A->Left == NULL ) 
	{ 
		A->Left = B;
	}			   
	else 
	{
		A->Right = Leftist_merge(A->Right,B);
		if (A->Left->Npl < A->Right->Npl )
		{ 
			LeftistHeap *tmp = A->Right;
			A->Right = A->Left;
			A->Left = tmp;
		} 
		A->Npl = A->Right->Npl + 1;
	}
	return A;
}

LeftistHeap *Leftist_deletemin(LeftistHeap *A)
{
	if(A == NULL)
	{
		printf("bad input\n");
		return NULL;
	}
	else
	{
		LeftistHeap *B = A->Left;
		LeftistHeap *C = A->Right;
		free(A);
		return Leftist_merge(B,C);
	}
}

int main()
{
	int a[100],b[100];
	for(int i = 0;i < 100;i++)
	{
		a[i] = i;
		b[i] = -i*i + 100*i;
	}
	LeftistHeap *A = Leftist_build(100,a,b);
//	LeftistHeap *B = Leftist_insert(A,a,b);
//	printf("ok");
	for(int i = 0;i < 100;i++)
	{ 
		A = Leftist_deletemin(A);
		if(A != NULL)
		{	
			printf("%d %d\n",A->num,A->Npl); 
			
		}
		else
		{
			printf("the heap is empty");
			break;
		} 
	}
}
