#include <stdio.h>
#include <malloc.h>

/*
问题：求一棵二叉树的节点个数

*/
/*
算法思想：
	采用先序
	1.接口设计：问题给什么就用什么
	2.出口（if树根不为空）
	3.问题规模递减（左右子树进行递归）
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
	for(rIndex = inStartIndex; rIndex <= inEndIndex; rIndex++) //在中序序列中寻找（子）根的索引
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


int getNodeNum(BiTree T)//接口：给什么用什么
{
	if(T == NULL) //出口
	{
		return 0;
	}
	//递归左右子树
	int leftNum = getNodeNum(T->lchild);
	int rightNum = getNodeNum(T->rchild);
	return 1 + leftNum + rightNum;
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


	int num1 = getNodeNum(T1);
	printf("T1Num:%d\n", num1);
}
