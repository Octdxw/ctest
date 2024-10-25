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
	(1)较小（大）值法：有序的输入->有序的处理->有序的输出
		A表从前往后取，B表从后往前取

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
	//printlist(L);//创建完打印L
}

void combine(Sqlist &La, Sqlist &Lb, Sqlist &Lc)
{
	//1.初始化Lc
	Lc.plist = (ElemType *)malloc(sizeof(ElemType) * (La.length + Lb.length));
	Lc.listsize = La.length + Lb.length;
	Lc.length = 0;
	//2.较小值插入
	int i = 0;//A表从前往后取
	int j = Lb.length - 1;//B表从后往前取
	while(i < La.length && j >= 0)
	{
		if (La.plist[i] < Lb.plist[j])//A更小
		{
			Lc.plist[Lc.length] = La.plist[i];
			Lc.length += 1;
			i++;
		}
		else
		{
			Lc.plist[Lc.length] = Lb.plist[j];
			Lc.length += 1;
			j--;
		}
	}
	while(i < La.length)//B表取完，将A表中的剩余元素加到C表
	{
		Lc.plist[Lc.length] = La.plist[i];
		Lc.length += 1;
		i++;
	}
	while(j >= 0) //A表取完，将B表中的剩余元素加到C表
	{
		Lc.plist[Lc.length] = Lb.plist[i];
		Lc.length += 1;
		j--;
	}
	//释放A，B空间，考试可不写
	free(La.plist);
	free(Lb.plist);
	La.length = Lb.length = 0;
	La.listsize = Lb.listsize = 0;
}






int main()
{
	//定义并创建La
	Sqlist La;
	initial(La);
	createlist(La);
	for(int i = 0; i < La.length; i++)
	{
		La.plist[i] = i;
	}
	printlist(La);
	//定义并创建Lb
	Sqlist Lb;
	initial(Lb);
	createlist(Lb);
	for(int i = 0; i < Lb.length; i++)
	{
		Lb.plist[i] = 9 - i;
	}
	printlist(Lb);
	//定义Lc
	Sqlist Lc;
	combine(La, Lb, Lc);
	printlist(Lc);

}