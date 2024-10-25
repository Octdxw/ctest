#include <stdio.h>
#include <malloc.h>
/*
题目：
	二叉排序树的构建
*/
/*
算法思想：
	遍历key数组，递归插入
*/

typedef int ElemType;
typedef struct BSTNode  //binary search tree node
{
	ElemType data;
	struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;
//BSTree等价于BSTNode *

void inOrderTravesing(BSTree T)//中序遍历
{
	if(T!=NULL)
	{
		inOrderTravesing(T->lchild);
		printf("%d ",T->data);
		inOrderTravesing(T->rchild);
	}
}

void insertKey(BSTree &T, ElemType key) //将key插入T(子)树中
{
	if(T == NULL)//（子）树为空
	{
		BSTNode *pnode = (BSTNode *)malloc(sizeof(BSTNode));
		pnode->data=key;
		pnode->lchild=NULL;
		pnode->rchild=NULL;
		T=pnode;
	}
	else if(key<T->data)
	{
		//插在左子树上,与该函数需求相同，产生递归
		insertKey(T->lchild,key);
	}
	else if(key>T->data)
	{
		insertKey(T->rchild,key);
	}
}

BSTree creatBSTree(ElemType keyList[],int keyListLength)
{
	BSTree T = NULL; // 初始化树
	for(int i = 0; i < keyListLength; i++)
	{
		//将key插入T(子)树中
		insertKey(T, keyList[i]);
	}
	return T;
}


int main()
{
	ElemType keyList[] = {40, 10, 45, 15};
	int keyListLength = 4;
	BSTree T= creatBSTree(keyList,keyListLength);
	inOrderTravesing(T);
}
