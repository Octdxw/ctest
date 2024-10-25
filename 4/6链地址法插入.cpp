#include <stdio.h>
#include <malloc.h>
/*
	题目：
	链地址法插入，若表中不存在key，则插入，存在，则不插入
*/
/*
	算法思想：

*/
typedef int Elemtype;
typedef struct Node //节点
{
	Elemtype data;
	struct Node *next;
} Node;

typedef struct ChHashTable //Hash表
{
	Node **plist;//指向指针数组的指针，即指针的指针
	int tlength;//表长
	int knum;//关键字数量
} ChHashTable;

void initialCHT(ChHashTable &CHT, int tlength) //初始化CHT
{
	CHT.plist = (Node **)malloc(sizeof(Node*)*tlength);
	CHT.tlength = tlength;
	CHT.knum = 0;
	for(int i = 0; i < CHT.tlength; i++)
	{
		CHT.plist[i] = NULL;
	}
}

ChHashTable createCHT(int tlength)//创建CHT
{
	ChHashTable CHT;
	initialCHT(CHT, tlength);
	return CHT;
}

#define p 7;
int Hash(Elemtype key)
{
	return key % p;
}

void insertKey(Elemtype key, ChHashTable &CHT)
{
	int i = Hash(key);
	Node *pcur = CHT.plist[i]; //获得位置i处的单链表第一个数据地址
	if(pcur != NULL) //不为空，key可能存在,查找key
	{
		Node *pre = NULL;
		while(pcur != NULL)
		{
			if(pcur->data == key)
			{
				break;
			}
			pre = pcur; //当前值不是key，继续查找
			pcur = pcur->next;
		}
		if(pcur == NULL) //不存在key,插入，尾插
		{
			Node *pnode = (Node *)malloc(sizeof(Node));
			pnode->data = key;
			pnode->next = NULL;
			//在尾节点上挂上key节点
			pre->next = pnode;
		}

	}
	else//为空，key不存在，插入，尾插
	{
		Node *pnode = (Node *)malloc(sizeof(Node));
		pnode->data = key;
		pnode->next = NULL;
		//插入节点
		CHT.plist[i] = pnode;
	}
}
/*
int insertKey(Elemtype key, ChHashTable &CHT)
{
	int i = Hash(key);
	Node *pcur = CHT.plist[i]; //获得位置i处的单链表第一个数据地址
	if(pur != NULL) //不为空，key可能存在,查找key
	{
		Node *pre = NULL;
		while(pur != NULL)
		{
			if(pur->data = key)
			{
				return 0;
			}
			pre = pcur; //当前值不是key，继续查找
			pcur = pcur->next;
		}
		//	不存在key，插入key
		Node *pnode = (Node *)malloc(sizeof(Node));
		pnode->data = key;
		pnode->next = NULL;
		//在尾节点上挂上key节点
		pre->next = pnode;


	}
	else//为空，key不存在，插入
	{
		Node *pnode = (Node *)malloc(sizeof(Node));
		pnode->data = key;
		pnode->next = NULL;
		//插入节点
		CHT.plist[i] = pnode;
	}
	return 1;
}
*/

int main()
{
	ChHashTable CHT = createCHT(10);

	Elemtype keyList[] = {31, 23, 17, 27, 19, 11, 13, 91, 61, 41};
	int keyListLength = 10;
	for(int i = 0; i < keyListLength; i++)
	{
		insertKey(keyList[i], CHT);
	}

	for(int i = 0; i < CHT.tlength; i++)
	{
		Node *pnode = CHT.plist[i];
		while(pnode != NULL)
		{
			printf("%d ", pnode->data);
			pnode = pnode->next;
		}
		printf("\n");
	}
}
