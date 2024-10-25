#include <stdio.h>
#include <malloc.h>
/*题目：
	给定两个非空的集合A和B，分别用升序顺序表La和Lb存储
	设计算法求解A∩B（共同的元素在结果中只出现一次）
*/
/*算法思想：
	最小值法+过滤法
	1.i指向La,j指向Lb,curlength=0
	2..若La[i]<Lb[j],i++
	3.若La[i]>Lb[j],j++
	4.若La[i]=Lb[j],La[i]加入新表La,curlength++,i++,j++
	5.更新La表长
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

void commonElem(Sqlist &La, Sqlist Lb)
{
	int curlength = 0;
	int i = 0;
	int j = 0;
	while(i < La.length && j < Lb.length)
	{
		//1.i指向La,j指向Lb,curlength=0
		if(La.plist[i] < Lb.plist[j])
		{
			//2.若La[i]<Lb[j],i++
			i++;
		}
		else if(La.plist[i] > Lb.plist[j])
		{
			//3.若La[i]>Lb[j],j++
			j++;
		}
		else
		{
			//4.若La[i]=Lb[j],La[i]加入新表La,curlength++,i++,j++
			La.plist[curlength] = La.plist[i];
			curlength++;
			i++;
			j++;
		}
	}
	//5.更新La表长
	La.length = curlength;
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
	commonElem(La, Lb);
	printlist(La);
}