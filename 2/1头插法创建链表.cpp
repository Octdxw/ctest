#include <stdio.h>
#include <malloc.h>
/*题目
	头插法创建带头节点的链表
	（可将原有的序列逆置）
*/
/*算法思想

*/

typedef int ElemType;

typedef struct LinkNode
{
	//链表
	ElemType data;
	struct LinkNode *next;
} LinkNode, *LinkList;
//头插法
void headinsert(LinkList &L, int enterList[], int listlength)
{
	int i = 0;
	while(i < listlength)
	{
		LinkNode *p = (LinkNode*)malloc(sizeof(LinkNode));
		p->data = enterList[i];
		//头插
		p->next = L->next;
		L->next = p;
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
	headinsert(L, enterList, listlength); //头插法
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



int main()
{
	int enterList[] = {1, 2, 3, 4, 100};
	int listlength = 5;
	LinkList L = creatLinkList(enterList, 5);
	printLinkList(L);
}
