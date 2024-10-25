#include <stdio.h>
#include <malloc.h>

/*
问题：求一棵树的最大宽度
*/
/*
算法思想：
	使用层次遍历
	压入队列的时候，同时也将层号压入
	引用队列保存父节点
	1.接口设计：问题给什么就用什么
	2.出口（if树根不为空）
	3.问题规模递减（左右子树进行递归）
	考试的时候不需要写队列的函数，
	只需要写题目要求的函数，调用队列的函数，写上注释就行
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

#define MAX_SIZE 100
typedef struct QElemtype
{
	int level;//层号
	BiNode *pnode;
} QElemtype;
typedef struct Quene//队列
{
	QElemtype *pList;//用于指向二叉树中每个节点地址的数组，该数组中的每个元素是一个地址
	int front;//队头
	int rear;//队尾，牺牲一个存储单元来表示队列满和空
} Queue;
void initailQueue(Quene &Q)//对队列进行初始化
{
	//用pList指向一个用于存储节点地址的顺序表
	Q.pList = (QElemtype *)malloc(sizeof(QElemtype) * MAX_SIZE);
	//只能在rear存入数据，且rear永远指向下一个存储数据的空白单元
	//front指向已经存储进去的元素，且front永远指向未来第一个要出队列的数据所在单元
	//对u列为空时，front指向rear（空白数据单元）
	Q.rear = 0;
	Q.front = 0;
}
void enQueue(Quene &Q, QElemtype e)//入队
{
	//进入队列时应判断是否满，插入的位置是在rear
	//入队列后，rear存储数据将要移到下一个位置pos，如果pos是front，则pos=front
	//因为规定rear=front为对空，但实际上队列是满的，为了解决这个矛盾
	//将(rear+1)%MAX_SIZE=front规定为队满，也就是不能存入数据，牺牲一个存储单元
	int nextInsertPos = (Q.rear + 1) % MAX_SIZE;
	//在rear当前指向的存储单元写入数据
	Q.pList[Q.rear] = e;
	Q.rear = nextInsertPos;
}
void deQueue(Quene &Q, QElemtype *e)//出队
{
	*e = Q.pList[Q.front];//取出元素内容
	Q.front = (Q.front + 1) % MAX_SIZE;//往后移动一个位置
}
int isEmptyQueue(Quene Q)//队列判空
{
	if(Q.front == Q.rear)
		return 1;
	else
		return 0;
}

int getWidthMax(BiTree T)
{
	if(T == NULL)
	{
		return 0;
	}
	Quene Q;
	initailQueue(Q);
	QElemtype e;
	e.pnode = T;
	e.level = 1;
	enQueue(Q, e);

	int maxNodes = 0; //记录当前最大的节点数
	int currentNodes = 0; //记录当前层的节点数
	int currentLevel = 1; //记录当前层号

	while(isEmptyQueue(Q) != 1)
	{
		deQueue(Q, &e);
		if(currentLevel == e.level) //是当前层
		{
			currentNodes++;//当前层的节点数+1
		}
		else//不是当前层
		{
			if(maxNodes < currentNodes) //判断上一层的节点数是否大于最大值
			{
				maxNodes = currentNodes;
			}
			currentLevel = e.level; //改变当前层号
			currentNodes = 1; //初始当前层节点
		}
		//判断时候有左右孩子，有则压入队列
		BiNode *pnode = e.pnode;
		if(pnode->lchild != NULL)
		{
			//打包压入队列，注意队列的接口参数
			QElemtype tmp;
			tmp.level = e.level + 1;
			tmp.pnode = pnode->lchild;
			enQueue(Q, tmp);
		}
		if(pnode->rchild != NULL)
		{
			//打包压入队列，注意队列的接口参数
			QElemtype tmp;
			tmp.level = e.level + 1;
			tmp.pnode = pnode->rchild;
			enQueue(Q, tmp);
		}
	}
	//当循环结束时，由于层号不再改变，最后一层的节点数没有和当前最大值作比较
	//因此需要进行比较
	if(maxNodes < currentNodes)
	{
		maxNodes = currentNodes;
	}
	return maxNodes;

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

	printf("%d ", getWidthMax(T1));




}
