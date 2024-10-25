#include <stdio.h>
#include <malloc.h>
#include <math.h>
/*
	题目：
	开放地址法删除
	如果key存在，则删除
	不存在，不执行删除
*/
/*
	算法思想：

*/
typedef int Elentype;
typedef struct HashTable //哈希表
{
	Elentype *plist;
	int knum;//实际关键字数量
	int tlength;//哈希表表长
} HashTable;

#define INF 9999999

void initial(HashTable &HT, int tlength)//初始化HT
{
	HT.plist = (Elentype *)malloc(sizeof(Elentype) * tlength);
	HT.tlength = tlength;
	HT.knum = 0;
	for(int i = 0; i < HT.tlength; i++)
	{
		HT.plist[i] = INF;
	}
}

HashTable createHT(int tlength)//创建HT
{
	HashTable HT;
	initial(HT, tlength);
	return HT;
}

void printfHT(HashTable HT)//打印HT
{
	for(int i = 0; i < HT.knum; i++)
	{
		printf("%d ", HT.plist[i]);
	}
}
#define p 3
int Hash(Elentype key)// 哈希函数
{
	return key % p;
}
/*
Di[0]=0  Hash(K)<===> Hash(K) + Di[0] = H0
H(1) = Hash(1)<===> (Hash(K) + Di[1] )%tlength
H(2) = Hash(2)<===> (Hash(K) + Di[2] )%tlength
....
这样就能统一化
*/
int Di[100] = {0};
void getDi(int tlength)
{
//	for(int i = 1; i <= tlength - 1; i++)
//	{
//		//D[0]=0
//		Di[i] = i;
//	}
	//二次遍历
	int Dilength = 0;
	for(int i = 1; i <= tlength / 2 + 1; i++)
	{
		Dilength++;//0->1
		Di[Dilength] = i * i; //D[1]=1*1
		Dilength++;//1->2
		Di[Dilength] = -i * i; //D[2]=-1*1

	}
	//打印Di[i]
//	for(int i=0;i<=Dilength;i++)
//	{
//		printf("%d ",Di[i]);
//	}

}

int isUpperBound(int di, int tlength) //判断di是否达到上界
{
//	if(di > tlength - 1) //超出查找范围
//	{
//		return 1;
//	}
//	return 0;
	//二次遍历

	if(sqrt(abs(di)) > tlength / 2) //超出查找范围，abs取绝对值，sqrt开平方
	{
		return 1;
	}
	return 0;

}

//Hi = (Di + Hash(key)) % tlength;
//那么就可以从第0次冲突发生时的地址Hi,开始i匹配
//如果当前的探测序列元素没有超限，并且访问的位置Hi非空白，冲突，继续查找Hi
//已经超限或者存储空间为空白单元，查找失败

int searchkey(Elentype key, HashTable HT, int &pos)
{
	int i = 0;
	int Hi = (Di[i] + Hash(key)) % HT.tlength;
	while(INF != HT.plist[Hi] && isUpperBound(Di[i], HT.tlength) == 0)//非空白单元并且没有超出上界
	{
		if(key == HT.plist[Hi])
		{
			pos = Hi;
			return 1;
		}
		//发生冲突
		i++;

		Hi = (Di[i] + HT.tlength + Hash(key)) % HT.tlength;
	}
	pos = Hi; //返回最后一次查找的位置
	return 0;
}

int insertKey(Elentype key, HashTable &HT)
{
	int pos = -1;
	int ret = searchkey(key, HT, pos);
	if(ret == 0 && HT.plist[pos] == INF)
	{
		HT.plist[pos] = key;
		HT.knum++;
		printf("HT.knum:%d\n",HT.knum);
		return 1;
		
	}
	return 0;
}
int delt(Elentype key, HashTable &HT)
{
	int pos = -1;
	int ret = searchkey(key, HT, pos);
	if(ret == 1)
	{
		HT.plist[pos] = INF;
		HT.knum--;
		printf("HT.knum:%d\n",HT.knum);
		return 1;
	}
	return 0;
}

int main()
{
	//线性探测
//	HashTable HT = createHT(10);
//	HT.tlength = 10;
//	getDi(HT.tlength);
//	HT.plist[6] = 6;
//	HT.plist[7] = 13;
//	HT.plist[8] = 27;
//	HT.plist[9] = 41;
//	HT.plist[0] = 55;
//	HT.knum = 5;

	HashTable HT = createHT(4);
	HT.tlength = 4;
	getDi(HT.tlength);
	HT.plist[0] = 0;
	HT.plist[1] = 1;
	HT.plist[2] = 2;
	HT.knum = 3;

	int ret = insertKey(3, HT);
	printf("ret:%d\n", ret);
	printfHT(HT);
	printf("\n");
	int ret2=delt(3,HT);
	printf("ret2:%d\n", ret2);
	printfHT(HT);

}
















