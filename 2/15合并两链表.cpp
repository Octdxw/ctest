#include <stdio.h>
#include <malloc.h>
/*题目：
	La和Lb按值非递减，归并La和Lb，获得新的Lc，使得Lc也按值非递减且不含重复元素，并占用原来La的空间
*/
/*算法思想：
	最小值法，尾插法
*/

typedef int ElemType;

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
	while(p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

void TailInsert(LinkNode *&pTail, LinkNode *&pnode)
{
	//检查是否和尾节点相同
	if(pTail->data != pnode->data)
	{

		pTail->next = pnode;
		pTail = pnode;
		pTail->next = NULL;
	}
}

void merge(LinkList &La, LinkList Lb, LinkList &Lc)
{
	LinkNode *pcurA = La->next;
	LinkNode *pcurB = Lb->next;
	//占用La
	Lc = La;
	Lc->next = NULL;
	La = NULL;
//	free(Lb);
//	Lb = NULL;
	//定义Lc的尾节点
	LinkNode *pTailC = Lc;

	while(pcurA != NULL && pcurB != NULL)
	{

		LinkNode *pnode = NULL;
		if(pcurA->data < pcurB->data)
		{
			//pcurA小，往后移
			pnode = pcurA;
			pcurA = pcurA->next;
		}
		else
		{
			//pcurB小，往后移
			pnode = pcurB;
			pcurB = pcurB->next;
		}
		//执行尾插
		TailInsert(pTailC, pnode);
	}

	while(pcurA != NULL)
	{
		//此时pcurB=NULL
		LinkNode *pnode = pcurA;
		pcurA = pcurA->next;
		TailInsert(pTailC, pnode);
	}
	while(pcurB != NULL)
	{
		//此时pcurA=NULL
		LinkNode *pnode = pcurB;
		pcurB = pcurB->next;
		TailInsert(pTailC, pnode);
	}
}

int main()
{
	ElemType enterList1[] = {1, 2};
	int listlength1 = 2;
	LinkList L1 = creatLinkList(enterList1, listlength1);
	printf("L1:");
	printLinkList(L1);


	ElemType enterList2[] = {1, 2, 3};
	int listlength2 = 3;
	LinkList L2 = creatLinkList(enterList2, listlength2);
	printf("L2:");
	printLinkList(L2);

	LinkList L3 = NULL;
	merge(L1, L2, L3);
	printf("L3:");
	printLinkList(L3);
}