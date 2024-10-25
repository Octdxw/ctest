#include <stdio.h>
#include <malloc.h>
/*题目：
		在第i给位置前插入e
*/
/*算法思想：
1.判断i的合法性
2.判断插入后空间是否足够,if不够,申请更大的空间，将原来的数据复制过去，改变总长
3.插入:第i个及之后的元素往后移动(从后往前挨个向后移动),在第i个位置插入e
4.有效数据表长加1
*/
#define N 10
typedef int ElemType;
typedef struct Sqlist
{
	ElemType *plist;
	int length;
	int listsize;
} Sqlist;

void initial(Sqlist &L)
{
	L.plist = (ElemType *)malloc(sizeof(ElemType) * N);
	L.length = 0;
	L.listsize = N;
	//printf("%d\n",L.length);
}
void creatlist(Sqlist &L)
{
	for(int i = 0; i < L.listsize; i++)
	{
		L.plist[i] = i+1;
		L.length += 1;
		//printf("L.plist[%d]:%d\n", i, L.plist[i]);

		//printf("L.length:%d\n", L.length);
	}
}

int insert(ElemType e, int ith, Sqlist &L)
{
	//1.判断i的合法性
	if (ith < 1 || ith > L.length)
	{
		printf("输入位置不合法\n");
		return 0;
	}
	//2.判断插入后空间是否足够,if不够,申请更大的空间，将原来的数据复制过去，改变总长
	if(L.length + 1 > N)
	{
		ElemType *pnew = (ElemType *)malloc(sizeof(ElemType) * 2 * N);//申请更大的空间
		for(int index = 0; index < L.length; index++)//将原来的数据复制过去
		{
			pnew[index] = L.plist[index];
		}
		free(L.plist);
		L.plist = pnew;
		L.listsize = 2 * N;//改变总长
	}
	//3.插入:第i个及之后的元素往后移动(从后往前挨个向后移动),在第i个位置插入e
	//第ith个位置对应plist[ith-1]
	for(int i = L.length - 1; i >= ith - 1; i--)//第i个：i >= ith - 1
	{
		L.plist[i + 1] = L.plist[i];
	}
	L.plist[ith - 1] = e;//在第i个位置插入e
	//4.有效数据表长加1
	L.length += 1;
	return 1;
}

void printlist(Sqlist L)//打印L
{
	printf("L.length:%d\n", L.length);
	for(int i = 0; i < L.length; i++)
	{
		printf("L.plist[%d]:%d\n", i, L.plist[i]);
	}
}

int main()
{
	Sqlist L;
	initial(L);
	creatlist(L);
	int res = insert(100, 11, L);
	//printf("%d\n",res);
	if (res == 1)
	{
		printlist(L);
	}

}
