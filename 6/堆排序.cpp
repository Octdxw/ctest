#include <stdio.h>
#include <malloc.h>
/*
	题目：堆排序

*/
/*
	算法思想：
	1.先初始化为大顶堆，根为最大者
	2.将最大者放在iList[listlength]的最后面，分离出最大者
	3.最大者iList[listlength]不参与下一次的初始化和分离
	即除了iList[listlength]，重复1，2
	大顶堆：父节点大于左右孩子
	先让最小的子树满足大顶堆，往上走

*/

void adjHeap(int iList[], int listlength, int rIndex)
{
	//rIndex为当前（子）树根节点的位置
	int iElem = iList[rIndex]; //保存根节点的数据，用于寻找根节点的数据在这次排序的最终位置
	int culIndex = rIndex; //记录当前要调整的位置

	while(2 * culIndex <= listlength)
	{
		int lcIndex = 2 * culIndex; //左孩子索引
		int rcIndex = 2 * culIndex + 1; //右孩子索引
		int biggerIndex = lcIndex; //右孩子可能不存在，初始化较大的数据索引为左孩子索引

		if(rcIndex <= listlength && iList[lcIndex] < iList[rcIndex]) //右孩子存在且右孩子的数据更大
		{
			biggerIndex = rcIndex; //更新孩子中较大者的索引
		}

		if(iList[biggerIndex] > iElem) //孩子数据中的较大者大于最开始根的数据，确定最开始根的数据的最终位置
		{
			iList[culIndex] = iList[biggerIndex]; //交换孩子数据中的较大者和父节点的数据，使较大的数据位于父节点里
			culIndex = biggerIndex; //更改当前的根节点索引，判断更小的子树是否满足大顶堆
		}
		else
		{
			//当前子树下所有的子子树都满足大顶堆
			break;
		}
	}
	//当前子树下所有的子子树都满足大顶堆,确定根节点位置
	iList[culIndex] = iElem;// 将最开始的根节点数据放到最终位置

}

//初始为大顶堆
void getInitHeap(int ilist[], int ilength)
{
	for(int i = ilength / 2; i >= 1; i--)
	{
		adjHeap(ilist, ilength, i);
	}

}

//堆排序
void heapSort(int ilist[], int listlength)
{
	getInitHeap(ilist, listlength); //初始为大顶堆

	for(int i = listlength; i > 1; i--)
	{
		int iElem = ilist[1]; //此时ilist[1]保存的为最大者，ilist[listlength]为最小值
		ilist[1] = ilist[i]; //将最小值和最大者交换,让根节点ilist[1]变成最小值
		ilist[i] = iElem;//末端变成最大者
		
		//此时最大者在ilist[listlength]内，不参与下一次查找最大者
		adjHeap(ilist, i-1,1);
	}

}

int main()
{
	int ilist[] = {0, 4, 9, 13, 5, 6, 8, 14, 20, 30, 80}; //ilist[0]不存入数据
	int ilength = 10; //读取索引1-10的数据

	heapSort(ilist,ilength);

	for(int i = 1; i <= ilength; i++)
	{
		printf("%d ", ilist[i]);
	}
	printf("\n");


}
