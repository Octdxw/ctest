#include <stdio.h>
#include <malloc.h>
/*
	题目：
	哈希表的创建,并使用开放地址法解决冲突
*/
/*
	算法思想：

*/
typedef int Elentype;
typedef struct HashTable //哈希表
{
	Elentype *plist;
	int knum;//实际关键字数量
	int tlength;//哈希表表长
} HashTable;

#define INF 9999999;

void initial(HashTable &HT, int tlength)//初始化HT
{
	HT.plist = (Elentype *)malloc(sizeof(Elentype) * tlength);
	HT.tlength=tlength;
	HT.knum = 0;
	for(int i = 0; i < HT.tlength; i++)
	{
		HT.plist[i] = INF;
	}
}

HashTable createHT(int tlength)//创建HT
{
	HashTable HT;
	initial(HT,tlength);
	return HT;
}

void printfHT(HashTable HT)//打印HT
{
	for(int i=0;i<HT.knum;i++)
	{
		printf("%d ",HT.plist[i]);
	}
}

int main()
{
	HashTable HT=createHT(10);
	
	for(int i=0;i<HT.tlength;i++)
	{
		printf("%d ",HT.plist[i]);
	}
}
