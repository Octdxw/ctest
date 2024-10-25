#include <stdio.h>
#include <malloc.h>
/*题目
	设单链表头指针为L，节点数据域为字符。
	设计时间复杂度最低的算法判断前n/2个字符是否与后n/2个字符
	依次相同
*/
/*算法思想
	s指向链表的前半部分的第一个节点
	t指向链表的后半部分的第一个节点
	从前往后依次匹配s和t的数据，
	如果不匹配，则不相同
	如果匹配，直到t为空为止，则相同
*/

typedef char ElemType;

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
		printf("%c ", p->data);
		p = p->next;
	}
	printf("\n");
}

int isSym(LinkList L, int n)
{
	LinkNode *pCur = L->next;
	int count = 1;
	while(pCur != NULL)
	{
		if(count == n / 2)//前一半的最后一个数据节点
		{
			break;
		}
		pCur = pCur->next;
		count++;
	}
	LinkNode *pLast = NULL;
	if(n % 2 != 0)//n为奇数
	{
		pLast = pCur->next->next;
	}
	else//n为偶数
	{
		pLast = pCur->next;
	}
	pCur = L->next;//前一半的第一个数据节点
	while(pLast != NULL)
	{
		if(pCur->data != pLast->data)//不匹配
		{
			return 0;
		}
		pCur = pCur->next;
		pLast = pLast->next;
	}
	return 1;

}


int main()
{
	ElemType enterList[] = {'a', 'b', 'c', 'a', 'b'};
	int listlength = 5;
	LinkList L = creatLinkList(enterList, 5);
	printLinkList(L);
	int res = isSym(L, 5);
	printf("res:%d\n", res);
}