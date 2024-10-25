#include <stdio.h>
#include <malloc.h>
/*题目：
	循环链表左移K个节点（不带头节点的更方便）
*/
/*算法思想：
	左移K，即让第k+1个节点变成第一个数据节点，即让L指向第k+1个节点
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

int moveK(LinkList &L,int k)//不带头节点
{
	if(L==NULL)
	{
		return 0;
	}
	int cnt =1;
	LinkNode *pcur=L;//第一个数据节点
	while(cnt<=k)
	{
		cnt++;
		pcur=pcur->next;
		L=pcur;
	}
	return 1;
}

int main()
{
	Elemtype list1[]={1,2,3,4,5};
	int length1 =5;
	LinkList L1 = NULL;
	creatLinkList(L1,list1,length1);
	
	L1->data=0;
	printf("L1:");
	printf("%d ",L1->data);
	printfLinkList(L1);
	
	moveK(L1,1);
	printf("L1:");
	printf("%d ",L1->data);
	printfLinkList(L1);

	
}