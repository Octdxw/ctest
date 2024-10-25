#include <stdio.h>
#include <malloc.h>
/*题目：
	判断La是否为Lb的子链
*/
/*算法思想：
	startLb为每轮匹配的起始位置，pMoceLb为工作指针
	pMoveLa为工作指针
	若循环结束（purLa并且purLb为NULL），全部的数据节点都匹配成功(此时pMoveLa为NLULL)，则为子链，否则不是
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

int isSubLink(LinkList Lb,LinkList La)
{
	LinkNode *startLb = Lb->next;
	LinkNode *pMoveLb = startLb;
	LinkNode *pMoveLa=La->next;
	
	while(pMoveLa !=NULL &&pMoveLb!=NULL)
	{
		if(pMoveLa->data == pMoveLb->data)
		{
			pMoveLa=pMoveLa->next;
			pMoveLb=pMoveLb->next;
		}
		else
		{
			startLb=startLb->next;
			pMoveLb=startLb;
			pMoveLa=La->next;
		}
	}
	if(pMoveLa==NULL)
	{
		return 1;
	}
	return 0;
}

int main()
{
	ElemType enterList1[] = {4, 3, 4, 1}; //构建L1
	int listlength1 = 4;
	LinkList L1 = creatLinkList(enterList1, listlength1);
	printf("L1:");
	printLinkList(L1);

	ElemType enterList2[] = {3, 4, 2}; //构建L2
	int listlength2 = 3;
	LinkList L2 = creatLinkList(enterList2, listlength2);
	printf("L2:");
	printLinkList(L2);
	
	printf("%d",isSubLink(L1,L2));	
	

}