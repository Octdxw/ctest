#include <stdio.h>
#include <stdlib.h>//����malloc������<malloc.h>
#define N 10

typedef struct Sqlist//��̬�洢
{
	int ilist[N];//��̬�洢
	int length;//��Ч���ݸ���
} Sqlist;

void staticlist()//��̬����
{
	int ilist[N] = {11, 2, 3, 4, 5, 6, 7, 8, 9}; //�洢�ռ䲻�䣬��̬
	printf("%d %d", ilist[1], ilist[2]); //ilist[i-1]

}

typedef struct Dqlist//��̬�洢
{
	int *plist;//��̬�洢
	int length;//��Ч���ݸ���
	int listsize;//�ܳ���
} Dqlist;

void dynamiclist()//��̬����
{
	int *plist = (int*)malloc(sizeof(int) * N);
//	plist[2] = 3;
//	printf("%d",plist[2])//��ֵ
	int *pnew = (int*)malloc(sizeof(int) * 2 * N);//����
	free(plist);
	plist = pnew;
//	plist[N + 1] = 6;

}
void formerlater(Sqlist L)	//���ǰ�����[0][1] [1][2]
{
	for(int i = 0; i < L.length - 1; i++)
	{
		printf("%d %d\n", L.ilist[i], L.ilist[i + 1]);
	}
}

void entire(Sqlist L)//�����������Ա�
{
	for(int i = 0; i < L.length; i++)
	{
		printf("%d ", L.ilist[i]);
	}
}
int main()
{
	dynamiclist();
	Sqlist L;
	L.length = 0;
//	L.ilist[0] = 11;
//	L.ilist[1] = 2;
//	......
//	L.length = N;
	
	for(int i = 0; i < N; i++) //ѭ����ֵ
	{
		L.ilist[i] = i + 1;
		L.length += 1;
	}
	//formerlater(L);
	entire(L);
}
