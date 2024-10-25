#include <stdio.h>
#include <malloc.h>

/*
题目：
	对线索二叉树进行先序遍历
*/
/*
算法思想：
	如果pre的左孩子存在，其后继就是左孩子
	如果左孩子不存在，其后继就是右孩子或者后孩子的线索
*/

typedef char Elentype;
typedef struct BiThrNode
{
	Elentype data;
	struct BiThrNode *lchild, *rchild;
	int lTag;
	int rTag;
} BiThrNode, *BiThrTree;
//BiThrTree等价于BiThrNode*

BiThrTree createBiTree(Elentype preOrderList[], int preStartIndex, int preEndIndex,
                       Elentype inOrderList[], int inStartIndex, int inEndIndex)
{
	//创建二叉树,未线索化
	if(preEndIndex < preStartIndex)
	{
		return NULL;
	}

	BiThrNode  *t = (BiThrNode  *)malloc(sizeof(BiThrNode));
	t->data = preOrderList[preStartIndex];
	t->lTag = 0;
	t->rTag = 0;
	int rIndex;
	for(rIndex = inStartIndex; rIndex <= inEndIndex; rIndex++) //在中序序列中找到根节点的索引
	{
		if(t->data == inOrderList[rIndex])
		{
			break;
		}
	}
	int length = rIndex - inStartIndex;
	t->lchild = createBiTree(preOrderList, preStartIndex + 1, preStartIndex + length,
	                         inOrderList, inStartIndex, rIndex - 1);
	t->rchild = createBiTree(preOrderList, preStartIndex + length + 1, preEndIndex,
	                         inOrderList, rIndex + 1, inEndIndex);
	return t;
}

void preOrderThreading(BiThrTree &T, BiThrNode *&preNode) //对T先序线索化,根左右
{
	if(T != NULL)
	{
		if(T->lchild == NULL)//对根进行线索化
		{
			T->lTag = 1;
			T->lchild = preNode;
			//printf("%d %c %d\n",T->lTag,T->data,T->rTag);
		}
		if(preNode != NULL && preNode->rchild == NULL)//相应的对前驱进行线索化
		{
			preNode->rTag = 1;
			preNode->rchild = T;
			//printf("%d %c %d\n",preNode->lTag,preNode->data,preNode->rTag);
		}

		preNode = T;//改变前驱节点，用于后代的线索化
		if(T->lTag == 0)//标记为0，才能进行线索化
		{
			preOrderThreading(T->lchild, preNode);//对T的左子树线索化
		}
		if(T->rTag == 0)//标记为0，才能进行线索
		{
			preOrderThreading(T->rchild, preNode);//对T的右子树线索化
		}
	}
}

void createPreThreading(BiThrTree &T)//创建线索二叉树
{
	BiThrNode *preNode = NULL; //前驱节点
	preOrderThreading(T, preNode);
}

void preOrderTraversing(BiThrTree T)//先序遍历
{
	BiThrNode *pSuccesser = NULL;
	BiThrNode *pre = T; //先序遍历时，第一个节点是根
	while (pre != NULL)
	{
		if(pre->lTag == 0) //左孩子存在
		{
			pSuccesser = pre->lchild;
		}
		else
		{
			pSuccesser = pre->rchild;
		}
		printf("%c ", pre->data);
		pre = pSuccesser; //更新前驱为后继，进行下次循环
	}
}


int main()
{
	Elentype preOrderList[] = {'A', 'B', 'C', 'D', 'E'};
	int preOrderListLength = 5;

	Elentype inOrderList[] = {'C', 'D', 'B', 'A', 'E'};
	int inOrderListLength = 5;
	BiThrTree T = createBiTree(preOrderList, 0, preOrderListLength - 1,
	                           inOrderList, 0, inOrderListLength - 1);

	createPreThreading(T);//先序线索化二叉树
	preOrderTraversing(T);//先序遍历
}
