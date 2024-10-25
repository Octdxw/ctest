#include <stdio.h>
#include <malloc.h>

#define N 10
typedef int ElemType;//给int取别名ElemType
typedef struct Sqlist
{//动态存储
	int *plist;
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

int main()
{
	Sqlist L;//声明L
	initial(L);//初始化L
}
