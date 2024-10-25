#include <stdio.h>
#include <malloc.h>
/*题目：
		删除s到u之间的元素
*/
/*算法思想：
过滤法：在一个表中操作，当前访问的子序列长度>=当前结果子序列长度，
		采用两个工作指针，一个用于指向当前访问的子序列末端
		另一个用于指向当前结果子序列末端
1.curlength指向当前结果子序列末端，而curlength的数值正好是当前结果子序列长度
2.i指向当前访问的子序列末端
3.不满足s到u范围的元素加到当前结果子序列，curlength+1；
4.L.length=curlength;
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

void deleterangeSU(ElemType s, ElemType u, Sqlist &L)
{
	//1.curlength指向当前结果子序列末端，而curlength的数值正好是当前结果子序列长度
	int curlength = 0;	
	//2.i指向当前访问的子序列末端
	for (int i = 0; i < L.length; i++)
	{
		if (L.plist[i] < s || L.plist[i] > u)
		{
			//3.不满足s到u范围的元素加到当前结果子序列，length+1；
			L.plist[curlength] = L.plist[i];
			curlength++;
		}
	}
	L.length = curlength; //4.L.length=curlength;
}



int main()
{
	Sqlist L;
	initial(L);
	createlist(L);
	deleterangeSU(3, 5, L);
	printlist(L);
}