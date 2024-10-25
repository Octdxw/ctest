#include <stdio.h>
#include <malloc.h>
/*题目：
	设计算法将不带头节点的循环单链表中节点p的直接前驱删除
*/
/*算法思想：
	pre指向p，从p出发，沿着循环链表走，
	用pcur记录后继，若pcur->next==p,则找到p的前驱，然后删除
*/
typedef int Elemtype; 
typedef struct LinkNode
{
	Elemtype data;
	struct LinkNode *next;
}LinkNode,*LinkList;
//LinlList等价于LinkNode *

//尾插法
void TailInsert(LinkList &L,Elemtype list[],int length)
{
	int i = 0;
	LinkNode *pTail=L; 
	while(i<length)
	{
		LinkNode *pnode = (LinkNode *)malloc(sizeof(LinkNode));
		pnode->data=list[i];
		i++;
		//尾插
		pnode->next=pTail->next;//注意这里是pTail->next，不是L->next
		pTail->next=pnode;
		pTail=pnode;
	}
}

//循环链表的构建（采用尾插法）
void creatLinkList(LinkList &L,Elemtype list[],int length)
{
	L = (LinkNode *)malloc(sizeof(LinkNode));//头节点
	L->next=L;//构成循环
	TailInsert(L,list,length);
}

//打印
void printfLinkListWithHead(LinkList L)
{
	LinkNode *pcur = L->next;
	while(pcur!=L)
	{
		printf("%d ",pcur->data);
		pcur=pcur->next;
	}
	printf("\n");
}
void printfLinkListNoHead(LinkList L)
{
	printf("%d ",L->data);
	LinkNode *pcur = L->next;
	while(pcur!=L)
	{
		printf("%d ",pcur->data);
		pcur=pcur->next;
	}
	printf("\n");
}

void delpPrior(LinkNode *p)
{
	LinkNode *pre = p;
	LinkNode *pcur = p->next;
	while(pcur->next!=p)
	{
		pre=pre->next;
		pcur=pcur->next;
	}
	//找到p的前驱pcur,删除pcur
	pre->next=p;
}

int main()
{
	Elemtype list1[]={1,2,3,4,5};
	int length1 =5;
	LinkList L1 = NULL;
	creatLinkList(L1,list1,length1);
	
	L1->data=0;
	printf("L1:");
	printfLinkListNoHead(L1);
	
	LinkNode *p=L1->next;//p->data=1;
	delpPrior(p);
	printf("L1:");
	printfLinkListNoHead(p);


	
}