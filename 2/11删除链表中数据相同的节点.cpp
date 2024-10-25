#include <stdio.h>
#include <malloc.h>
/*题目
	删除非递减链表中数据相同的节点(在同一个表中操作)
*/
/*算法思想
	1.定义两个工作指针，一个pcur指向当前表，一个pre指向结果表的末端
	2.pcur和pre比较
	3.相同，pcur指向pcur->next，pre不动
	4.不同pre指向pcur，pcur指向pcur->next
*/

typedef char ElemType;

typedef struct LinkNode
{
	//链表
	ElemType data;
	struct LinkNode *next;
} LinkNode, *LinkList;
//LinlList等价于LinkNode *


void tailinsert(LinkList &L, ElemType enterList[], int listlength)
{
	LinkNode *pTail = L; //链表为空时，尾节点指向头节点
	int i = 0;
	while(i < listlength)
	{
		LinkNode *p = (LinkNode*)malloc(sizeof(LinkNode));
		p->data = enterList[i];
		//尾插
		p->next = NULL;//p->next=pTail->next;
		pTail->next = p;
		pTail = p;
		i++;
	}
}
//创建链表
LinkList creatLinkList(ElemType enterList[], int listlength)
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
		printf("%c ", p->data);
		p = p->next;
	}
	printf("\n");
}

void deleteSim(LinkList &L)
{
	//1.定义两个工作指针，
	//一个pcur指向当前表，一个pre指向结果表的末端
	LinkNode *pCur = L->next;
	LinkNode *pre = L;
	while(pCur != NULL)
	{
		//2.pcur和pre比较
		if(pre != L && pre->data == pCur->data) //2.pcur和pre比较
		{
			//3.相同，pcur指向pcur->next，pre不动
			pCur = pCur->next;
		}
		else
		{
			//4.不同pre指向pcur，pcur指向pcur->next
			pre->next=pCur;
			pre=pCur;
			pCur = pCur->next;
		}
	}
}


int main()
{
	ElemType enterList[] = {'a', 'b', 'b', 'b', 'c'};
	int listlength = 5;
	LinkList L = creatLinkList(enterList, 5);
	printLinkList(L);
	deleteSim(L);
	printLinkList(L);
}