#include <stdio.h>
#include <malloc.h>
#include <cstring>
/*
	题目：DFS

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

typedef struct ArcNode //单链表中数据节点的信息
{
	//int weight;//权值
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
int createALGraph(ALGraph *G, int vSet[], int vSetlength, int arcSet[][2], int arcSetlength)
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

		//生成一个包含dest的弧节点，插入到以src为源点的头节点之后
		ArcNode *arcNodePtr = (ArcNode *)malloc(sizeof(ArcNode));
		arcNodePtr->adjvex = dest;

		//头插法，插入到以src为源点的头节点之后
		arcNodePtr->nextArc = G->vertices[src].firstArc;
		G->vertices[src].firstArc = arcNodePtr;

		//以dest为源点
		ArcNode *arcNodePtr2 = (ArcNode *)malloc(sizeof(ArcNode));
		arcNodePtr2->adjvex = src;

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

void printALGraph(ALGraph G)
{
	for(int i = 1; i <= G.vexnum; i++) //顶点索引从1开始
	{
		int src = G.vertices[i].data; //源点
		ArcNode *pNextArc = G.vertices[i].firstArc; //源点的第一条边

		while (pNextArc != NULL)
		{
			printf("%d----->%d\n", src, pNextArc->adjvex);
			pNextArc = pNextArc->nextArc;
		}
	}
}

int visit[MAX_VERTEX_NUM] = {0};

void DFS(ALGraph G,int vertex)
{
	printf("%d ",vertex);//访问顶点vertex
	visit[vertex]=1;//标记访问
	
	//寻找vertex未被访问的邻居顶点
	ArcNode *nextArcNode=G.vertices[vertex].firstArc;
	while(nextArcNode!=NULL)
	{
		int neighborVertex=nextArcNode->adjvex;
		if(visit[neighborVertex]==0)//邻居顶点未被访问
		{
			DFS(G,neighborVertex);
		}
		//邻居节点访问后，访问下一个未被访问的邻居节点,进入循环
		nextArcNode=nextArcNode->nextArc;
	}
	
}



void DFSTraverse(ALGraph G)
{
	for(int v = 1; v <= G.vexnum; v++) //v从索引1开始
	{
		if(visit[v] == 0) //i号顶点未被访问
		{
			DFS(G, v);
		}
	}
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



	ALGraph G;
	//初始化G
	memset(&G, 0, sizeof(ALGraph));
	createALGraph(&G, vSet, vSetlength, arcSet, arcSetlength);
	//printALGraph(G);
	
	DFSTraverse(G);

}