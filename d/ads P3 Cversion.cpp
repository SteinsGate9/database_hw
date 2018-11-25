#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define maxsize 10000
/*****************/
struct BinaryHeap
{
	int size;
	int *num;
};

BinaryHeap *Binary_build(int i,int *a);
void Binary_Insert(BinaryHeap *A,int i);
int Binary_FindMin(BinaryHeap *A);
void Binary_DeleteMin(BinaryHeap *A);
BinaryHeap *Binary_Merge(BinaryHeap *A,BinaryHeap *B);

void AdjustBinaryHeap(int *a, int j, int i);
BinaryHeap *Binary_build(int i,int *a)
{
	BinaryHeap *A = new BinaryHeap;
	A->size = i;
	i = i / 2;
	for(int j = i;j > 0;j--){
    	AdjustBinaryHeap(a, j, i);
  	}
   	for(int j = 0;j < i;j++)
   	{
   		A->num[j + 1] = a[j];
	}
}
void AdjustBinaryHeap(int *a, int j, int i)
{
    int left = 2*j;
    int right = 2*j+1;
    int smallest = j;

    if (a[left-1] <= a[i-1] && left <= i)
        smallest = left;
    if (a[right-1] <= a[smallest-1] && right <= i)
        smallest = right;
    if (smallest != j)
	{
        int temp = a[ j-1 ];
        a[ j-1 ] = a[ smallest-1 ];
        a[ smallest-1 ] = temp;
        AdjustBinaryHeap(a, smallest, i);
    }
}

void Binary_Insert(BinaryHeap *A,int i)
{
	int j;
    for (j = ++A->size;A->num[j/2] > i;j = j / 2)
	{
		A->num[j] = A->num[j/2];
	}
    A->num[j] = i;
}

int Binary_FindMin(BinaryHeap *A)
{
	return A->num[1];
}

void Binary_DeleteMin(BinaryHeap *A)
{
    int i,Child;
    int MinElement,LastElement;
    MinElement = A->num[1];
    LastElement = A->num[A->size--];
    for ( i = 1; i * 2 <= A->size; i = Child )
	{
        Child = i * 2;
        if (Child != A->size && A->num[Child+1] < A->num[Child])
        {
        	Child++;
		}
        if (LastElement > A->num[Child])
        {
        	A->num[i] = A->num[Child];
		}
        else break;
    }
    A->num[i] = LastElement;
}

BinaryHeap *Binary_Merge(BinaryHeap *A,BinaryHeap *B)
{
	BinaryHeap *C = (BinaryHeap*)malloc(sizeof(BinaryHeap));
	int i,j;
	int number[maxsize];
	for(i = 0;i < A->size;i++){
		number[i] = A->num[i + 1];
	}
	for(j = 0;j < B->size;j++){
		number[j + A->size] = B->num[j + 1];
	}
	C->num = number;
	C->size = A->size + B->size;
	return C;
}

/********************************************/
//typedef struct LeftistHeap* Leftist;
struct LeftistHeap
{
	int num;
	LeftistHeap *Left;
	LeftistHeap *Right;
	int Npl;
};

LeftistHeap *Leftist_build(int n,int *a);
void Leftist_Insert(LeftistHeap *A,int i);
int Leftist_FindMin(LeftistHeap *A);
void Leftist_DeleteMin(LeftistHeap *A);
LeftistHeap *Leftist_Merge(LeftistHeap *A,LeftistHeap *B);

LeftistHeap *Leftist_build(int n,int *a)
{
	LeftistHeap* A = (LeftistHeap*)malloc(sizeof(LeftistHeap));
	A = NULL;
	for(int j = 0;j < n;j++)
	{
		Leftist_Insert(A,a[j]);
	}
	return A;
}
void Leftist_Insert(LeftistHeap *A,int i)
{
	if(A == NULL)
	{
		LeftistHeap* B = (LeftistHeap*)malloc(sizeof(LeftistHeap));
		B->num = i;
		B->Left = NULL;
		B->Right = NULL;
		B->Npl = 0;
		A = B;
	}
	else
	{
		LeftistHeap* B = (LeftistHeap*)malloc(sizeof(LeftistHeap));
		B->num = i;
		B->Left = NULL;
		B->Right = NULL;
		B->Npl = 0;
		A = Leftist_Merge(A,B);
	}
}

int Leftist_FindMin(LeftistHeap *A)
{
	return A->num;
}

void Leftist_DeleteMin(LeftistHeap *A)
{
	LeftistHeap* B = A->Left;
	LeftistHeap* C = A->Right;
	A = Leftist_Merge(B,C);
}

LeftistHeap *Merge1(LeftistHeap *A,LeftistHeap *B);
LeftistHeap *Leftist_Merge(LeftistHeap *A,LeftistHeap *B)
{
	if (A == NULL)  return A;
	if (B == NULL)  return B;
	if (A->num < B->num )  return Merge1(A,B);
}
LeftistHeap *Merge1(LeftistHeap *A, LeftistHeap *B)
{
	if (A->Left == NULL )
	{
		A->Left = B;
	}
	else
	{
		A->Right = Leftist_Merge(A->Right,B);
		if (A->Left->Npl < B->Right->Npl )
		{
			LeftistHeap *tmp = A->Right;
			A->Right = A->Left;
			A->Left = tmp;
		}
		A->Npl = A->Right->Npl + 1;
	}
	return A;
}

