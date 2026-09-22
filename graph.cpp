#include "graph.h"
#include <iostream>

#include <queue>
#include <deque>
#include <limits.h>
#include <functional>
#include "union_find.h"
#include <stack>


using namespace std;

bool flag[MaxVexNum];


//找到节点i的第一个相邻节点
int firstNeighbor(MGraph* h,int i) {
	for (int n = 0; n < h->vertexNum; n++) {
		if (h->edges[i][n]!=INT_MAX) {
			return n;
		}
	}
	return -1;
}
//找到i除了j之外的下一个节点
int nextNeighbor(MGraph* h, int i, int j) {
	for (int n = j+1; n < h->vertexNum; n++) {
		if (h->edges[i][n]!=INT_MAX) {
			return n;
		}
	}
	return -1;
}

//初始化标记数组
void initFlag() {
	for (int i = 0; i < MaxVexNum; i++) {
		flag[i] = false;
	}
}

//深度优先遍历算法DFS
void dfs(MGraph* g) {
	initFlag();
	for (int i = 0; i < g->vertexNum; i++) {
		if (!flag[i]) {
			dfs(g, i);
		}
	}

}

void dfs(MGraph* g, int i) {
	cout << "访问节点：" << g->vex[i] << endl;
	flag[i] = true;
	for (int neighbor = firstNeighbor(g, i); neighbor != -1; neighbor = nextNeighbor(g, i, neighbor)) {
		if (!flag[neighbor]) {
			dfs(g, neighbor);
		}
	}
}

//广度优先遍历算法BFS
void bfs(MGraph*g) {
	initFlag();
	for (int i = 0; i < g->vertexNum; i++) {
		if (!flag[i]) {
			bfs(g, i);
		}
	}
}
void bfs(MGraph* g, int i) {
	deque<int> deq;
	flag[i] = true;
	deq.push_back(i);
	while (!deq.empty()) {
		int visited = deq.front();
		deq.pop_front();
		cout << "访问节点：" << g->vex[visited] << endl;
		for (int neighbor = firstNeighbor(g,visited); neighbor != -1; neighbor = nextNeighbor(g, visited, neighbor)) {
			if (!flag[neighbor]) {
				flag[neighbor] = true;
				deq.push_front(neighbor);//入队时候必须标记true，防止重复入队
			}
		}
	}

}

//获得边<x,y>或(x,y)的权值
int get_edge_value(MGraph* g, int i, int j) {
	return g->edges[i][j];
}

//判断节点i,j直接是否相邻
bool adjacent(MGraph* g, int i, int j) {
	return g->edges[i][j] != INT_MAX;
}

//最小生成树算法
void prim(MGraph* g, int i) {
	int minWeight[MaxVexNum]; //记录每个节点加入最小生成树最小边权值
	int adjVex[MaxVexNum]; //记录每个节点最小权值边的相邻节点
	bool isJoin[MaxVexNum];
	int total_weight = 0;
	//初始化
	for (int j = 0; j < g->vertexNum; j++) {
		minWeight[j] = get_edge_value(g,j,i);
		adjVex[j] = i;
		isJoin[j] = false;
	}
	isJoin[i] = true;
	//遍历，从minWeight中找到最小权值以及对应的节点，加入生成数
	for (int j = 0; j < g->vertexNum-1; j++) {

		//挑选未加入树且加入代价最小的节点
		int k = -1;
		int kWeight = INT_MAX;
		for (int n = 0; n < g->vertexNum; n++) {

			if (minWeight[n] < kWeight && !isJoin[n]) {
				k = n;
				kWeight = minWeight[n];
			}
		}
		//图不连通
		if (k == -1) {
			cout << "图不连通" << endl;
			return;
		}
		cout << "加入树的节点:" << k << "权值:" << kWeight << endl;
		isJoin[k] = true;
		total_weight += kWeight;
		//更新minWeight
		for (int p = 0; p < g->vertexNum; p++) {
			int p_to_k = get_edge_value(g, k, p);
			if (minWeight[p] > p_to_k&&!isJoin[p]) {
				minWeight[p] = p_to_k;
				adjVex[p] = k;
			}
		}
	}

	cout << "最小生成树的权值为:" << total_weight << endl;

}

//kruskal算法实现最小生成树
typedef struct EdType{
	int start;
	int end;
	int weight;
	bool operator>(const EdType& e)const {
		return weight > e.weight;
	}
} Edge;

void kruskal(MGraph* g) {
	priority_queue<Edge, deque<Edge>, greater<Edge>> deque;
	int edge_count = 0;
	int total_weight = 0;
	//两个节点如果存在边，创建边对象放进优先级队列
	for (int i = 0; i < g->vertexNum; i++) {
		for (int j = i+1; j < g->vertexNum; j++) {
			if (adjacent(g, i, j)) {
				Edge temp;
				temp.start = i;
				temp.end = j;
				temp.weight = get_edge_value(g,i,j);
				deque.push(temp);
			}
		}
	}
	int union_find_arr[MaxVexNum];
	init(union_find_arr,g->vertexNum);
	while (!deque.empty()) {
		Edge minEdge= deque.top();
		deque.pop();
		int i_arr = find(union_find_arr,minEdge.start);
		int j_arr = find(union_find_arr, minEdge.end);
		//处于不同的集合
		if (i_arr != j_arr) {
			++edge_count;
			printf("边为<%d,%d>,权值为%d ",i_arr,j_arr,minEdge.weight);
			total_weight += minEdge.weight;
			_union(union_find_arr,i_arr,j_arr);
		}
	}
	if (edge_count != g->vertexNum - 1) {
		cout << "图不连通" << endl;
		return;
	}

	cout << "最小生成树总权值为:" << total_weight << endl;
}


