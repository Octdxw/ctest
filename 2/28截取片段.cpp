#include <stdio.h>
#include <malloc.h>
/*题目：
	已知L为单链表的头节点，设计算法将表中从第i到m号节点构成一个逆置的循环链表
*/
/*算法思想：
	逆置：头插法
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

//循环链表的构建（采用尾插法）
void creatLinkList(LinkList &L, Elemtype list[], int length)
{
	L = (LinkNode *)malloc(sizeof(LinkNode));//头节点
	L->next = L; //构成循环
	TailInsert(L, list, length);
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

LinkNode *getPre(int i, LinkList L)
{
	//查找单链表第i个节点的前驱
	LinkNode *pre = L;
	LinkNode *pcur = L->next;
	int cnt = 0;
	while(pcur != NULL)
	{
		cnt++;
		if(cnt == i)
		{
			break;
		}
		pre = pcur;
		pcur = pcur->next;
	}
	return pre;
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
LinkList compose(LinkList &L, int i, int m)
{
	LinkNode *preI = getPre(i, L);
	LinkNode *preM = getPre(m, L);
	LinkNode *pcur = preI->next;
	preI->next = preM->next->next; //从L中删除这一片段
	preM->next->next = NULL; //片段最后一个节点的next=Null

	LinkList rL = (LinkNode *)malloc(sizeof(LinkNode)); //构建空的循环单链表
	rL->next = rL;
	//头插法插入到rl
	
	while(pcur != NULL)
	{
		LinkNode *pnode = pcur;
		pcur = pcur->next;
		//头插
		pnode->next = rL->next;
		rL->next = pnode;
	}
	return rL;
}


int main()
{
	Elemtype list1[] = {1, 2, 3, 4, 5};
	int length1 = 5;
	LinkList L1 = NULL;
	creatSingleLinkList(L1, list1, length1);
	printf("L1:");
	printfSingleLinkListWithHead(L1);
	
	LinkList rL= compose(L1,1,3);
	printf("rL:");
	printfLinkListWithHead(rL);
	
	printf("L1:");
	printfSingleLinkListWithHead(L1);
	




}