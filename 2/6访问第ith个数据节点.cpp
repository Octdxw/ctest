#include <stdio.h>
#include <malloc.h>
/*题目
	访问带头节点链表中第i个数据节点
*/
/*算法思想
	可以将头节点看成第0个节点
	引入计数器count记录访问到第几个数据节点
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
//访问带头节点链表中第i个数据节点
LinkNode *visitIth(LinkList L, int ith)
{
	LinkNode *p = L;
	int count = 0;//计数
	while (p->next != NULL)
	{
		if (count == ith)
		{
			return p;
		}
		//当前节点不是第ith个节点，继续往后访问
		p = p->next;
		count++;
	}
	//while循环执行完也没找到第ith个节点
	return NULL;
}

int main()
{
	int enterList[] = {1, 2, 3, 4, 100};
	int listlength = 5;
	LinkList L = creatLinkList(enterList, 5);
	printLinkList(L);
	LinkNode *p = visitIth(L, 2);
	if (p != NULL)
	{
		printf("%d\n", p->data);
	}
	else
	{
		printf("不存在\n");
	}
}