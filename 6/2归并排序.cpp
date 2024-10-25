#include <stdio.h>
#include <malloc.h>
/*
	题目：归并排序

*/
/*
	算法思想：
	划分与归并
*/

#define N 100
void mergeSort(int ilist[], int firstIndex, int lastIndex)
{
	if(lastIndex > firstIndex) //序列中的元素不止1个，进行划分归并，递归
	{
		int middleIndex = (firstIndex + lastIndex) / 2;
		mergeSort(ilist, firstIndex, middleIndex); //前一半序列
		mergeSort(ilist, middleIndex + 1, lastIndex); //后一半序列

		//前后一半排序好后，进行归并
		int tlist[N] = {0}; //用于保存待归并的序列
		int tlistlength = 0;

		int i = firstIndex;
		int j = middleIndex + 1;
		//先用tlist[]保存排序好的归并序列
		while(i <= middleIndex && j <= lastIndex)
		{
			if(ilist[i] < ilist[j])
			{
				tlist[tlistlength] = ilist[i];
				tlistlength++;
				i++;
			}
			else
			{
				tlist[tlistlength] = ilist[j];
				tlistlength++;
				j++;
			}
		}

		while(i <= middleIndex) //前一半序列有剩余
		{
			tlist[tlistlength] = ilist[i];
			tlistlength++;
			i++;
		}
		while(j <= lastIndex) //前一半序列有剩余
		{
			tlist[tlistlength] = ilist[j];
			tlistlength++;
			j++;
		}
		//将tlist[]中已排序好的序列复制到ilist[]中

		int base = firstIndex;
		for(int i = 0; i < tlistlength; i++)
		{
			ilist[base] = tlist[i];
			base++;
		}

	}



}


int main()
{
	int ilist[]={3,4,1,-1,6,7,2,3};
	int ilength=8;
	
	mergeSort(ilist,0,ilength-1);
	
	for(int i=0;i<ilength;i++)
	{
		printf("%d ",ilist[i]);
	}
	
	
}
