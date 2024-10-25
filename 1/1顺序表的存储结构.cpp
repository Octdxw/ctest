#include <stdio.h>
#include <stdlib.h>//声明malloc函数或<malloc.h>
#define N 10

typedef struct Sqlist//静态存储
{
	int ilist[N];//静态存储
	int length;//有效数据个数
} Sqlist;

void staticlist()//静态数组
{
	int ilist[N] = {11, 2, 3, 4, 5, 6, 7, 8, 9}; //存储空间不变，静态
	printf("%d %d", ilist[1], ilist[2]); //ilist[i-1]

}

typedef struct Dqlist//动态存储
{
	int *plist;//动态存储
	int length;//有效数据个数
	int listsize;//总长度
} Dqlist;

void dynamiclist()//动态数组
{
	int *plist = (int*)malloc(sizeof(int) * N);
//	plist[2] = 3;
//	printf("%d",plist[2])//赋值
	int *pnew = (int*)malloc(sizeof(int) * 2 * N);//扩容
	free(plist);
	plist = pnew;
//	plist[N + 1] = 6;

}
void formerlater(Sqlist L)	//输出前驱后继[0][1] [1][2]
{
	for(int i = 0; i < L.length - 1; i++)
	{
		printf("%d %d\n", L.ilist[i], L.ilist[i + 1]);
	}
}

void entire(Sqlist L)//访问整个线性表
{
	for(int i = 0; i < L.length; i++)
	{
		printf("%d ", L.ilist[i]);
	}
}
int main()
{
	dynamiclist();
	Sqlist L;
	L.length = 0;
//	L.ilist[0] = 11;
//	L.ilist[1] = 2;
//	......
//	L.length = N;
	
	for(int i = 0; i < N; i++) //循环赋值
	{
		L.ilist[i] = i + 1;
		L.length += 1;
	}
	//formerlater(L);
	entire(L);
}
