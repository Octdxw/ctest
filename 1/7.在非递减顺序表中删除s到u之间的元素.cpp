#include <stdio.h>
#include <malloc.h>
/*题目：
		在非递减(前驱<=后继)顺序表中删除s到t之间的元素
*/
/*算法思想：
	偏移法：第一个大于u的元素索引往前偏移tIndex-sIndex个单元
	1.从前往后找第一个大于等于s且小于等于t的索引为sIndex
	2.从后往前找第一个小于等于t且大于等于s的索引为tIndex
	3.删除sIndex到tIndex之间的元素，
	  即将第一个大于u的元素索引往前偏移x=tIndex-sIndex个单元
	4.L.length=L.length-x；
过滤法和偏移法的不同：
	1.不能一次性确定删除的位置，用过滤法
	2.能一次性确定删除的位置，用偏移法
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
//		if (i == 3)
//		{
//			L.plist[i] = L.length - 3;
//		}
//		else if(i == 6)
//		{
//			L.plist[i] = L.length - 2;
//		}
//		else
//		{
//			L.plist[i] = L.length - i;
//		}
		L.plist[i] = i;
	}
	printlist(L);//创建完打印L
}

int deleteElem(ElemType s, ElemType t, Sqlist &L)
{
	//1.从前往后找第一个大于等于s且小于等于t的索引为sIndex
	int sIndex = -1;
	for(int i = 0; i < L.length; i++)
	{
		if (L.plist[i] >= s && L.plist[i] <= t)
		{
			sIndex = i;
			break;
		}
	}
	//printf("sIndex:%d\n",sIndex);
	if(sIndex == -1)//没有比s更大的数，删除失败
	{
		return 0;
	}

	//2.从后往前找第一个小于等于t且大于等于s的索引为tIndex
	int tIndex = -1;
	for(int i = L.length - 1; i >= 0; i--)
	{
		if (L.plist[i] <= t && L.plist[i] >= s)
		{
			tIndex = i;
			break;
		}
	}
	//printf("tIndex:%d\n",tIndex);
	//3.删除sIndex到tIndex之间的元素，
	//即将第一个大于u的元素索引往前偏移tIndex-sIndex个单元
	int x = tIndex - sIndex + 1;
	for (int i = tIndex + 1; i < L.length; i++)
	{
		L.plist[i - x] = L.plist[i];
	}
	L.length -= x;
	return 1;
}






int main()
{
	Sqlist L;
	initial(L);
	createlist(L);
	int res = deleteElem(3, 5, L);
	//printf("res:%d\n",res);
	if (res == 1)
	{
		printlist(L);
	}
}