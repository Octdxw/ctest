#include <stdio.h>
#include <malloc.h>
/*题目：

*/
/*算法思想：

*/
#define N 10
typedef int ElemType;//给int取别名ElemType
typedef struct Sqlist
{
	//动态存储
	ElemType *plist;
	int length;
	int listsize;
} Sqlist;

void initial(Sqlist &L)//初始化动态顺序表,&对L进行修改
{
	L.plist = (ElemType *)malloc(sizeof(ElemType) * N);//手动分配空间
	L.length = 0;//初始化有效数据长度
	L.listsize = N;//初始化总长度
	//printf("%d\n",L.length);
}

void printlist(Sqlist L)//打印L
{
	for(int i = 0; i < L.length; i++)
	{
		printf("%d ", L.plist[i]);
	}
	printf("\n");
	printf("length:%d listsize:%d\n", L.length, L.listsize);
}

void createlist(Sqlist &L)//创建L
{
	L.length = N;//L.length未赋值之前为0
	for (int i = 0; i < L.length; i++)
	{
		if (i == 3)
		{
			L.plist[i] = L.length - 3;
		}
		else if(i == 6)
		{
			L.plist[i] = L.length - 2;
		}
		else
		{
			L.plist[i] = L.length - i;
		}
	}
	printlist(L);//创建完打印L
}



int main()
{
	Sqlist L;
	initial(L);
	createlist(L);
	
	
	
	
	printlist(L);
}