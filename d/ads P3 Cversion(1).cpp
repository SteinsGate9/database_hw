#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

#define maxsize 10000

/*****************/
typedef struct Binary_Node
{
	int num;
	int pos;
}*Pbn;

struct BinaryHeap
{
	int size;
	Binary_Node *node[maxsize];
};

BinaryHeap *Binary_build(int i,Binary_Node *a[]);
void Binary_Insert(BinaryHeap *A,Binary_Node *i);
Binary_Node *Binary_FindMin(BinaryHeap *A);
void Binary_DeleteMin(BinaryHeap *A);
BinaryHeap *Binary_Merge(BinaryHeap *A,BinaryHeap *B);

void PercolateDown(Binary_Node *a[], int j, int n);
BinaryHeap *Binary_build(int i,Binary_Node *a[])
{
	BinaryHeap *A = new BinaryHeap;
	A->size = i;
	for(int j = 0;j <= i;j++)
	{
		A->node[j] = a[j];
	}
	i = i / 2;
	for(int j = i;j > 0;j--){
    	PercolateDown(A->node, j, A->size);
  	}
	return A;
}
void PercolateDown(Binary_Node *a[], int j, int n)
{
	int left = 2 * j;
    int right = left + 1;
    int smallest = j;
    while (1)
    {
	    if (left <= n && a[left]->num <= a[j]->num)
		{
	        smallest = left;
		}
	    if (right <= n && a[right]->num <= a[smallest]->num)
		{
	        smallest = right;
		}
	    if (smallest != j)
		{
	        Binary_Node *tmp = a[j];
	        a[j] = a[smallest];
	        a[smallest] = tmp;
	    }
	    else break;
	    j = smallest;
	    left = 2 * j;
		right = left + 1;
	}
}

void Binary_Insert(BinaryHeap *A,Binary_Node *i)
{
	if(i->pos == -1)
	{
		A->size = 0;
		A->node[0] = i;
	}
	else
	{
		int j;
		for (j = ++A->size;A->node[j/2]->num > i->num;j = j / 2)
		{
			A->node[j] = A->node[j/2];
		}
	    A->node[j] = i;
	}
}

Binary_Node *Binary_FindMin(BinaryHeap *A)
{
	return A->node[1];
}

void Binary_DeleteMin(BinaryHeap *A)
{
    int i,Child;
    Binary_Node *MinElement,*LastElement;
    MinElement = A->node[1];
   // free(MinElement);
    LastElement = A->node[A->size--];
    A->node[A->size+1] = NULL;
    for ( i = 1; i * 2 <= A->size; i = Child )
	{
        Child = i * 2;
        if (Child != A->size && A->node[Child+1]->num < A->node[Child]->num)
        {
        	Child++;
		}
        if (LastElement->num > A->node[Child]->num)
        {
        	A->node[i] = A->node[Child];
		}
        else break;
    }
    A->node[i] = LastElement;

}

BinaryHeap *Binary_Merge(BinaryHeap *A,BinaryHeap *B)
{
	BinaryHeap *C ;
	int i,j;
	Binary_Node *nodes[maxsize];
	nodes[0] = A->node[0];
	for(i = 1;i <= A->size;i++){
		nodes[i] = A->node[i];
	}
	for(j = 1;j <= B->size;j++){
		nodes[j + A->size] = B->node[j];
	}
	C = Binary_build(A->size + B->size,nodes);
	return C;
}

/********************************************/
//typedef struct LeftistHeap* Leftist;

typedef struct LeftistHeap
{
	int num;
	int pos;
	LeftistHeap *Left;
	LeftistHeap *Right;
	int Npl;
}*Plp;

LeftistHeap *Leftist_build(int n,int *a,int *b);
LeftistHeap *Leftist_insert(LeftistHeap *A,int a,int b);
LeftistHeap *Leftist_merge(LeftistHeap *A,LeftistHeap *B);
LeftistHeap *Leftist_DeleteMin(LeftistHeap *A);

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

