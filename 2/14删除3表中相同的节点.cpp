#include <stdio.h>
#include <malloc.h>
/*题目：
	已知La，Lb，Lc，是3个链表。且已经初始化，其元素按递增顺序排序，每个表中无重复数据
	设计算法在Lc表中删除同时出现在La和Lb中的所有元素
*/
/*算法思想：
	每次在La和Lb中找到相同的节点，然后在Lc中查找该相同节点，如果Lc中存在该相同节点，进行删除
	重复上述步骤，直到其中一条链搜索结束
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

void deleteElem(LinkList &L, ElemType e)
{
	//pcurA=pcurB,Lc中判断是否含有此元素，若有，执行删除。
	//1.定义Lc的删除工作指针
	LinkNode *pcurC = L->next;
	LinkNode *preC = L;

	while(pcurC != NULL && e > pcurC->data)
	{
		preC = pcurC;
		pcurC = pcurC->next;
	}
	if(pcurC->data == e)
	{
		//有此元素，执行删除(每个表中无重复数据)
		preC->next = pcurC->next;
		pcurC = pcurC->next;
	}
}

void operSim(LinkList La, LinkList Lb, LinkList &Lc)
{
	//1.获得La，Lb的数据节点
	LinkNode *pcurA = La->next;
	LinkNode *pcurB = Lb->next;



	while(pcurA && pcurB)
	{
		//2.移动数据小的一方
		if(pcurA->data < pcurB->data)
		{
			pcurA = pcurA->next;
		}
		else if(pcurA->data > pcurB->data)
		{
			pcurB = pcurB->next;
		}
		else
		{
			//3.相等,在Lc中判断是否含有此元素，若有，执行删除。pcurA和pcurB往后移动
			deleteElem(Lc, pcurA->data);
			pcurA = pcurA->next;
			pcurB = pcurB->next;
		}
	}

}


int main()
{
	ElemType enterList1[] = {1, 2, 2};
	int listlength1 = 3;
	LinkList L1 = creatLinkList(enterList1, listlength1);
	printLinkList(L1);

	ElemType enterList2[] = {1, 2, 2, 3};
	int listlength2 = 4;
	LinkList L2 = creatLinkList(enterList2, listlength2);
	printLinkList(L2);

	ElemType enterList3[] = {1, 2, 2, 3, 4};
	int listlength3 = 5;
	LinkList L3 = creatLinkList(enterList3, listlength3);
	printLinkList(L3);

	operSim(L1, L2, L3);
	printLinkList(L3);
}