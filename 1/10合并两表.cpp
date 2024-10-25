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
	(2)最大值法：从A表尾开始存
	每次选出A表数据最后一个元素，B表头的较大者存入A表尾
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

void combine(Sqlist &La, Sqlist &Lb)
{
	int i = La.length - 1;//从A最后一的数据元素取
	int j = 0;
	int curlength = 0;//当前结果子序列长度
	//较大值法
	while(i >= 0 && j < Lb.length)
	{
		if (La.plist[i] > Lb.plist[j])//A更大
		{
			//存入的位置为La.plist[La.listsize - 1 - curlength]
			La.plist[La.listsize - 1 - curlength] = La.plist[i];
			i--;
			curlength++;
		}
		else
		{
			La.plist[La.listsize - 1 - curlength] = Lb.plist[j];
			j++;
			curlength++;
		}
	}
	while(i >= 0)//B取完，将A中剩余的元素存入A
	{
		La.plist[La.listsize - 1 - curlength] = La.plist[i];
		i--;
		curlength++;
	}
	while(j < Lb.length)//A取完，将B中剩余的元素存入A
	{
		Lb.plist[La.listsize - 1 - curlength] = Lb.plist[j];
		j++;
		curlength++;
	}
	//修改A表的有效长度
	La.length = La.length + Lb.length;
	Lb.length = 0;
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
	//定义并创建B
	Sqlist Lb;
	Lb.plist = (ElemType *)malloc(sizeof(ElemType) * N);
	Lb.listsize =  N;
	Lb.length = 10;
	for (int i = 0; i < Lb.length; i++)
	{
		Lb.plist[i] = 9-i;
	}
	printlist(Lb);
	combine(La,Lb);
	printlist(La);
}