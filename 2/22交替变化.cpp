#include <stdio.h>
#include <malloc.h>
/*题目：
	长度为n的单链表L(L1,L2,...Ln),给出时间复杂度和空间复杂度最小的算法
	将L转化成LT(L1,Ln,L2,Ln-1,L3,Ln-2,...)
*/
/*算法思想：
	将L分为前半段Ltop(L1,...Ln/2)和后半段Lbottom(Ln/2+1,...,Ln),将后一半逆置(头插法)，
	依次取Ltop和Lbottom的节点将每一对节点插入到L中，
	重复，直到其中一条链为空，将另一条的剩余节点插入到L
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

void convertLinkList(LinkList &L, int length)
{
	int cnt = 0 ;
	LinkNode *pcur = L->next;
	//取前一半
	while(pcur != NULL)
	{
		cnt++;
		if(cnt == length / 2)
		{
			break;
		}
		pcur = pcur->next;
	}
	
	LinkNode *ptop = L->next;
	LinkNode *pbottom = pcur->next;//后一半
	pcur->next = NULL; //前一半的最后一个节点的后继为NULL
	L->next = NULL; //在L上进行初始化操作
	//逆置后一半
	while(pbottom != NULL)
	{
		LinkNode *pnode = pbottom;
		pbottom = pbottom->next;
		//头插在L后面
		pnode->next = L->next;//注意此处不为NULL
		L->next = pnode;
	}
	pbottom = L->next; //后一半
	//交替插入L,尾插
	L->next = NULL;
	LinkNode *ptail = L;//L为头节点，空链表：L=ptail;
	while(ptop != NULL && pbottom != NULL)
	{
		
		//前一半交替插入
		LinkNode *pnode = ptop;
		ptop = ptop->next;
		//尾插
		pnode->next = NULL;
		ptail->next = pnode;
		ptail = pnode;
	
		//后一半交替插入
		pnode = pbottom;
		pbottom = pbottom->next;
		//尾插
		pnode->next = NULL;
		ptail->next = pnode;
		ptail = pnode;
		
	}
	if(ptop != NULL)
	{
		ptail->next = ptop;
	}
	if(pbottom != NULL)
	{
		ptail->next = pbottom;
	}
}

int main()
{
	ElemType enterList1[] = {4, 3, 5, 1, 2}; //构建L1
	int listlength1 = 5;
	LinkList L1 = creatLinkList(enterList1, listlength1);
	printf("L1:");
	printLinkList(L1);

	convertLinkList(L1, 5);
	printf("L1:");
	printLinkList(L1);

//	ElemType enterList2[] = {3, 4, 2}; //构建L2
//	int listlength2 = 3;
//	LinkList L2 = creatLinkList(enterList2, listlength2);
//	printf("L2:");
//	printLinkList(L2);
//
//	printf("%d", isSubLink(L1, L2));


}