/********************************/
typedef struct Fibonacci_Node *Node;
struct FibonacciHeap
{
	int n;
	Node min;
};
struct Fibonacci_Node
{
	int num;
	int degree;
	int mark;
	Node p;
	Node child;
	Node left;
	Node right;
};

FibonacciHeap *Fibonacci_build(int n,int *a);
void Fibonacci_Insert(FibonacciHeap *A,int i);
int Fibonacci_FindMin(FibonacciHeap *A);
Node Fibonacci_DeleteMin(FibonacciHeap *A);
FibonacciHeap *Fibonacci_Merge(FibonacciHeap *A,FibonacciHeap *B);

FibonacciHeap *Fibonacci_build(int n,int *a)
{
	FibonacciHeap *A = (FibonacciHeap*)malloc(sizeof(FibonacciHeap));
	A->min = NULL;
	A->n = 0;
	for(int i = 0;i < n;i++)
	{
		Fibonacci_Insert(A,a[i]);
	}
	return A;
}

void Fibonacci_Insert(FibonacciHeap *A,int i)
{
	Node new_n = (Node)malloc(sizeof(Fibonacci_Node));
	new_n->child = NULL;
	new_n->p = NULL;
	new_n->left = NULL;
	new_n->right = NULL;
	new_n->mark = 0;
	new_n->degree = 0;
	new_n->num = i;
	if(A->min == NULL)
	{
		new_n->left = new_n;
		new_n->right = new_n;
		A->min = new_n;
	}
	else
	{
		Node tmp = A->min->right;
		A->min->right = new_n;
		new_n->left = A->min;
		new_n->right = tmp;
		tmp->left = new_n;
		if (new_n->num < A->min->num)
		{
			A->min = new_n;
		}
	}
	(A->n)++;
}

int Fibonacci_FindMin(FibonacciHeap *A)
{
	return A->min->num;
}

FibonacciHeap *Fibonacci_Merge(FibonacciHeap *A,FibonacciHeap *B)
{
	FibonacciHeap *C = (FibonacciHeap*)malloc(sizeof(FibonacciHeap));
	C->min = NULL;
	C->n = 0;
	C->min = A->min;
	Node tmp1 = A->min->right;
	Node tmp2 = B->min->left;
	A->min->right = B->min;
	B->min->left = A->min;
	tmp2->right=tmp1;
	tmp1->left=tmp2;
	if((A->min == NULL) || ((B->min != NULL) && (A->min->num > B->min->num)))
	{
		C->min = B->min;
	}
	C->n = A->n + B->n;
	return C;
}

void Consolidate(FibonacciHeap *A);
void Fibonacci_Insert2(FibonacciHeap *A,Node x);
Node Fibonacci_DeleteMin(FibonacciHeap *A)
{
	Node z = A->min;
	if(z != NULL)
	{
		Node tmp;
		Node tmp1 = z->left;
		Node tmp2 = z->right;
		z->child->p = NULL;
		z->child->left = tmp1;
		for(tmp = z->child->right;tmp != z->child;tmp = tmp->right)
		{
			tmp->p = NULL;
		}
		z->child->left->right = tmp2;
		tmp1->right = z->child;
		tmp2->left = z->child->left;
		if(A->n == 1)
		{
			A->min == NULL;
		}
		else
		{
			A->min = z->right;
			Consolidate(A);
		}
		(A->n)--;
		return z;
	}
}
void Consolidate(FibonacciHeap *A)
{
	int number = log(A->n)/log((1+sqrt(5))/2);
	Node A1[number];
	for(int i = 0;i < number;i++)
	{
		A1[i] = NULL;
	}
	Node tmp = A->min;
	int d = tmp->degree;
	A1[A->min->degree] = tmp;
	for(tmp = tmp->right;tmp == A->min;tmp = tmp->right)
	{
		Node x = tmp;
		d = x->degree;
		while(A1[d]!=NULL)
		{
			Node y = A1[d];
			if(x->num > y->num)
			{
				Node tmp1 = x;
				x = y;
				y = tmp1;
			}
			y->p = x;
			Node tmp2 = x->child->right;
			x->child->right = y;
			y->left = x->child;
			y->right = tmp2;
			tmp2->left = y;
			x->degree++;
			A1[d] = NULL;
			d++;
		}
		A1[d] = x;
	}
	A->min = NULL;
	for(int i = 0;i < number;i++)
	{
		if(A1[i] != NULL){
			Fibonacci_Insert2(A,A1[i]);
		}
	}
}

void Fibonacci_Insert2(FibonacciHeap *A,Node x)
{
	if(A->min == NULL)
	{
		x->left = x;
		x->right = x;
		A->min = x;
	}
	else
	{
		Node tmp = A->min->right;
		A->min->right = x;
		x->left = A->min;
		x->right = tmp;
		tmp->left = x;
		if (x->num < A->min->num)
		{
			A->min = x;
		}
	}
	(A->n)++;
}
