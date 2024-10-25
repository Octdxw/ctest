#include <stdio.h>
#include <malloc.h>
/*题目：
	查找公共后缀的起始位置
*/
/*算法思想：
	长的链表长度为b，短的链表长度为a，长的链表先移动b-a个数据节点，再同时访问La，Lb中的节点
	如果访问的两个链中数据节点地址值相同，则找到公共节点
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

int getLength(LinkList L)
{
	//查询链表长度
	int length = 0;
	LinkNode *pnode = L->next;
	while(pnode != NULL)
	{
		length++;
		pnode = pnode->next;
	}
	return length;
}

LinkNode *getCommomNode(LinkList La, LinkList Lb)
{
	int lengthLa = getLength(La);//获得La的长度
	int lengthLb = getLength(Lb);//获得Lb的长度
	LinkNode *pLong = NULL;
	LinkNode *pShort = NULL;
	int cnt = 0;
	if(lengthLa < lengthLb)
	{
		//pLong指向长链表
		pLong = Lb->next;
		pShort = La->next;
		cnt = lengthLb - lengthLa;
	}
	else
	{
		//pLong指向长链表
		pLong = La->next;
		pShort = Lb->next;
		cnt = lengthLa - lengthLb;
	}
	int i = 0;
	while(pLong != NULL)
	{
		//长的链表先移动
		i++;
		if(i == cnt)
		{
			break;
		}
		pLong = pLong->next;
	}
	pLong = pLong->next;

	while(pLong != pShort)
	{
		//寻找共享的后缀
		pLong = pLong->next;
		pShort = pShort->next;

	}
	return pLong;
}

int main()
{
	ElemType enterList1[] = {4, 3, 4, 1}; //构建L1
	int listlength1 = 4;
	LinkList L1 = creatLinkList(enterList1, listlength1);
	printf("L1:");
	printLinkList(L1);

	ElemType enterList2[] = {3, 4, 1}; //构建L2
	int listlength2 = 3;
	LinkList L2 = creatLinkList(enterList2, listlength2);
	printf("L2:");
	printLinkList(L2);
	
	L1->next->next = L2->next;
	
	getCommomNode(L1,L2);
	printf("%d",getCommomNode(L1,L2)->data);
}