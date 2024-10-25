#include <stdio.h>
#include <malloc.h>
/*
	题目：
		森林的遍历
*/
/*
	算法思想：
		森林只有一棵树和其他树之分
		先序遍历：先访问根，根的子树，再遍历其他树
		后序遍历：先访问根的子树，根，再遍历其他树
*/

typedef int Elemtype;
typedef struct CSTNode //child,sibling
{
	Elemtype data;
	struct CSTNode *firstChild;
	struct CSTNode *nextSibling;
} CSTNode, *CSTree;
//CSTree等价于CSTNOde *

/*
//以下是树的遍历
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
*/

//森林的遍历
//此时的森林中不包含虚构的节点，即根就是第一颗树的根
void preOrderTraverse(CSTree T)//森林的先序遍历
{
	if(T != NULL)
	{
		printf("%d ", T->data); //先访问根
		CSTNode *pcurchild = T->firstChild; //访问根的第一个孩子
		while(pcurchild != NULL)
		{
			preOrderTraverse(pcurchild);
			pcurchild = pcurchild->nextSibling;//根的下一个孩子
		}
		//访问森立中的下一棵树
		preOrderTraverse(T->nextSibling);
	}
}

void inOrderTraverse(CSTree T)//森林的中序遍历
{
	if(T != NULL)
	{
		CSTNode *pcurchild = T->firstChild;//先访问根的第一个孩子
		while(pcurchild != NULL)
		{
			inOrderTraverse(pcurchild);
			pcurchild = pcurchild->nextSibling; //根的下一个孩子
		}
		//根的孩子全部访问完后，访问根和森林中的下一棵
		printf("%d ", T->data);
		inOrderTraverse(T->nextSibling)


	}
}

int main()
{

}
