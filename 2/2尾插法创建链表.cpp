#include <stdio.h>
#include <malloc.h>
/*题目
	尾插法创建带头结点的链表
	(不改变顺序)
*/
/*算法思想
	需要定义一个尾指针来指向链表尾
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


int main()
{
	int enterList[] = {1, 2, 3, 4, 100};
	int listlength = 5;
	LinkList L = creatLinkList(enterList, 5);
	printLinkList(L);
}