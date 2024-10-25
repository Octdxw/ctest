#include <stdio.h>
#include <malloc.h>
/*题目
	求链表中的节点数（不包括头节点）
*/
/*算法思想
	在顺序子链中递归求节点数
	或利用循环求节点数
*/

typedef int ElemType;

typedef struct LinkNode
{
	//链表
	ElemType data;
	struct LinkNode *next;
} LinkNode, *LinkList;
//LinlList等价于LinkNode *


void tailinsert(LinkList &L, int enterList[], int listlength)
{
	LinkNode *pTail = L; //链表为空时，尾节点指向头节点
	int i = 0;
	while(i < listlength)
	{
		LinkNode *p = (LinkNode*)malloc(sizeof(LinkNode));
		p->data = enterList[i];
		//尾插
		p->next = pTail->next;//p->next=NULL;
		pTail->next = p;
		pTail = p;
		i++;
	}
}
//创建链表
LinkList creatLinkList(int enterList[], int listlength)
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
//递归求节点数
int getNodeNum(LinkList pList)
{
	if (pList == NULL)
	{
		return 0;
	}
	return 1 + getNodeNum(pList->next);
}
//循环求链表节点数
int getNodeNum2(LinkList L)
{
	int NodeNum = 0;
	LinkNode *p = L->next;//p指向第一个数据节点
	while(p != NULL)
	{
		NodeNum++;
		p = p->next;//p指向下一个节点
	}
	return NodeNum;
}

int main()
{
	int enterList[] = {1, 2, 3, 4, 100};
	int listlength = 5;
	LinkList L = creatLinkList(enterList, 5);
	printLinkList(L);
	int NodeNum = getNodeNum(L->next);
	printf("%d\n", NodeNum);
	int NodeNum2 = getNodeNum2(L);
	printf("%d\n", NodeNum2);
}
