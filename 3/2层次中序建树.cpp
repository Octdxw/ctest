#include <stdio.h>
#include <malloc.h>

/*
中序+层次创建树
中序：左根右
层次：每一层从左到右，根左右的相对位置不变
*/
#define MAX_SIZE 100
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

BiTree creatBiTree(Elemtype levelOrderList[], int levelStartIndex, int levelEndIndex,
                   Elemtype inOrderList[], int inStartIndex, int inEndIndex)
{
	//中序+层次创建树
	if(levelStartIndex > levelEndIndex) //已经创建好
	{
		return NULL;
	}

	BiTree t = (BiNode *)malloc(sizeof(BiNode)); //创建（子）根节点
	t->data = levelOrderList[levelStartIndex];
	int rIndex;
	for(rIndex = inStartIndex; rIndex <= inEndIndex; rIndex++) //在中序序列中寻找（子）根的索引
	{
		//动的是中序序列的索引
		if(t->data == inOrderList[rIndex]) //在中序序列中找到（子）根的索引
		{
			break;
		}
	}
	//判断层次序列中的节点是否属于其左子树,属于，加入到左子树序列
	char leftlevelOrderList[MAX_SIZE];
	int leftlevelOrderListLength = 0;
	for(int i = levelStartIndex + 1; i <= levelEndIndex; i++)//依次取levelOrderList[]的每个节点去中序序列左子树序列中匹配
	{
		for(int j = inStartIndex;j<=rIndex-1;j++)//依次访问左子树中的每个顶点
		{
			if(inOrderList[j]==levelOrderList[i])//在左子树中
			{
				leftlevelOrderList[leftlevelOrderListLength]=levelOrderList[i];
				leftlevelOrderListLength++;
			}
		}
	}
	//判断层次序列中的节点是否属于其右子树,属于，加入到右子树序列
	char rightlevelOrderList[MAX_SIZE];
	int rightlevelOrderListLength = 0;
	for(int i = levelStartIndex + 1; i <= levelEndIndex; i++)//依次取levelOrderList[]的每个节点去中序序列右子树序列中匹配
	{
		for(int j = rIndex+1;j<=inEndIndex;j++)//依次访问右子树中的每个顶点
		{
			if(inOrderList[j]==levelOrderList[i])//在右子树中
			{
				rightlevelOrderList[rightlevelOrderListLength]=levelOrderList[i];
				rightlevelOrderListLength++;
			}
		}
	}
	t->lchild=creatBiTree(leftlevelOrderList,0,leftlevelOrderListLength-1,
						  inOrderList,inStartIndex,rIndex-1);//创建左子树
	t->rchild=creatBiTree(rightlevelOrderList,0,rightlevelOrderListLength-1,
						  inOrderList,rIndex+1,inEndIndex);//创建右子树
	
	return t;
}

int main()
{
	char levelOrderList[] = {'A', 'B', 'D', 'E', 'C', 'F', 'G'};
	int levelOrderListLength = 7;

	char inOrderList[] = {'D', 'B', 'E', 'A', 'F', 'C', 'G'};
	int inOrderListLength = 7;

	BiTree T1 = creatBiTree(levelOrderList,0,levelOrderListLength-1,
						   inOrderList,0,inOrderListLength-1);

	printf("先序序列：");
	preOrder(T1);
	printf("\n");
	
	printf("中序序列：");
	inOrder(T1);
	printf("\n");
}
