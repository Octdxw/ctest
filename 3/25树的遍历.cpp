#include <stdio.h>
#include <malloc.h>
/*
	题目：
		树的遍历算法，先根，后根遍历
*/
/*
	算法思想：
	树只有根和子树，所以分为先根，后根遍历
*/

typedef int Elemtype;
typedef struct CSTNode //child,sibling
{
	Elemtype data;
	struct CSTNode *firstChild;
	struct CSTNode *nextSibling; 
}CSTNode,*CSTree;
//CSTree等价于CSTNOde *


void preOrderTraverse(CSTree T) //先根遍历
{
	if(T!=NULL)
	{
		printf("%d ",T->data);//先访问根
		CSTNode *pcurchild=T->firstChild;//访问孩子
		while(pcurchild!=NULL)
		{
			preOrderTraverse(pcurchild);//访问孩子左子树，
			//孩子子树遍历完后，访问下一个兄弟
			preOrderTraverse(pcurchild->nextSibling);
		}
	}
}

void postOrderTraverse(CSTree T) //后根遍历
{
	if(T!=NULL)
	{
		CSTNode *pcurchild=T->firstChild;//先访问孩子
		while(pcurchild!=NULL)
		{
			postOrderTraverse(pcurchild);//访问孩子左子树
			//访问完孩子左子树后，访问下一个兄弟
			postOrderTraverse(pcurchild->nextSibling);
		}
		printf("%d ",T->data);//访问根
	}
}

int main()
{

}
