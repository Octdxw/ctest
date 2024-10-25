#include <stdio.h>
#include <malloc.h>
/*题目：
	给定两个非空集合A，B，分别用升序表La和Lb存储，设计算法求解A-B
*/
/*算法思想：
	最小值法
	1.每次取La和Lb中的较小值，
	2.若相同，则i++，j++
	3.不同，较小的一方存入Lc，较小的一方索引++
	4.直至都取完
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

void except(Sqlist La, Sqlist Lb, Sqlist &Lc)
{
	int indexLa = 0;//指向La
	int indexLb = 0;//指向Lb
	while(indexLa < La.length && indexLb < Lb.length)
	{
		if (La.plist[indexLa] < Lb.plist[indexLb])
		{
			//La的较小
			Lc.plist[Lc.length] = La.plist[indexLa];
			Lc.length++;
			indexLa++;
		}
		else if (La.plist[indexLa] > Lb.plist[indexLb])
		{
			//Lb的较小
			Lc.plist[Lc.length] = Lb.plist[indexLb];
			Lc.length++;
			indexLb++;
		}
		else
		{
			//相等
			indexLa++;
			indexLb++;
		}
	}
	while(indexLa < La.length)
	{
		//Lb的取完但La未取完
		Lc.plist[Lc.length] = La.plist[indexLa];
		Lc.length++;
		indexLa++;
	}
	while(indexLb < Lb.length)
	{
		//La的取完但Lb未取完
		Lc.plist[Lc.length] = Lb.plist[indexLb];
		Lc.length++;
		indexLb++;
	}
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
	Lb.length = 6;
	for (int i = 0; i < Lb.length; i++)
	{
		Lb.plist[i] = i;
	}
	printlist(Lb);
	//定义Lc
	Sqlist Lc;
	Lc.plist = (ElemType *)malloc(sizeof(ElemType) * 3 * N);
	Lc.listsize = 3 * N;
	Lc.length = 0;
	except(La,Lb,Lc);
	printlist(Lc);
}