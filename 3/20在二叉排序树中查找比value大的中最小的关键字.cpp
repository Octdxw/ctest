#include <stdio.h>
#include <malloc.h>
/*
题目：
	查找二叉排序树中比value大的值中最小的关键字
*/
/*
算法思想：
	使用中序序列(右根左，降序)
	用一变量保存上次打印的结果
	1.先进行右子树遍历
	2.if（这一次的T->data>value）
		去左子树查找
	3.f（这一次的T->data<=value）
		打印上一次的值
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
	if(T != NULL)
	{
		inOrderTravesing(T->lchild);
		printf("%d ", T->data);
		inOrderTravesing(T->rchild);
	}
}

void insertKey(BSTree &T, ElemType key) //将key插入T(子)树中
{
	if(T == NULL)//（子）树为空
	{
		BSTNode *pnode = (BSTNode *)malloc(sizeof(BSTNode));
		pnode->data = key;
		pnode->lchild = NULL;
		pnode->rchild = NULL;
		T = pnode;
	}
	else if(key < T->data)
	{
		//插在左子树上,与该函数需求相同，产生递归
		insertKey(T->lchild, key);
	}
	else if(key > T->data)
	{
		insertKey(T->rchild, key);
	}
}

BSTree creatBSTree(ElemType keyList[], int keyListLength)
{
	BSTree T = NULL; // 初始化树
	for(int i = 0; i < keyListLength; i++)
	{
		//将key插入T(子)树中
		insertKey(T, keyList[i]);
	}
	return T;
}

BSTNode *pre = NULL;
BSTNode *getMoreMin(BSTree T, ElemType value)
{
	if(T != NULL)
	{
		getMoreMin(T->rchild, value);
		if(T->data > value)
		{
			pre=T;;
			//printf("pre:%d\n", pre->data);
			getMoreMin(T->lchild, value);
		}
		else if(T->data <= value)
		{
			return pre;
		}


	}
}

int main()
{
	ElemType keyList[] = {88, 40, 20, 10, 30, 60, 58, 70, 90, 89, 99};
	int keyListLength = 11;
	BSTree T = creatBSTree(keyList, keyListLength);
	printf("中序遍历：");
	inOrderTravesing(T);
	printf("\n");

	BSTNode *pnode= getMoreMin(T, 60);
	printf("pnode:%d\n",pnode->data);


}