#include <stdio.h>
#include <malloc.h>
/*题目：
	设计循环单链表中的数字，字母，其他字符拆分成3个循环链表，每个表中只包含1种类型的字符
*/
/*算法思想：
	设计3个空的子循环链表，采用头插法依次插入到对应的子链中
*/
typedef int Elemtype; 
typedef struct LinkNode
{
	Elemtype data;
	struct LinkNode *next;
}LinkNode,*LinkList;
//LinlList等价于LinkNode *

//尾插法创建循环链表
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

void insrt(LinkNode *pnode,LinkList &L)
{//头插法插入到每个子链
	pnode->next=L->next;
	L->next=pnode;
}
void creatchild(LinkList &L)
{//创建带头节点的循环子链
	L=(LinkNode *)malloc(sizeof(LinkNode));
	L->next=L;
}
void spilit(LinkNode &L)
{
	LinkList chrL = NULL;
	creatchild(chrL);
	LinkList numL=NULL;
	creatchild(numL);
	LinkList otherL=NULL;
	creatchild(otherL);
	
	LinkNode *pcur=L->next;
	while(pcur!=L)
	{
		LinkNode *pnode = pcur;
		pcur=pcur->next;
		if(pnode->data>='A'&&pnode->data<='Z' || pnode->data>='a'&&pnode->data<='z')
		{
			insrt(pnode,chrL);
		}
		else if(pnode->data>=0&&pnode<=9)
		{
			insrt(pnode,numL);
		}
		else
		{
			insrt(pnode,otherL);
		}
	}
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