#include <stdio.h>
#include <malloc.h>
/*题目：
	带头结点的单链表的数值按递增顺序排列，删除链表中大于min且小于max的元素
*/
/*算法思想：
	遍历每对前驱后继，若后继位于范围内，执行删除
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

void deleteElemRangeMinMax(ElemType min, ElemType max, LinkList &L)
{
	LinkNode *pre = L;
	LinkNode *pcur = L->next;

	while(pcur != NULL)
	{
		if(min < pcur->data && pcur->data < max)
		{
			//删除
			pre->next = pcur->next;
			pcur = pcur->next;
		}
		else if(pcur->data <= min)
		{//注意=号
			pre = pcur;
			pcur = pcur->next;
		}
		else if(pcur->data >= max)
		{//注意=号
			break;
		}
	}
}

int main()
{
	ElemType enterList1[] = {1, 2};
	int listlength1 = 2;
	LinkList L1 = creatLinkList(enterList1, listlength1);
	printf("L1:");
	printLinkList(L1);


	ElemType enterList2[] = {1, 2, 3, 4, 5, 6};
	int listlength2 = 6;
	LinkList L2 = creatLinkList(enterList2, listlength2);
	printf("L2:");
	printLinkList(L2);

	deleteElemRangeMinMax(2, 5, L2);
	printLinkList(L2);
}