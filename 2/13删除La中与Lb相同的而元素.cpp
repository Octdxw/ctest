#include <stdio.h>
#include <malloc.h>
/*题目：
	删除非递减单链表La与非递减单链表Lb相同的元素
*/
/*算法思想：
	pcurA为La的工作指针，preA为La的拼接指针
	pcurB为Lb的工作指针
	比较pcurA和pcurB
	当pcurA小时，preA和pcurA往后移动
	当pcurB小时，pcurB往后移动
	相等时，La执行删除，即preA->next=pcurA->next,pcurA=pcurA->next;
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
	printf("L:");
	while(p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

void deleteSim(LinkList &La, LinkList Lb)
{
	LinkNode *preA = La;
	LinkNode *pcurA = La->next;
	LinkNode *pcurB = Lb->next;
	
	while(pcurA!=NULL &&pcurB!=NULL)
	{
		if(pcurA->data<pcurB->data)
		{
			preA=pcurA;
			pcurA=pcurA->next;
		}
		else if(pcurA->data>pcurB->data)
		{
			pcurB=pcurB->next;
		}
		else
		{
			preA->next=pcurA->next;
			pcurA=pcurA->next;
		}
	}
}


int main()
{
	ElemType enterList1[] = {1, 2, 2, 3, 4};
	int listlength1 = 5;
	LinkList L1 = creatLinkList(enterList1, listlength1);
	printLinkList(L1);
	ElemType enterList2[] = {1, 2, 2, 3};
	int listlength2 = 4;
	LinkList L2 = creatLinkList(enterList2, listlength2);
	printLinkList(L2);
	
	deleteSim(L1,L2);
	printLinkList(L1);
}