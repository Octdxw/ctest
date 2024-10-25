#include <stdio.h>
#include <malloc.h>
/*题目：
	顺序表A和B的元素分别为m和n，表A升序排序，表B降序排序，
	两个表中都不存在相同的元素
	（1）将两表合并，两表中的元素都存到非递减表C中
	（2）表A中有m+n个存储空间，将A，B两表合并，所有元素都存到A中，仍保持非递减
	（3）表A前r个元素递增有序，而A中后n—r个元素递减有序，将表A进行升序排序
*/
/*算法思想：
	(3)插入排序
	前面的递增有序，将后面的有序序列看做成一个待排序列，
	每次取一个元素插入到递增有序的序列中
*/
#define N 6
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
//	for (int i = 0; i < L.length; i++)
//	{
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
//	}
	L.plist[0]=0;
	L.plist[1]=1;
	L.plist[2]=3;
	L.plist[3]=6;
	L.plist[4]=5;
	L.plist[5]=4;

	printlist(L);//创建完打印L
}

void insertSort(int r, Sqlist &L)
{
	int insertIndex = r;
	while(insertIndex < L.length)
	{
		int i = insertIndex - 1;
		ElemType e = L.plist[insertIndex];
		while(i >= 0)
		{
			if(e >= L.plist[i]) //找到插入位置
			{
				L.plist[i + 1] = e;
				break;
			}
			L.plist[i + 1] = L.plist[i];//(没找到位置)往后挪一个位置
			i--;//没找到位置，往前找位置
		}
		insertIndex++;//下一个待插入的元素索引
	}
}


int main()
{
	Sqlist L;
	initial(L);
	createlist(L);
	insertSort(3,L);


	printlist(L);
}