LeftistHeap *Leftist_DeleteMin(LeftistHeap *A)
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
/********************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct Fibonacci_Node
{
	int num;
	int pos;
	int degree;
//	int mark;
	Fibonacci_Node *p;
	Fibonacci_Node *child;
	Fibonacci_Node *left;
	Fibonacci_Node *right;
};

struct FibonacciHeap
{
	int n;
//	int maxdegree;
	Fibonacci_Node *min;
};



FibonacciHeap *Fibonacci_insert(FibonacciHeap *A,int a,int b);
FibonacciHeap *Fibonacci_build(int n,int *a,int *b);
FibonacciHeap *Fibonacci_merge(FibonacciHeap *A,FibonacciHeap *B);
Fibonacci_Node *Fibonacci_findmin(FibonacciHeap *A);
void Fibonacci_deletemin(FibonacciHeap *A);


void Fibonacci_add(Fibonacci_Node *A,Fibonacci_Node *B);
void Fibonacci_add(Fibonacci_Node *A,Fibonacci_Node *B)
{
	A->left = B->left;
	B->left->right = A;
	A->right = B;
	B->left = A;
}
FibonacciHeap *Fibonacci_insert(FibonacciHeap *A,int a,int b)
{
	if(A == NULL)
	{
		A = (FibonacciHeap *)malloc(sizeof(FibonacciHeap));
		A->min =  (Fibonacci_Node *)malloc(sizeof(Fibonacci_Node));
		A->n = 1;
//		A->maxdegree = 0;
		A->min->child = NULL;
		A->min->p = NULL;
		A->min->left = A->min;
		A->min->right = A->min;
		A->min->pos = a;
		A->min->num = b;
		A->min->degree = 0;
		return A;
	}
	else
	{
		Fibonacci_Node *new_n = (Fibonacci_Node *)malloc(sizeof(Fibonacci_Node));
		new_n->left = new_n;
		new_n->right = new_n;
		new_n->degree = 0;
		new_n->child = NULL;
		new_n->p = NULL;
		new_n->pos = a;
		new_n->num = b;
		Fibonacci_add(new_n,A->min);
		if(new_n->num < A->min->num)
		{
			A->min = new_n;
		}
		A->n++;
	//	printf("%d\n",A->min->num);
		return A;
	}
}

FibonacciHeap *Fibonacci_build(int n,int *a,int *b)
{
	FibonacciHeap *A = NULL;
	for(int i = 0;i < n;i++)
	{
		A = Fibonacci_insert(A,a[i],b[i]);
	}
	return A;
}

FibonacciHeap *merge1(FibonacciHeap *A,FibonacciHeap *B);
FibonacciHeap *Fibonacci_merge(FibonacciHeap *A,FibonacciHeap *B)
{
	if(A == NULL)
	{
		return B;
	}
	if(B == NULL)
	{
		return A;
	}
	FibonacciHeap *C = merge1(A,B);
	return C;
}
FibonacciHeap *merge1(FibonacciHeap *A,FibonacciHeap *B)
{
	Fibonacci_Node *tmp;
    tmp = A->min->right;
    A->min->right = B->min->right;
    B->min->right->left = A->min;
    B->min->right = tmp;
    tmp->left = B->min;
    if(A->min->num < B->min->num)
    {
    	B->min = A->min;
	}
	B->n += A->n;
	free(A);
	return B;
}

Fibonacci_Node *Fibonacci_findmin(FibonacciHeap *A)
{
	if(A == NULL)	return NULL;
	else return A->min;
}

void Fibonacci_remove(Fibonacci_Node *A)
{
	A->left->right = A->right;
	A->right->left = A->left;
}

Fibonacci_Node *Fibonacci_remove_min(FibonacciHeap *A);
Fibonacci_Node *Fibonacci_remove_min(FibonacciHeap *A)
{
	Fibonacci_Node *tmp = A->min;
	if(A->min == A->min->right)
	{
		A->min = NULL;
	}
	else
	{
		Fibonacci_remove(A->min);
		A->min = A->min->right;
	}
	tmp->left = tmp;
	tmp->right = tmp;
	return tmp;
}

void Fibonacci_link(Fibonacci_Node *A, Fibonacci_Node *B);
void Fibonacci_link(Fibonacci_Node *A, Fibonacci_Node *B)
{
	Fibonacci_remove(A);
    if (B->child == NULL)
    {
	    B->child = A;
	}
    else
    {
	    Fibonacci_add(A, B->child);
    }
    A->p = B;
    B->degree++;
}

void Consolidate(FibonacciHeap *A);
void Consolidate(FibonacciHeap *A)
{
	Fibonacci_Node *tmp;
	Fibonacci_Node *z = A->min;
	int m_degree = log(A->n)/log(1.618);
//		printf("%d",m_degree);
	int d;
	Fibonacci_Node *N[m_degree + 10];
	Fibonacci_Node *x;
	Fibonacci_Node *y;
	for(int i = 0;i < m_degree + 10;i++)
	{
		N[i] = (Fibonacci_Node*)malloc(sizeof(Fibonacci_Node));
	}
	for(int i = 0;i < m_degree + 10;i++)
	{
		N[i] = NULL;
	}
//	for(tmp = A->min->right;tmp!=A->min;tmp=tmp->right)
//		printf("%d",tmp->num);
	while(A->min != NULL)
	{
		x = Fibonacci_remove_min(A);
//		for(tmp = A->min->right;tmp!=A->min;tmp = tmp->right)
//			printf("%d\n",tmp->num);

//		printf("min:%d\n",x->num);
//		system("pause");
		d = x->degree;


		while (N[d] != NULL)
		{
		//	printf("%d\n",A->min->num);
			y = N[d];
			if(x->num > y->num)
			{
				tmp = x;
				x = y;
				y = tmp;
			}
			Fibonacci_link(y,x);
			N[d] = NULL;
			d++;
		}
		//printf("\n");
		N[d] = x;
//		for(int i = 0;i < m_degree + 10;i++)
//		{
//			if(N[i]!=NULL)
//			printf("N[%d] = %d\n",i,N[i]->num);
//		}
//		printf("\n");
	}

	A->min = NULL;

	for(int i = 0;i < m_degree + 10;i++)
	{
		if(N[i] != NULL)
		{
	//		printf("%d\n",N[i]->num);
			if(A->min == NULL)
			{
				A->min = N[i];
			}
			else
			{
				Fibonacci_add(N[i], A->min);
				if(N[i]->num < A->min->num)
				{
					A->min = N[i];
				}
			}
		}
	}
//				printf("ok");
}
void Fibonacci_deletemin(FibonacciHeap *A)
{
	if(A == NULL || A->min == NULL)
	{
		return;
	}
	else
	{//	Fibonacci_Node* tmp;
	//	for(tmp = A->min->right;tmp!=A->min;tmp=tmp->right)
	//	printf("%d",tmp->num);
		Fibonacci_Node* a = NULL;
		Fibonacci_Node* z = A->min;
		while(A->min->child != NULL)
		{
			a = z->child;
			Fibonacci_remove(a);
			if(a->right == a)
			{
				z->child = NULL;
			}
			else
			{
				z->child = a->right;
			}
			Fibonacci_add(a, A->min);
			a->p = NULL;
		}
		Fibonacci_remove(z);

		if(z->right == z)
		{
//					printf("ok");
			A->min = NULL;
//			return;
//										printf("ok");
		}
		else
		{

			A->min = z->right;
			Consolidate(A);
		}
		A->n--;
		return;
	}
}
/*
int main()
{
	int i = 10;
	int a[10];
	for(int j = 0;j < 10;j++)
	{
		a[j] = 10 - j;
	}
	BinaryHeap *A = Binary_build(i,a);
	for(int j = 1;j < 11;j++)
	{
		printf("%d ",A->num[j]);
		printf("%d \n",A->pos[j]);
	}
} */
