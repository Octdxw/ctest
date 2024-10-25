#include <stdio.h>
#include <malloc.h>
/*
	题目：
	哈希表的创建,并使用链地址法解决冲突
*/
/*
	算法思想：

*/
typedef int Elemtype;
typedef struct Node //节点
{
	Elemtype data;
	struct Node *next;	
}Node;

typedef struct ChHashTable //Hash表
{
	Node **plist;//指向指针数组的指针，即指针的指针
	int tlength;//表长
	int knum;//关键字数量
}ChHashTable;

void initialCHT(ChHashTable &CHT,int tlength)//初始化CHT
{
	CHT.plist=(Node **)malloc(sizeof(Node*)*tlength);
	CHT.tlength=tlength;
	CHT.knum=0;
	for(int i=0;i<CHT.tlength;i++)
	{
		CHT.plist[i]=NULL;
	}
}

ChHashTable createCHT(int tlength)//创建CHT
{
	ChHashTable CHT;
	initialCHT(CHT,tlength);
	return CHT;
}

void printfCHT(ChHashTable CHT)//打印CHT
{
	for(int i=0;i<CHT.knum;i++)
	{
		printf("%d ",CHT.plist[i]);
	}
}

int main()
{
	ChHashTable CHT=createCHT(10);
	
	for(int i=0;i<CHT.tlength;i++)
	{
		printf("%d ",CHT.plist[i]);
	}
}
