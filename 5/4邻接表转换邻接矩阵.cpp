#include <stdio.h>
#include <malloc.h>
#include <cstring>
/*
	题目：
		将邻接表表示的无向网转换成邻接矩阵

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

typedef struct ArcNode //单链表中数据节点的信息
{
	int weight;//权值
	int adjvex; //终点的编号索引
	struct ArcNode *nextArc; //指向下一个弧节点的指针
} ArcNode;

//顶点数组的存储结构
typedef struct VNode
{
	int data; //源点的信息
	ArcNode *firstArc;//指向第一条弧终点的指针
} VNode, AdjList[MAX_VERTEX_NUM]; //头节点数组

//将图的微观信息打包成图
typedef struct ALGraph
{
	AdjList vertices; //邻接表
	int vexnum;//节点的数量
	int arcnum;//边的数量
	GraphKind kind;//图的种类
} ALGraph;

//创建以邻接表存储的图,无向图
int createALGraph(ALGraph *G, int vSet[], int vSetlength, int arcSet[][3], int arcSetlength)
{
	if(G == NULL || vSet == NULL || arcSet == NULL)
	{
		return 0;
	}

	//存入顶点信息,顶点索引从1开始
	for(int index = 1; index <= vSetlength; index++)
	{
		int vertex = vSet[index];//读出一个顶点信息
		G->vertices[vertex].data = vertex; //将顶点信息存入头节点数组中，此时其后无节点
		//将头节点指向第一条边的指针置为NULL
		G->vertices[vertex].firstArc = NULL;
	}

	//存入边信息到邻接表中
	for(int i = 0; i < arcSetlength; i++)
	{
		int src = arcSet[i][0]; //源点
		int dest = arcSet[i][1]; //终点
		int weight = arcSet[i][2]; //权值

		//生成一个包含dest的弧节点，插入到以src为源点的头节点之后
		ArcNode *arcNodePtr = (ArcNode *)malloc(sizeof(ArcNode));
		arcNodePtr->adjvex = dest;
		arcNodePtr->weight = weight;

		//头插法，插入到以src为源点的头节点之后
		arcNodePtr->nextArc = G->vertices[src].firstArc;
		G->vertices[src].firstArc = arcNodePtr;

		//以dest为源点
		ArcNode *arcNodePtr2 = (ArcNode *)malloc(sizeof(ArcNode));
		arcNodePtr2->adjvex = src;
		arcNodePtr2->weight = weight;

		//头插法，插入到以dest为源点的头节点之后
		arcNodePtr2->nextArc = G->vertices[dest].firstArc;
		G->vertices[dest].firstArc = arcNodePtr2;
	}

	//图的其他信息
	G->kind = UDG;
	G->arcnum = 2 * arcSetlength;
	G->vexnum = vSetlength;
	return 1;
}

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
			if(mG.arcs[iRow][jCol].adj != INF) //邻接矩阵存在该边
			{
				printf("%d %d %d\n", mG.vexs[iRow], mG.vexs[jCol], mG.arcs[iRow][jCol].adj); //打印存在的边
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
void printALGraph(ALGraph G)
{
	for(int i = 1; i <= G.vexnum; i++) //顶点索引从1开始
	{
		int src = G.vertices[i].data; //源点
		ArcNode *pNextArc = G.vertices[i].firstArc; //源点的第一条边

		while (pNextArc != NULL)
		{
			printf("%d----->%d %d\n", src, pNextArc->adjvex, pNextArc->weight);
			pNextArc = pNextArc->nextArc;
		}
	}
}

int switchALGToMG(ALGraph G, MGraph * mG)
{
	if(mG == NULL)
	{
		return 0;
	}

	//宏观信息

	mG->vexnum = G.vexnum;
	mG->arcnum = G.arcnum;
	mG->kind = G.kind;

	//微观信息,顶点，边
	for(int i = 1; i <= G.vexnum; i++) //顶点
	{
		mG->vexs[i] = G.vertices[i].data; //顶点
	}
	for(int i = 1; i <= G.vexnum; i++) //边
	{
		int src = G.vertices[i].data; //源点
		ArcNode *ArcNode = G.vertices[i].firstArc; //源点的帝一条边
		while(ArcNode != NULL)
		{
			int dest = ArcNode->adjvex;
			mG->arcs[src][dest].adj = ArcNode->weight; //权值
			ArcNode = ArcNode->nextArc; //处理下一条边
		}

	}
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
	int arcSet[MAX_ARC_NUM][3];//读取边信息，不是邻接矩阵
	int arcSetlength = 0;//文件读到第几行,最终为边的数量
	if(fArc != NULL) //存入边信息
	{
		int srcVertex;//起点
		int destVertex;//终点
		int weight;//权值
		while(!feof(fArc))
		{
			fscanf(fArc, "%d %d %d", &srcVertex, &destVertex, &weight);
			arcSet[arcSetlength][0] = srcVertex;
			arcSet[arcSetlength][1] = destVertex;
			arcSet[arcSetlength][2] = weight;
			arcSetlength++;//每读入一条边，边的数量加1

		}
		fclose(fArc);
	}

	ALGraph G;
	//初始化G
	memset(&G, 0, sizeof(ALGraph));
	createALGraph(&G, vSet, vSetlength, arcSet, arcSetlength);
	printALGraph(G);
	printf("============\n");

	MGraph mG;

	//对邻接矩阵初始化
	for(int index = 0; index < MAX_VERTEX_NUM; index++)
	{
		memset(mG.arcs[index], INF, sizeof(ArcCell) * MAX_VERTEX_NUM);
	}
	switchALGToMG(G, &mG);
	printMGraph(mG);
}

