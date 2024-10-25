#include <stdio.h>
#include <malloc.h>
/*题目
	求链表所有元素的平均值
*/
/*算法思想
	在顺序子链中递归求平均值:d1/n +d2/n +...+dn/n,n为数据节点数
	或利用循环求总和，然后求平均值
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

//递归求节点数
int getNodeNum(LinkList pList)
{
	if (pList == NULL)
	{
		return 0;
	}
	return 1 + getNodeNum(pList->next);
}
//递归求平均值
double getAvg(LinkList pList, int num)
{
	if (pList == NULL)
	{
		return 0;
	}
	return (double)pList->data / num + getAvg(pList->next, num);
}
//循环求平均值
double getAvg2(LinkList L)
{
	LinkNode *p = L->next;
	int sum = 0;
	int num = 0;
	while(p != NULL)
	{
		sum = sum + p->data;
		num++;
		p=p->next;
	}
	return sum / num;
}

int main()
{
	int enterList[] = {1, 2, 3, 4, 100};
	int listlength = 5;
	LinkList L = creatLinkList(enterList, 5);
	printLinkList(L);
	int num = getNodeNum(L->next);
	printf("num：%d\n", num);
	double Avg = getAvg(L->next, num);
	printf("Avg:%f\n", Avg);//注意此处为%f
	double Avg2 = getAvg2(L);
	printf("Avg2:%f\n", Avg2);//注意此处为%f

}
