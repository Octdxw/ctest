#include <stdio.h>
#include <malloc.h>
/*题目
	在一个非递减的正整数单链表中，设计算法确定笔x小的节点数量
	例L={1,2,2,4,6},x=4,则比x小的数有2个(去除重复)
*/
/*算法思想
	遍历链表中的每一对前驱后继，如果后记中的数据大于x，则停止
	如果后继结点中的数据小于x且节点和前驱不同，计数器+1
	直到访问结束
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
	printf("L:");
	while(p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

int getLessNodes(LinkList L, int x)
{
	int count = 0;
	LinkNode *pcur = L->next;
	LinkNode *pre = L;
	while(pcur != NULL && pcur->data < x)
	{
		if(pcur->data != pre->data || pre == L)
		{
			count++;
		}
		pre = pcur;
		pcur = pcur->next;
	}
	return count;
}


int main()
{
	ElemType enterList[] = {1,2,2,3,4};
	int listlength = 5;
	LinkList L = creatLinkList(enterList, listlength);
	printLinkList(L);
	int cnt=getLessNodes(L,3);
	printf("%d\n",cnt);
}