#include <stdio.h>
#include <malloc.h>
/*题目
	查找链表中的最大值
*/
/*算法思想
	在顺序子链中递归查找最大值
	或利用循环求最大值
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
#define INF_MIN -99999
//递归求最大值
ElemType getMAx(LinkList pList)
{
	if(pList == NULL)
	{
		//L的数据节点为空
		return INF_MIN;
	}
	ElemType t = getMAx(pList->next); //用t记录子链中的最大值
	if(pList->data > t)
	{
		return pList->data;
	}
	else
	{
		return t;
	}
}

//ElemType getMax(LinkList pCur)
//{
//
//	if(pCur == NULL)
//	{
//		//L的数据节点为空
//		return INF_MIN;
//	}
//	ElemType temp = getMax(pCur->next); //用t记录子链中的最大值
//	return pCur->data > temp ? pCur->data : temp;
//}
//循环求最大值
ElemType getMax2(LinkList L)
{
	LinkNode *p = L->next;
	int max = p->data; //让max为第一个数据节点的值
	p = p->next; //p指向第二个数据节点
	while(p != NULL)
	{
		if(p->data > max)
		{
			max = p->data;
		}
		p = p->next;
	}
	return max;
}

int main()
{
	int enterList[] = {1, 2, 3, 4, 100};
	int listlength = 5;
	LinkList L = creatLinkList(enterList, 5);
	printLinkList(L);
	int max = getMAx(L->next);
	printf("%d\n", max);
	int max2 = getMax2(L);
	printf("%d\n", max2);
}