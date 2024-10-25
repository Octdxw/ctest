#include <stdio.h>
#include <malloc.h>

/*
问题：查找二叉树中值为x的节点，若存在，返回存储位置，不存在，返回NULL

*/
/*
算法思想：
	采用先序
	1.接口设计：问题给什么就用什么 T,x
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
	for(rIndex = inStartIndex; rIndex <= inStartIndex; rIndex++) //查找（子）根节点在中序序列的位置
	{
		//动的是中序序列的索引
		if(t->data == inOrderList[rIndex])//找到（子）根节点在中序序列的位置
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

BiNode *getNode(BiTree T, Elemtype x)
{
	if(T == NULL) //出口
	{
		return NULL;
	}
	if(T->data == x) //出口
	{
		return T;
	}
	BiNode *pnode = getNode(T->lchild, x); //上面两个判断都没执行，去左子树查找
	if(pnode != NULL) //左子树中找到，返回地址
	{
		return pnode;
	}
	if(pnode == NULL) //左子树没找到，去右子树查找
	{
		//若右子树有x，则返回x的地址
		return getNode(T->rchild, x);
	}//若没有，则进去右子树的空树，返回NULL
	return NULL;

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

	BiNode *pnode = getNode(T1, 'A');
	if(pnode != NULL)
	{
		printf("pnode:%c", pnode->data);
	}
	else
	{
		printf("不存在");
	}

}