//Dijkstra单源最短路径算法
void dijkstra(MGraph* g, int i) {
	bool isJoin[MaxVexNum];
	int minRoad[MaxVexNum], path[MaxVexNum];
	for (int j = 0; j < g->vertexNum; j++) {
		isJoin[j] = false;
		minRoad[j] = get_edge_value(g,i,j);
		path[j] = i;
		if (j == i) {
			isJoin[j] = true;
			minRoad[j] = 0;
			path[i] = -1;
		}
	}
	//从最短路径数组找权值最小节点，标记为确认,更改相邻节点
	int count = g->vertexNum-1;
	while (count--) {
		int k = -1;
		int weight = INT_MAX;
		for (int j = 0; j < g->vertexNum; j++) {
			if (!isJoin[j] && minRoad[j] < weight) {
				weight = minRoad[j];
				k = j;
			}		
		}
		if (k == -1) {
			cout << "图不连通管" << endl;
			return;
		}
		//标记到源路径最短节点为true，记录path,并且修改相邻节点
		isJoin[k] = true;
		for (int w = firstNeighbor(g, k); w != -1; w = nextNeighbor(g, k, w)) {
			int new_min_weight = minRoad[k] + get_edge_value(g, k, w);
			if (!isJoin[w]&&new_min_weight<minRoad[w]) {
				minRoad[w] = new_min_weight;
				path[w] = k;
			}
		}
	}
	printf("Dijkstra最短路径结果如下：\n");
	for (int m = 0; m < g->vertexNum; m++) {
		printf("节点 %d 到 %d 的最短路径 %d ,节点%d的前驱节点为:%d\n",m,i,minRoad[m],m,path[m]);
	}
}


void printPath(int path[MaxVexNum][MaxVexNum], int p, int q) {
	if (path[p][q] == -1) {
		printf("%d -> ", p);
		return;
	}
	printPath(path, p, path[p][q]);
	printf("%d -> ", path[p][q]);
}


// 打印路径的辅助函数（需补充实现）
void print(int path[MaxVexNum][MaxVexNum], int minRoad[MaxVexNum][MaxVexNum], int p, int q) {
	printf("节点%d到%d的最短距离：%d\n", p, q, minRoad[p][q]);
	printf("路径：");
	printPath(path, p, q);
	printf("%d\n", q);
}



//floyd多源最短路线算法
void floyd(MGraph*g, int p,int q) {
	int path[MaxVexNum][MaxVexNum], minRoad[MaxVexNum][MaxVexNum];
	for (int i = 0; i < g->vertexNum; i++) {
		for (int j = 0; j < g->vertexNum; j++) {
			path[i][j] = -1;
			minRoad[i][j] = get_edge_value(g, i, j);
			if (i == j) {
				minRoad[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < g->vertexNum; i++) {
		for (int m = 0; m < g->vertexNum; m++) {
			for (int n = 0; n < g->vertexNum; n++) {
				// 若i→k和k→j都可达，且经k中转的路径更短，则更新
				if (minRoad[m][i] != INT_MAX && minRoad[i][n] != INT_MAX
					&& minRoad[m][i] + minRoad[i][n] < minRoad[m][n]) {
					minRoad[m][n] = minRoad[m][i] + minRoad[i][n];
					path[m][n] = i;  // 记录j的前驱为k
				}
			}
		}
	}
	print(path, minRoad, p, q);
}

//求一个顶点的入度
int inDegree(MGraph*g,int i) {
	int count = 0;
	for (int j = 0; j < g->vertexNum; j++) {
		if (adjacent(g, j, i)) {
			++count;
		}
	}
	return count;
}
//求一个顶点的出度
int outDegree(MGraph*g,int i) {
	int count = 0;
	for (int j = 0; j < g->vertexNum; j++) {
		if (adjacent(g, i, j)) {
			++count;
		}
	}
	return count;
}


//拓扑排序
void topoLogicalSort(MGraph* g) {
	deque<int> deq;
	int indegree[MaxVexNum];
	int sort_result[MaxVexNum];
	int index = 0;
	//初始化入度数组
	for (int i = 0; i < g->vertexNum; i++) {
		indegree[i] = inDegree(g,i);
		if (indegree == 0) {
			deq.push_back(i);
			sort_result[index++] = i;
		}
	}
	while (!deq.empty()) {
		int head= deq.front();
		deq.pop_front();
		for (int neighbor = firstNeighbor(g, head); neighbor != -1; neighbor = nextNeighbor(g, head, neighbor)) {
			--indegree[neighbor];
			if (indegree[neighbor] == 0) {
				deq.push_back(neighbor);
				sort_result[index++] = neighbor;
			}
		}
	}
	if (index != g->vertexNum) {
		cout << "拓扑排序失败,不满足有向无环图" << endl;
		return;
	}
	for (int i = 0; i < g->vertexNum; i++) {
		printf("排名: %d ,节点为: %d\n",i+1,sort_result[i]);
	}
}


















