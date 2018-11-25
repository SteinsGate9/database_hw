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

int main()
{
	FibonacciHeap *A;
	int n = 10;
	int a[10],b[10];
	for(int i = 0;i < n;i++)
	{
		a[i] = i;
		b[i] = 10-i;
	}
	A = Fibonacci_build(n,a,b);
	printf("%d\n",Fibonacci_findmin(A)->num);
	Fibonacci_deletemin(A); 
	printf("%d\n",A->min->num);
	Fibonacci_deletemin(A); 
	printf("%d\n",A->min->num);
	Fibonacci_deletemin(A); 
	printf("%d\n",A->min->num);
	Fibonacci_deletemin(A); 
	printf("%d\n",A->min->num);
	Fibonacci_deletemin(A); 
	printf("%d\n",A->min->num);
//	printf("%d\n",A->min->num);
//	printf("%d\n",A->min->right->num);
//	printf("%d",Fibonacci_findmin(A)->num);
	
/*	
	FibonacciHeap *B;
	int n1 = 10;
	int c[10],d[10];
	for(int i = 0;i < n1;i++)
	{
		c[i] = 1;
		d[i] = 2 * i;
	}
	B = Fibonacci_build(n1,c,d);
	FibonacciHeap *C = Fibonacci_merge(B,A);
	printf("%d",Fibonacci_findmin(C)->num);
*/
}
