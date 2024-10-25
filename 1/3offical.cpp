#include <stdio.h>
#include <malloc.h>
/*题目：
		在第i给位置前插入e
*/
/*算法思想：
1.判断i的合法性
2.判断当前是否足够,if不够,申请更大的空间，将原来的数据复制过去，改变总长
3.插入:第i个及之后的元素往后移动(从后往前挨个向后移动),在第i个位置插入e
4.有效数据表长加1
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

int insert(ElemType e, int ith, Sqlist &L)
{
	if (ith < 1 || ith > L.length)//判断ith是否合法，不合法，返回0
	{
		return 0;
	}
	if (L.length >= L.listsize) //表内没有空间给e
	{
		ElemType *pnew = (ElemType *)malloc(sizeof(ElemType) * 2 * L.listsize);//申请空间
		for (int i = 0; i < L.length; i++)//复制原来的数据到新的空间
		{
			pnew[i] = L.plist[i];
		}
		free(L.plist);
		L.plist = pnew;
		L.listsize = 2 * L.listsize;
	}
	for (int i = L.length - 1; i >= ith - 1; i--)//第ith位（plist[ith-1]）及以后的往后移（从后往前操作）
	{
		L.plist[i + 1] = L.plist[i];
	}
	L.plist[ith - 1] = e;//第ith位（plist[ith-1]）插入e
	L.length += 1;//表长加1
	return 1;
}
int main()
{
	Sqlist L;//声明L
	initial(L);//初始化L
	createlist(L);
	int res = insert(100, 1, L);
	if (res == 1)
	{
		printlist(L);
	}
}
