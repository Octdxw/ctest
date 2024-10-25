#include <stdio.h>
#include <malloc.h>

/*
题目：
	对二叉树进行中序线索化
*/
/*
算法思想：

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

void inOrderThreading(BiThrTree &T, BiThrNode *&preNode) //中序线索化，左根右
{
	if(T != NULL)
	{
		inOrderThreading(T->lchild, preNode); //左子树线索化
		if(T->lchild == NULL) //对很线索化
		{
			T->lTag = 1;
			T->lchild = preNode;
			//printf("%d %c %d\n", T->lTag, T->data, T->rTag);
		}
		if(preNode != NULL && preNode->rchild == NULL) //相应的对前驱进行线索化
		{
			preNode->rTag = 1;//右孩子不存在
			preNode->rchild = T;
			//printf("%d %c %d\n", preNode->lTag, preNode->data, preNode->rTag);
		}
		preNode = T; //更新前驱为后继，进右子树的遍历
		inOrderThreading(T->rchild, preNode);
	}
}

void createinOrderThreadingTree(BiThrTree &T)
{
	BiThrNode *preNode = NULL;
	inOrderThreading(T, preNode);
}

int main()
{
	Elentype preOrderList[] = {'A', 'B', 'C', 'D', 'E'};
	int preOrderListLength = 5;

	Elentype inOrderList[] = {'C', 'D', 'B', 'A', 'E'};
	int inOrderListLength = 5;
	BiThrTree T = createBiTree(preOrderList, 0, preOrderListLength - 1,
	                           inOrderList, 0, inOrderListLength - 1);

	createinOrderThreadingTree(T);//中序线索化二叉树
}
