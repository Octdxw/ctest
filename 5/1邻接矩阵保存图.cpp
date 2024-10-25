#include <stdio.h>
#include <malloc.h>
#include <cstring>
/*
	题目：邻接矩阵保存图的信息

*/
/*
	算法思想：

*/

//图的种类，枚举
typedef enum GraphKind
{
	DG, UDG, DN, UDN //directed graph,directed network
} GraphKind;

#define INF 9999999
#define MAX_ARC_NUM 10
#define MAX_VERTEX_NUM 10
typedef  int VRType;//权值

//图的弧信息
typedef struct ArcCell
{
	int adj;//权值

	//InfoType *info;
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//邻接矩阵

//图的拓扑信息，弧，顶点，宏观的信息

typedef struct MGraph
{
	AdjMatrix arcs;//弧信息,邻接矩阵
	int vexs[MAX_VERTEX_NUM];//顶点
	int vexnum;//顶点个数
	int arcnum;//弧边数
	GraphKind kind;//图的种类
} MGraph;

int printMGraph(MGraph mG)
{
	if(mG.vexnum <= 0 || mG.arcnum <= 0)
	{
		return 0;
	}

	//打印存在的边
	for(int iRow = 1; iRow <= mG.vexnum; iRow++)
	{
		for(int jCol = 1; jCol <= mG.vexnum; jCol++) //顶点编号从1开始，索引也从1开始
		{
			if(mG.arcs[iRow][jCol].adj != 0) //邻接矩阵存在该边
			{
				printf("%d %d\n", mG.vexs[iRow], mG.vexs[jCol]); //打印存在的边
			}
		}
	}

	//打印顶点信息
	for(int index = 1; index <= mG.vexnum; index++)
	{
		printf("%d ", mG.vexs[index]);
	}
	printf("\n");

	printf("vexnum:%d\n", mG.vexnum);
	printf("arcnum:%d\n", mG.arcnum);
	return 1;
}

int createMGraph(MGraph *mG, int vSet[], int vSetlength, int arcSet[][2], int arcSetlength)
{
	//图mG，顶点，顶点数量，边，边数
	if(mG == NULL || vSet == NULL || arcSet == NULL)
	{
		return 0;
	}
	
	//将顶点信息存入到mG的顶点数组中,从数组1号索引开始存
	for(int index = 1; index <= vSetlength; index++)
	{
		int vertex = vSet[index];
		mG->vexs[vertex] = vertex; //将顶点信息存入到mG的顶点数组中
	}

	//将边信息存入mG的邻接矩阵中,因为arcSetlength从0开始，所以index也从0开始
	for(int index = 0; index < arcSetlength; index++)
	{
		int src = arcSet[index][0];//起点
		int dest = arcSet[index][1];//终点

		mG->arcs[src][dest].adj = 1;
	}
	
	mG->vexnum = vSetlength;
	mG->arcnum = arcSetlength;
	mG->kind = DG;
	return 1;


}

int main()
{
	int vSet[MAX_VERTEX_NUM] = {0};
	int vSetlength = 0; //记录顶点数量
	FILE *f = fopen("D:/C/try/5/vSet.txt", "r");
	if(NULL != f)//读取顶点信息
	{
		int vertexID;//顶点ID
		while(!feof(f))//feof:end of file,判断是否读完文件
		{

			fscanf(f, "%d", &vertexID); //从文件 f 中读取一个整数，并将其存储到 vertexID 变量中
			//printf("vertexID:%d\n", vertexID);//输出顶点信息
			//假设顶点ID从1开始
			vSet[vertexID] = vertexID; //顶点信息
			vSetlength++;//定点数+1
		}
	}
	fclose(f);//关闭文件

	FILE *fArc = fopen("D:/C/try/5/arcSet.txt", "r");
	int arcSet[MAX_ARC_NUM][2];//读取边信息，不是邻接矩阵
	int arcSetlength = 0;//文件读到第几行,最终为边的数量
	if(fArc != NULL) //存入边信息
	{
		int srcVertex;//起点
		int destVertex;//终点
		while(!feof(fArc))
		{
			fscanf(fArc, "%d %d", &srcVertex, &destVertex);
			arcSet[arcSetlength][0] = srcVertex;
			arcSet[arcSetlength][1] = destVertex;
			arcSetlength++;//每读入一条边，边的数量加1

		}
		fclose(fArc);
	}

//	for(int i = 0; i < arcSetlength; i++)
//	{
//		printf("%d %d\n", arcSet[i][0], arcSet[i][1]);
//	}


	MGraph mG;
	//对邻接矩阵初始化
	for(int index = 0; index < MAX_VERTEX_NUM; index++)
	{
		memset(mG.arcs[index], 0, sizeof(ArcCell) * MAX_VERTEX_NUM);
	}
	
	
	//创建邻接矩阵
	int ret = createMGraph(&mG, vSet, vSetlength, arcSet, arcSetlength);
	
	if(ret == 1)
	{
		int i = printMGraph(mG);
	}





}
