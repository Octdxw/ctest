#include <stdio.h>
#include <malloc.h>

/*
中序+先序创建树
中序：左根右
先序：根左右
*/

typedef char Elemtype;
typedef struct BiNode
{
	Elemtype data;
	struct BiNode *lchild, *rchild;
} BiNode, *BiTree;
//Bitree与BiNode *等价

void preOrder(BiTree T)//先序遍历
{
	if(T != NULL) //根（子树根）不为空
	{
		printf("%c ", T->data);
		preOrder(T->lchild);//遍历左子树
		preOrder(T->rchild);//遍历右子树
	}
}
void inOrder(BiTree T)//中序遍历
{
	if(T != NULL) //根（子树根）不为空
	{

		inOrder(T->lchild);//遍历左子树
		printf("%c ", T->data);
		inOrder(T->rchild);//遍历右子树
	}
}

BiTree creatBiTree(Elemtype preOrderList[], int preStartIndex, int preEndIndex,
                   Elemtype inOrderList[], int inStartIndex, int inEndIndex)
{
	//中序+先序创建树
	if(preStartIndex > preEndIndex)//代表已创建完(子)树
	{
		return NULL;
	}

	BiNode *t = (BiNode *)malloc(sizeof(BiNode));
	t->data = preOrderList[preStartIndex];//（子）根节点
	int rIndex;//记录（子）根节点在中序序列的位置
	for(rIndex = inStartIndex; rIndex <= inEndIndex; rIndex++) //查找（子）根节点在中序序列的位置
	{
		//动的是中序序列的索引
		if(t->data == inOrderList[rIndex]) //找到（子）根节点在中序序列的位置
		{
			break;
		}
	}

	int length = rIndex - inStartIndex;
	t->lchild = creatBiTree(preOrderList, preStartIndex + 1, preStartIndex + length,
	                        inOrderList, inStartIndex, rIndex - 1); //创建左子树
	t->rchild = creatBiTree(preOrderList, preStartIndex + length + 1, preEndIndex,
	                        inOrderList, rIndex + 1, inEndIndex);//创建右子树
	return t;
}

int main()
{
	char preOrderList[] = {'A', 'B', 'D', 'E', 'C', 'F', 'G'};
	int preOrderListLength = 7;

	char inOrderList[] = {'D', 'B', 'E', 'A', 'F', 'C', 'G'};
	int inOrderListLength = 7;

	BiTree T1 = creatBiTree(preOrderList, 0, preOrderListLength - 1,
	                       inOrderList, 0, inOrderListLength - 1);

	printf("先序序列：");
	preOrder(T1);
	printf("\n");

	printf("中序序列：");
	inOrder(T1);
	printf("\n");

}
