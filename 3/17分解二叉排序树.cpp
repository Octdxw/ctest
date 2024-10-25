#include <stdio.h>
#include <malloc.h>
/*
题目：
	将二叉排序树T分解成两棵二叉排序树t1与t2，
	使得t1中的所有节点的关键值都小于key，t2中的所有节点的关键值都大于key
*/
/*
算法思想：
	采用先序遍历
	1.key小于根，将根及右子树划分到t2，继续划分左子树
	2.key等于根，将根的左右子树分别划分到t1与t2中
	3.key大于根，将根及左子树划分到t1，继续分解右子树
	重复，直到树中不存在未划分的节点
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

void insertTree(BSTree T, BSTree &t) //例insertTree(T,t2)//T及T的右子树插入T2
{
	if(t == NULL) //待被插入的(子)树为空（T2或其子树）
	{
		t = T;
	}
	else if(T->data < t->data) //待被插入的树的值更大，查到其左子树上
	{
		insertTree(T, t->rchild);
	}
	else //待被插入的树的值更小，查到其右子树上
	{
		insertTree(T, t->lchild);
	}
}

void spilitBSTree(ElemType key, BSTree &T, BSTree &T1, BSTree &T2)
{
	if(T != NULL)
	{
		if(key < T->data) //key小于根T，分解T的左子树，T及T的右子树插入T2
		{
			//分解T的左子树
			spilitBSTree(key, T->lchild, T1, T2);
			//左子树分解完，T的左子树为NULL
			T->lchild = NULL;
			insertTree(T, T2); //T及T的右子树插入T2
		}
		else if(key == T->data)
		{
			insertTree(T->lchild, T1);
			insertTree(T->rchild, T2);
			//free(T);
			T = NULL;
		}
		else //key大于根，分解T的右子树，T及T的左子树插入T1
		{
			spilitBSTree(key, T->rchild, T1, T2);
			T->rchild = NULL;
			insertTree(T, T1);
		}
	}

}



int main()
{
	ElemType keyList[] = {40, 10, 45, 15};
	int keyListLength = 4;
	BSTree T = creatBSTree(keyList, keyListLength);
	printf("中序遍历：");
	inOrderTravesing(T);
	printf("\n");

	BSTree T1 = NULL;
	BSTree T2 = NULL;
	spilitBSTree(17, T, T1, T2);
	printf("T1：");
	inOrderTravesing(T1);
	printf("\n");
	printf("T2：");
	inOrderTravesing(T2);

}