#include <stdio.h>
#include <malloc.h>
/*题目
	已知指针La和Lb分别指向两个无头节点的单链表
	编写函数完成从La中删除第j个元素开始的共len个元素
	并将这len个元素插入到Lb中第j个元素之前
*/
/*算法思想
	1.链表中加入头节点oper()
	2.查找第j个节点的前驱，查找第j+len的前驱getpre()
	3.执行操作
	4.删除头节点
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

LinkNode *getpre(LinkList L, int m)
{
	LinkNode *pre = L;
	LinkNode *p = L->next;
	int count = 1; //计数器
	while(p != NULL)
	{
		if(count == m)//找到第m个节点
		{
			return pre;//返回第m个节点的前驱
		}
		p = p->next;//没找到第m个节点，继续往后找
		pre = pre->next;
		count++;
	}
	return NULL;//while循环结束也没找到，返回空
}

void oper(LinkList &La, LinkList &Lb, int j, int len)
{
	//La增加头节点
	LinkNode *pLa = (LinkNode *)malloc(sizeof(LinkNode));
	pLa->next = La;
	La = pLa;
	//Lb增加头节点
	LinkNode *pLb = (LinkNode *)malloc(sizeof(LinkNode));
	pLb->next = Lb;
	Lb = pLb;

	LinkNode *prejLa = getpre(La, j);//得到La第j个节点的前驱
	LinkNode *prejlenLa = getpre(La, j + len);//得到La第j+len个节点的前驱

	LinkNode * prejLb = getpre(Lb, j); //得到Lb第j个节点的前驱
	//操作
	prejlenLa->next = prejLb->next;
	prejLb->next = prejLa->next;
	prejLa->next = prejlenLa->next;

	printLinkList(La);
	printLinkList(Lb);
	//去掉头节点
	La = La->next;
	Lb = Lb->next;

}

int main()
{
	int enterList1[] = {1, 2, 3, 4, 100};
	int listlength1 = 5;
	LinkList La = creatLinkList(enterList1, 5);
	printLinkList(La);
	La = La->next;

	int enterList2[] = {5, 6, 7, 8, 101};
	int listlength2 = 5;
	LinkList Lb = creatLinkList(enterList2, 5);
	printLinkList(Lb);
	Lb = Lb->next;

	oper(La, Lb, 2, 3);
}