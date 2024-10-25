#include <stdio.h>
#include <malloc.h>
/*题目：
	循环链表的构建（采用尾插法）
*/
/*算法思想：
	将为节点的后继从NULL改成头节点L(或者第一个数据节点)；
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
void printfLinkList(LinkList L)
{
	LinkNode *pcur = L->next;
	while(pcur!=L)
	{
		printf("%d ",pcur->data);
		pcur=pcur->next;
	}
	printf("\n");
}

int main()
{
	Elemtype list1[]={1,2,3,4,5};
	int length1 =5;
	LinkList L1 = NULL;
	creatLinkList(L1,list1,length1);
	printf("L1:");
	printfLinkList(L1);
	
}