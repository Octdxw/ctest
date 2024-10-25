#include <stdio.h>
#include <malloc.h>
/*
题目：
	删除二叉排序树中所有节点值小于x的节点
*/
/*
算法思想：
	使用先序遍历
	1.T>x，先序搜索左子树并删除左子树中小于x的节点，保留该节点和右子树
	2.T<x，先序遍历搜索并删除其右子树中小于x的节点，在直接删除左子树所有的节点
	3.T=x，直接删除该节点的左子树
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

void deleteFunc(BSTree &T)
{
	if(T!=NULL)
	{
		//采用后续遍历删除
		deleteFunc(T->lchild);
		deleteFunc(T->rchild);
		T->lchild=NULL;
		T->rchild=NULL;
		free(T);
	}
}

void preOrderTraversing(ElemType x,BSTree &T)
{
	if(T!=NULL)
	{
		if(x==T->data)
		{
			deleteFunc(T->lchild);//删除其左子树
			T->lchild=NULL;
		}
		else if(x>T->data)//T的右子树可能存在大于等于x的节点，去遍历其右子树，删除左子树及根
		{
			preOrderTraversing(x,T->rchild);//遍历其右子树，将右子树中小于x的节点删除
			BSTNode *pnode=T;
			T=T->rchild;//T的右孩子代替T
			pnode->rchild=NULL;//此时pnode为87行T的左子树及根删除T的左子树及根
			deleteFunc(pnode);
				
		}
		else if(x<T->data)//T的左子树中可能存在小于x的节点
		{
			preOrderTraversing(x,T->lchild);//处理T的左子树中小于x的节点
		}
	}
}



int main()
{
	ElemType keyList[] = {88,40,20,10,30,60,58,70,90,89,99};
	int keyListLength = 11;
	BSTree T = creatBSTree(keyList, keyListLength);
	printf("中序遍历：");
	inOrderTravesing(T);
	printf("\n");

	preOrderTraversing(60,T);
	inOrderTravesing(T);

}