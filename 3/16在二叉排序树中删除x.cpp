#include <stdio.h>
#include <malloc.h>
/*
题目：
	删除二叉排序树中值为x的节点
*/
/*
算法思想：
	先序遍历找到x节点
	1.x为叶子（没有孩子的根）节点
	2.x为线性结构，让其独生子代替它
	3.x为非线性结构，找到x左子树中最大者pMax，让x右孩子挂在pMax的右子树上
		最后让x的左孩子代替x
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

void deleteoper(BSTree &T)
{
	if(T->lchild==NULL&&T->rchild==NULL)
	{
		T=NULL;
	}
	else if(T->lchild==NULL)//线性结构,只存在右子树，让右孩子代替T
	{
		//BSTNode *pnode=T;
		T=T->rchild;//让右孩子代替T
		//free(pnode);
	}
	else if(T->rchild==NULL)//线性结构,只存在左子树，让左孩子代替T
	{
		//BSTNode *pnode=T;
		T=T->lchild;//让左孩子代替T
		//free(pnode);
	}
	else //T存在左右孩子
	{
		//寻找T的左子树中的最大者pMax，把T的右孩子挂到pMax的右孩子上，
		//最后让T的左孩子代替T
		BSTNode *pMax=T->lchild;
		while(pMax->rchild!=NULL) //寻找左子树中的最大者pMax
		{
			pMax=pMax->rchild;
		}
		pMax->rchild=T->rchild;
		//BSTNode *pnode=T;
		T=T->lchild;//最后让x的左孩子代替T
		//free(pnode);
	}
}



void deleteXinBSTree(BSTree &T,ElemType x)
{
	if(T!=NULL)
	{
		if(T->data==x)
		{
			//删除操作
			deleteoper(T);
		}
		else if(x<T->data)
		{
			deleteXinBSTree(T->lchild,x);
		}
		else
		{
			deleteXinBSTree(T->rchild,x);
		}
	}
}


int main()
{
	ElemType keyList[] = {40, 10, 45, 15};
	int keyListLength = 4;
	BSTree T= creatBSTree(keyList,keyListLength);
	printf("中序遍历：");
	inOrderTravesing(T);
	printf("\n");
	
	deleteXinBSTree(T,40);
	printf("中序遍历：");
	inOrderTravesing(T);
}
