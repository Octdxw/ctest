#include <stdio.h>
#include <malloc.h>
/*题目：
	设L为单链表头节点地址，其数据节点都是正整数，可能存在相同的数值节点
	设计空间复杂度最低的算法，利用直接插入排序把链表整理成有序递增的链表并删除重复节点
*/
/*算法思想：
	插入排序的时间复杂度为O(n²)
	从第一个节点开始确定其相对位置，每次从第一个节点开始查找插入位置
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

void insertSort(LinkList &L)
{
	LinkNode *pcurData = L->next;
	L->next = NULL;//占用原来的L，降低空间复杂度

	while(pcurData != NULL)
	{
		LinkNode *pnode = pcurData; //工作指针
		pcurData = pcurData->next; //往后移动

		//查找插入位置,循环结束及找到插入位置，插在pre和pcur之间
		LinkNode *pcur = L->next;//第一轮pcur=NULL
		LinkNode *pre = L;
		while(pcur != NULL)
		{
			if(pnode->data <= pcur->data)
			{
				//找到插入位置
				break;
			}
			//没找到，继续往后找
			pre = pcur;
			pcur = pcur->next;
		}
		if(pcur != NULL && pnode->data == pcur->data)
		{
			//过滤到相同的元素
			free(pnode);
		}
		else
		{
			//执行插入
			pre->next = pnode;
			pnode->next = pcur;
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


	ElemType enterList2[] = {6, 5, 4, 3, 2, 1};
	int listlength2 = 6;
	LinkList L2 = creatLinkList(enterList2, listlength2);
	printf("L2:");
	printLinkList(L2);

	insertSort(L2);
	printf("L2:");
	printLinkList(L2);
}