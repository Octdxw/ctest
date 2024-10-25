#include <stdio.h>
#include <malloc.h>
/*
	题目：
		计算一颗以孩子兄弟链表表示的树T的度，时间复杂度为O(n)
*/
/*
	算法思想：
		先跟遍历树，访问树的每个节点，并计算孩子的数量
*/

typedef int Elemtype;
typedef struct CSTNode //child,sibling
{
	Elemtype data;
	struct CSTNode *firstChild;
	struct CSTNode *nextSibling;
} CSTNode, *CSTree;
//CSTree等价于CSTNOde *


void preOrderTraverse(CSTree T) //先根遍历
{
	if(T != NULL)
	{
		printf("%d ", T->data); //先访问根
		CSTNode *pcurchild = T->firstChild; //访问孩子
		while(pcurchild != NULL)
		{
			preOrderTraverse(pcurchild);//访问孩子左子树，
			//孩子子树遍历完后，访问下一个兄弟
			preOrderTraverse(pcurchild->nextSibling);
		}
	}
}

void postOrderTraverse(CSTree T) //后根遍历
{
	if(T != NULL)
	{
		CSTNode *pcurchild = T->firstChild; //先访问孩子
		while(pcurchild != NULL)
		{
			postOrderTraverse(pcurchild);//访问孩子左子树
			//访问完孩子左子树后，访问下一个兄弟
			postOrderTraverse(pcurchild->nextSibling);
		}
		printf("%d ", T->data); //访问根
	}
}

int preOrderSearch(CSTree T)
{
	if(T == NULL)
	{
		return 0;
	}
	else
	{

		int max = 0;//记录最大的度
		int rootNodeDegree = 0;//用于记录当前根节点的度
		CSTNode *pcurchild = T->firstChild;
		while(pcurchild != NULL) //孩子不为空
		{
			//先根
			rootNodeDegree++;//孩子不为空，根节点的度++
			//求以孩子节点为根的度
			int childDegree = preOrderSearch(pcurchild);
			if(childDegree > max)
			{
				max = childDegree;
			}
			pcurchild = pcurchild->nextSibling
		}
		//循环结束,该根的度计算完毕，判断根节点的度和max哪个大
		if(rootNodeDegree > max)
		{
			return rootNodeDegree;
		}
		else
		{
			return max;
		}
	}
}




int main()
{

}
