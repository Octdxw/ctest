#include <stdio.h>
#include <malloc.h>
/*题目
	查找带头结点链表倒数第m个位置的节点并输出该节点
*/
/*算法思想
	本题不知道一共有多少个节点
	采用相对位移法
	1.pCur指向第m+1个数据节点
	2.pNode指向第一个数据节点
	3.都往后移动，当pCur指向空节点时，pNode刚好指向倒数第m个节点
*/

typedef int ElemType;

typedef struct LinkNode
{
	//链表
	ElemType data;
	struct LinkNode *next;
} LinkNode, *LinkList;
//LinlList等价于LinkNode *


void tailinsert(LinkList &L, int enterList[], int listlength)
{
	LinkNode *pTail = L; //链表为空时，尾节点指向头节点
	int i = 0;
	while(i < listlength)
	{
		LinkNode *p = (LinkNode*)malloc(sizeof(LinkNode));
		p->data = enterList[i];
		//尾插
		p->next = pTail->next;//p->next=NULL;
		pTail->next = p;
		pTail = p;
		i++;
	}
}
//创建链表
LinkList creatLinkList(int enterList[], int listlength)
{
	//创建头节点
	LinkNode *L = NULL;
	L = (LinkNode *)malloc(sizeof(LinkNode));
	L->next = NULL; //头节点的后继为空，当前为空链表
	tailinsert(L, enterList, listlength); //尾插法
	return L;
}
//输出链表的数据
void printLinkList(LinkList L)
{
	LinkNode *p = L->next; //p指向L的第一个数据节点
	printf("L:");
	while(p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

void getData(int m, LinkList L)
{
	//pCur指向第m+1个数据节点
	LinkNode *pCur = L->next;
	int count = 1;
	while(pCur != NULL)
	{
		if(count == m + 1) //找到第m+1个数据节点
		{
			break;
		}
		pCur = pCur->next; //没找到，往后找
		count++;
	}
	LinkNode *pNode = L->next;//pNode指向第1个数据节点
	while(pCur != NULL)//依次往后移动使pCur指向空节点，此时pNode为倒数第m个节点
	{
		pCur = pCur->next;
		pNode = pNode->next;
	}
	printf("%d", pNode->data);
}

int main()
{
	int enterList[] = {1, 2, 3, 4, 100};
	int listlength = 5;
	LinkList L = creatLinkList(enterList, 5);
	printLinkList(L);
	getData(2,L);
}