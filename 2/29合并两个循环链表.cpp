#include <stdio.h>
#include <malloc.h>
/*题目：
	已知La和Lb分别为两个循环单链表的头节点，m和n分别为La和Lb中数据节点的个数，
	设计时间复杂度最小的算法将两个链表合并成一个带头节点的循环单链表
*/
/*算法思想：
	将短链中的节点插入到长链中，采用头插法
*/
typedef int Elemtype;
typedef struct LinkNode
{
	Elemtype data;
	struct LinkNode *next;
} LinkNode, *LinkList;
//LinlList等价于LinkNode *

//尾插法创建循环链表
void TailInsert(LinkList &L, Elemtype list[], int length)
{
	int i = 0;
	LinkNode *pTail = L;
	while(i < length)
	{
		LinkNode *pnode = (LinkNode *)malloc(sizeof(LinkNode));
		pnode->data = list[i];
		i++;
		//尾插
		pnode->next = pTail->next; //注意这里是pTail->next，不是L->next
		pTail->next = pnode;
		pTail = pnode;
	}
}
void TailInsert2(LinkList &L, Elemtype list[], int length)
{
	int i = 0;
	LinkNode *pTail = L;
	while(i < length)
	{
		LinkNode *pnode = (LinkNode *)malloc(sizeof(LinkNode));
		pnode->data = list[i];
		i++;
		//尾插
		pnode->next = pTail->next; //注意这里是pTail->next，不是L->next
		pTail->next = pnode;
		pTail = pnode;
	}
	L = pTail; //L指向尾节点
}

//循环链表的构建（采用尾插法）
void creatLinkList(LinkList &L, Elemtype list[], int length)
{
	L = (LinkNode *)malloc(sizeof(LinkNode));//头节点
	L->next = L; //构成循环
	TailInsert2(L, list, length);
}

//打印
void printfLinkListWithHead(LinkList L)
{
	LinkNode *pcur = L->next;
	while(pcur != L)
	{
		printf("%d ", pcur->data);
		pcur = pcur->next;
	}
	printf("\n");
}
void printfLinkListNoHead(LinkList L)
{
	printf("%d ", L->data);
	LinkNode *pcur = L->next;
	while(pcur != L)
	{
		printf("%d ", pcur->data);
		pcur = pcur->next;
	}
	printf("\n");
}

void creatSingleLinkList(LinkList &L, Elemtype list[], int length)
{
	//创建单链表
	L = (LinkNode *)malloc(sizeof(LinkNode));//头节点
	L->next = NULL; //构成循环
	TailInsert(L, list, length);
}
void printfSingleLinkListWithHead(LinkList L)
{
	//打印单链表
	LinkNode *pcur = L->next;
	while(pcur != NULL)
	{
		printf("%d ", pcur->data);
		pcur = pcur->next;
	}
	printf("\n");
}

void combine1(LinkList &La, LinkList &Lb, int n, int m)
{
	//L指向头节点版
	LinkNode *pShort = NULL;
	LinkNode *pLong = NULL;
	if(n > m)
	{
		pShort = Lb;
		pLong = La;
	}
	else
	{
		pShort = La;
		pLong = Lb;
	}
	LinkNode *pcur = pShort->next;
	while(pcur != pShort)
	{
		LinkNode *pnode = pcur;
		pcur = pcur->next;
		//头插
		pnode->next = pLong->next;
		pLong->next = pnode;
	}
}
void combine2(LinkList &Ta, LinkList &Tb)
{
	//L指向尾节点版
	LinkNode *pHeadLa = Ta->next; //保存Ta的头节点
	LinkNode *pHeadLb = Tb->next; //保存Tb的头节点
	
	Ta->next = pHeadLb->next; //La的尾节点指向Lb的第一个数据节点
	Tb->next = pHeadLa; //Lb的尾节点指向La的头节点

	Ta = Tb; //修改La的尾节点指向Lb的尾节点
}


int main()
{
	Elemtype list1[] = {1, 2, 3, 4, 5};
	int length1 = 5;
	LinkList L1 = NULL;
	creatLinkList(L1, list1, length1);
	printf("L1:");
	//printfLinkListWithHead(L1);
	printfLinkListWithHead(L1->next);

	Elemtype list2[] = {1, 2, 3};
	int length2 = 3;
	LinkList L2 = NULL;
	creatLinkList(L2, list2, length2);
	printf("L2:");
//	printfLinkListWithHead(L2);
	printfLinkListWithHead(L2->next);

	//combine1(L1, L2, 5, 3);
	combine2(L1, L2);
	printf("L1:");
//	printfLinkListWithHead(L1);
	printfLinkListWithHead(L1->next);



}