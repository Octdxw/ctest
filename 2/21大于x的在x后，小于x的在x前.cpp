#include <stdio.h>
#include <malloc.h>
/*题目：
	将小于x的元素都排在其前面，所有大于x的元素都排在其后面
*/
/*算法思想：
	创建空表，插入人工制造的x节点，用preX记录人工制造x的前驱
	大于x的采用尾插
	等于x，头插，插在x的前面
	小于x的采用头插，头插在L后面
	插入结束，删除人工制造的x节点
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

void orderX(LinkList &L, int x)
{
	//对L进行操作
	LinkNode *pcur = L->next;
	L->next = NULL;
	//创建节点X
	LinkNode *pX = (LinkNode *)malloc(sizeof(LinkNode));
	pX->data = x;
	pX->next = NULL;
	//插入节点X，使其成为尾节点，并记录其前驱
	L->next = pX;
	LinkNode *pTail = pX;
	LinkNode *preX = L;

	while(pcur != NULL)
	{
		LinkNode *pnode = pcur; //工作指针
		pcur = pcur->next;

		if(pnode->data > x)
		{
			//尾插
			pnode->next = NULL;
			pTail->next = pnode;
			pTail = pnode;
		}
		else if(pnode->data == x)
		{
			//头插，插在x的前面
			pnode->next = pX;
			preX->next = pnode;
			preX = pnode;
		}
		else
		{
			//小于x,头插在L后面
			pnode->next = L->next;
			L->next = pnode;
			if(preX == L)
			{
				preX = pnode;
			}
		}
	}
	//删除人工制造的x
	preX->next = pX->next;
}

int main()
{
	ElemType enterList1[] = {4, 3, 5, 1,2}; //构建L1
	int listlength1 = 5;
	LinkList L1 = creatLinkList(enterList1, listlength1);
	printf("L1:");
	printLinkList(L1);

	orderX(L1, 3);
	printLinkList(L1);

//	ElemType enterList2[] = {3, 4, 2}; //构建L2
//	int listlength2 = 3;
//	LinkList L2 = creatLinkList(enterList2, listlength2);
//	printf("L2:");
//	printLinkList(L2);
//
//	printf("%d", isSubLink(L1, L2));


}