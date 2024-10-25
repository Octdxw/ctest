#include <stdio.h>
#include <malloc.h>

/*
问题：设计算法利用叶子节点的空指针域将所有的叶子节点连接成一个带头结点的双链表

*/
/*
算法思想：
	采用先序遍历每个叶子节点，使用尾插法
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

void preOrderOper(BiTree T, BiNode *&pTail)
{
	if(T!=NULL)
	{
		if(T->lchild==NULL &&T->rchild==NULL)//T是叶子节点
		{
			//尾插
			T->lchild=pTail;
			pTail->rchild=T;
			pTail=T;
		}
		else//T不是叶子节点，继续递归左右子树,根左右--先序遍历
		{
			preOrderOper(T->lchild,pTail);
			preOrderOper(T->rchild,pTail);
		}
	}
}

void LinkLeafNode(BiTree T)
{
	BiNode *L=(BiNode *)malloc(sizeof(BiNode));//L作为双链表的头节点
	BiNode *pTail=L;//尾指针
	L->lchild=NULL;
	L->rchild=NULL;
	
	//链接操作，采用先序遍历操作叶子节点
	preOrderOper(T,pTail);
	
	//打印双链表
	BiNode *pnode=L->rchild;
	while(pnode!=NULL)
	{
		printf("%c",pnode->data);
		pnode=pnode->rchild;
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
	
	LinkLeafNode(T1);
	

	

}
