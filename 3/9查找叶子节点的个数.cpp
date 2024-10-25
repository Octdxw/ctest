#include <stdio.h>
#include <malloc.h>

/*
问题：求一颗二叉树中叶子节点的个数

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

int getLeafNum(BiTree T)
{
	if(T==NULL)//出口
	{
		return 0;
	}
	else if(T->lchild==NULL&&T->rchild==NULL)//是叶子节点
	{
		return 1;
	}
	else//不是叶子节点，也不为空，继续递归其左右子树
	{
		return getLeafNum(T->lchild)+getLeafNum(T->rchild);
	}
}


int main()
{
	char preOrderList1[] = {'A', 'B', 'D', 'E', 'C', 'F', 'G'};
	int preOrderListLength1 = 7;

	char inOrderList1[] = {'D', 'B', 'E', 'A', 'F', 'C', 'G'};
	int inOrderListLength1 = 7;

	BiTree T1 = creatBiTree(preOrderList1, 0, preOrderListLength1 - 1,
	                        inOrderList1, 0, inOrderListLength1 - 1);
	printf("T1:\n");
	printf("先序序列：");
	preOrder(T1);
	printf("\n");
	printf("中序序列：");
	inOrder(T1);
	printf("\n");
	
	int LeafNun= getLeafNum(T1);
	printf("LeafNun:%d",LeafNun);
	

}
