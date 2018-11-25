
#include<stdio.h>
#include<malloc.h>
#define max(a,b)(((a)>(b))?(a):(b))
#define tall(x) ((x) == NULL?-1:(x)->height)
typedef struct avlnode *avl;
struct avlnode
{
    avl left;
    avl right;
    int key;
    int height;
    int bf;
};

avl insert(avl tree,int node);
avl left(avl tree);
avl right(avl tree);
avl leftright(avl tree);
avl rightleft(avl tree);
int main()
{
    int number;
    scanf("%d",&number);
    avl tree = NULL;
    for(int i = 1;i<=number ; i++)
    {
        int shit;
        scanf("%d",&shit);
        tree = insert(tree,shit);
    }
    printf("%d",tree->key);
    return 0;
}

avl insert(avl tree,int node)
{
    if(!tree)
    {
        tree = (avl)malloc(sizeof(struct avlnode));;
        tree->key = node;
        tree->left = NULL;
        tree->right = NULL;
        tree->height = 0;
        tree->bf = 0;

        return tree;

    }
    if(tree->key < node)
    {

      tree->right = insert(tree->right,node);
      tree->bf = tall(tree->left) - tall(tree->right);
      if(tree->bf == -2)
      {
          if (tree->right->key < node)// zuozuo
          {
              tree = left(tree);

          }
          else                 // zuoyou
          {
              tree = rightleft(tree);

          }
          

      }tree->height = max(tall(tree->left),tall(tree->right))+1;
    }
    else
    {

        tree->left = insert(tree->left,node);
        tree->bf = tall(tree->left) - tall(tree->right);
        if(tree->bf == 2)
        {
            if(tree->left->key >node)
            {
                tree = right(tree);

            }
            else
            {
                tree = leftright(tree);

            }
        }
         tree->height = max(tall(tree->left),tall(tree->right))+1;

    }



   return tree;
}


avl left(avl tree)
{
    avl tm = tree->right;
    tree->right = tm->left;
    tm->left = tree;

    tm->height = max(tall(tm->left),tall(tm->right))+1;
    tm->bf = tall(tm->left) - tall(tm->right);
    tree->height = max(tall(tree->left),tall(tree->right))+1;
    tree->bf = tall(tree->left) - tall(tree->right);
    return tm;
}
avl right(avl tree)
{
    avl tm = tree->left;
    tree->left = tm->right;
    tm->right = tree;

    tm->height = max(tall(tm->left),tall(tm->right))+1;
    tm->bf = tall(tm->left) - tall(tm->right);
    tree->height = max(tall(tree->left),tall(tree->right))+1;
    tree->bf = tall(tree->left) - tall(tree->right);
    return tm;

}
avl leftright(avl tree)
{
    tree->left = left(tree->left);
    tree = right(tree);
    return tree;


}
avl rightleft(avl tree)
{
    tree->right = right(tree->right);
    tree = left (tree);
    return tree;


}