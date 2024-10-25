#include <stdio.h>
#include <malloc.h>

/*
问题：假设一个仅含二元运算的算术表达式以二叉链表的形式存放在二叉树T，
		设计算法求解算术表达式的值
		（1+2）*3=9
			*
	+				3
1		2

*/
/*
算法思想：
	采用后序遍历,叶子节点是数字
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

int oper(char oper, int leftRes, int rightRes) // 算数
{
	switch(oper)
	{
		case '+':
			return leftRes + rightRes;
		case '-':
			return leftRes - rightRes;
		case '*':
			return leftRes * rightRes;
		case '/':
			return leftRes / rightRes; 
		default:
			// 如果 oper 不在规定的范围内，返回 0 或其他错误值
			return 0; 
	}
}


int getResult(BiTree T)
{
	if(T == NULL)
	{
		return 0;
	}
	else if(T->lchild == NULL && T->rchild == NULL) //T为叶子节点
	{
		return T->data-'0';//让数字字符变成数值
	}
	else//T不是叶子节点
	{
		int leftRes = getResult(T->lchild);
		int rightRes = getResult(T->rchild);
		return oper(T->data, leftRes, rightRes);
	}
}


int main()
{
	char preOrderList1[] = {'*', '+', '1', '2', '3'};
	int preOrderListLength1 = 5;

	char inOrderList1[] = {'1', '+', '2', '*', '3'};
	int inOrderListLength1 = 5;

	BiTree T1 = creatBiTree(preOrderList1, 0, preOrderListLength1 - 1,
	                        inOrderList1, 0, inOrderListLength1 - 1);
	printf("T1:\n");
	printf("先序序列：");
	preOrder(T1);
	printf("\n");
	printf("中序序列：");
	inOrder(T1);
	printf("\n");

	int res = getResult(T1);
	printf("res:%d",res);




}
