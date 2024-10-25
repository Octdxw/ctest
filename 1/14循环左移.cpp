#include <stdio.h>
#include <malloc.h>
/*题目：
	逆置表
	循环左移r:整体逆置+部分逆置
*/
/*算法思想：
	逆置表：索引low<high，交换元素
	循环左移r:整体逆置+部分逆置
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

void reverse(Sqlist &L, int low, int high)
{
	//逆置
	while(low < high)
	{
		ElemType e = L.plist[low];
		L.plist[low] = L.plist[high];
		L.plist[high] = e;
		low++;
		high--;
	}
}
void moveR(int r, Sqlist &L)
{
	//循环左移
	reverse(L, 0, L.length - 1);
	reverse(L, 0, L.length - r - 1);
	reverse(L, L.length - r, L.length - 1);

}

int main()
{
	//定义并创建A
	Sqlist La;
	//initial(L);
	//createlist(L);
	La.plist = (ElemType *)malloc(sizeof(ElemType) * 2 * N);
	La.listsize = 2 * N;
	La.length = 10;
	for (int i = 0; i < La.length; i++)
	{
		La.plist[i] = i;
	}
	printlist(La);
	moveR(4,La);
	printlist(La);
}