#include <stdio.h>
#include <malloc.h>
/*题目：
	对链表使用冒泡排序（从小到大）
*/
/*算法思想：
	交换数据域，若没有发生交换，则排序完成
	冒泡排序，每一次都是较大的落在相应位置
	//注意冒泡排序时间复杂度为O(n²)，每次从头开始比较
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

void paoSort(LinkList &L)
{
	//注意冒泡排序时间复杂度为O(n²)，
	while(1)
	{
		//每次从头开始比较
		LinkNode *pre = L;
		LinkNode *pcur = L->next;
		int ischange = 0;

		while(pcur != NULL)
		{
			if(pre != L && pre->data > pcur->data)
			{
				ElemType tmp = pre->data;
				pre->data = pcur->data;
				pcur->data = tmp;
				ischange = 1;
			}
			pre = pcur;
			pcur = pcur->next;
		}
		if(ischange==0)
		{
			break;
		}
	}


}

int main()
{
	ElemType enterList1[] = {1, 2};
	int listlength1 = 2;
	LinkList L1 = creatLinkList(enterList1, listlength1);
	printf("L1:");
	printLinkList(L1);


	ElemType enterList2[] = {6,5,4,3,2,1};
	int listlength2 = 6;
	LinkList L2 = creatLinkList(enterList2, listlength2);
	printf("L2:");
	printLinkList(L2);

	paoSort(L2);
	printf("L2:");
	printLinkList(L2);
}