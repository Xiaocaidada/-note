#pragma once

#define MaxVexNum 100

extern bool flag[MaxVexNum]; //用于判断节点i是否被访问

typedef char VertexType; //节点数据类型
typedef int EdgeType;  //边的数据类型



typedef struct {
	VertexType vex[MaxVexNum];
	EdgeType edges[MaxVexNum][MaxVexNum];
	int vertexNum;
}MGraph;
/*
**Adjacent(G, x, y)：**判断图 G 是否存在边 < x , y > 或 ( x , y )。
**Neighbors(G, x)：**列出图 G 中与结点 x 邻接的边。
**InsertVertex(G, x)：**在图 G 中插入顶点 x 。
**DeleteVertex(G, x)：**从图 G 中删除顶点 x。
**AddEdge(G, x, y)：**若无向边 ( x , y )  或有向边 < x , y > 不存在，则向图 G 中添加该边。
**RemoveEdge(G, x, y)：**若无向边 ( x , y ) (x, y)(x,y) 或有向边 < x , y > <x,y><x,y> 存在，则从图 G 中删除该边。
**FirstNeighbor(G, x)：**求图 G 中顶点 x 的第一个邻接点，若有则返回顶点号。若 x 没有邻接点或图中不存在 x，则返回 -1。
**NextNeighbor(G, x, y)**：假设图 G 中顶点 y 是顶点 x 的一个邻接点，返回除 y 之外顶点 x 的下一个邻接点的顶点号，若 y 是 x 的最后一个邻接点，则返回 -1。
**Get\_edge\_value(G, x, y)：**获取图 G 中边 ( x , y )或 < x , y > 对应的权值。
**Set\_edge\_value(G, x, y, v)：**设置图 G 中边 ( x , y )或 < x , y >对应的权值为 v。
*/

int firstNeighbor(MGraph* g,int i); //找到i节点第一个邻接点
int nextNeighbor(MGraph * g,int i,int j);//找到i除j之外的另一个邻接点
int get_edge_value(MGraph* g,int i,int j);
bool adjacent(MGraph*g,int i,int j); //判断节点i,j直接是否相邻
int inDegree(MGraph* g,int i);
int outDegree(MGraph*g,int i);


//深度优先遍历
void dfs(MGraph* g);
void dfs(MGraph* g,int i);
//广度优先遍历
void bfs(MGraph* g); 
void bfs(MGraph* g,int i);
void initFlag();
//最小生成树算法
void prim(MGraph* g,int i);
void kruskal(MGraph*g);

//单源最短路径问题——Dijkstra算法
void dijkstra(MGraph*g,int i);
//多源最短路径问题——Floyd算法
void floyd(MGraph* g, int i, int j);

//拓扑排序
void topologicalSort(MGraph* g);











