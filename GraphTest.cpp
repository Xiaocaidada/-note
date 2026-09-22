#include "graph.h"  // 包含图结构及接口定义
#include <stdio.h>
#include <limits.h>
#include <iostream>
using namespace std;


// 初始化一个标准测试图（5个顶点的连通图）
inline void initTestGraph(MGraph* g) {
    // 1. 初始化顶点信息
    g->vertexNum = 5;  // 顶点数量：5个（A~E）
    g->vex[0] = 'A';   // 顶点0：A
    g->vex[1] = 'B';   // 顶点1：B
    g->vex[2] = 'C';   // 顶点2：C
    g->vex[3] = 'D';   // 顶点3：D
    g->vex[4] = 'E';   // 顶点4：E

    // 2. 初始化邻接矩阵（无边时为INT_MAX，自身为0）
    for (int i = 0; i < g->vertexNum; i++) {
        for (int j = 0; j < g->vertexNum; j++) {
            g->edges[i][j] = INT_MAX;
        }
    }

    // 3. 添加无向边（权值均为正数，模拟实际场景）
    g->edges[0][1] = g->edges[1][0] = 2;   // A-B：权值2
    g->edges[0][3] = g->edges[3][0] = 5;   // A-D：权值5
    g->edges[1][2] = g->edges[2][1] = 3;   // B-C：权值3
    g->edges[1][4] = g->edges[4][1] = 7;   // B-E：权值7
    g->edges[2][4] = g->edges[4][2] = 1;   // C-E：权值1
    g->edges[3][4] = g->edges[4][3] = 4;   // D-E：权值4
    // 注意：B-D 无边（原示例中删除，避免干扰最小生成树唯一性）
}

// 初始化一个非连通图（用于测试算法容错性）
inline void initDisconnectedGraph(MGraph* g) {
    g->vertexNum = 4;  // 顶点：W(0), X(1), Y(2), Z(3)
    g->vex[0] = 'W';
    g->vex[1] = 'X';
    g->vex[2] = 'Y';
    g->vex[3] = 'Z';

    // 初始化邻接矩阵
    for (int i = 0; i < g->vertexNum; i++) {
        for (int j = 0; j < g->vertexNum; j++) {
            g->edges[i][j] =INT_MAX;
        }
    }

    // 添加边（W-X连通，Y-Z连通，但两组不连通）
    g->edges[0][1] = g->edges[1][0] = 2;   // W-X：权值2
    g->edges[2][3] = g->edges[3][2] = 3;   // Y-Z：权值3
}

// 测试1：验证图初始化及顶点信息
inline void testGraphInit(MGraph* g) {
    printf("\n===== 测试1：图初始化验证 =====\n");
    printf("预期顶点数量：5  实际：%d\n", g->vertexNum);
    printf("预期顶点顺序：A B C D E  实际：");
    for (int i = 0; i < g->vertexNum; i++) {
        printf("%c ", g->vex[i]);
    }
    printf("\n");
    // 验证：若顶点数量为5且顺序正确，则初始化成功
}

// 测试2：验证FirstNeighbor和NextNeighbor接口
inline void testNeighborInterfaces(MGraph* g) {
    printf("\n===== 测试2：邻接顶点接口验证 =====\n");

    // 2.1 测试顶点A(0)的第一个邻接点
    int firstA = firstNeighbor(g, 0);
    printf("顶点A(0)的第一个邻接点：预期B(1)  实际：");
    if (firstA == 1) printf("B(1) [正确]\n");
    else printf("%d [错误]\n", firstA);

    // 2.2 测试顶点B(1)的第一个邻接点
    int firstB = firstNeighbor(g, 1);
    printf("顶点B(1)的第一个邻接点：预期A(0)  实际：");
    if (firstB == 0) printf("A(0) [正确]\n");
    else printf("%d [错误]\n", firstB);

    // 2.3 测试顶点A(0)在B(1)之后的下一个邻接点
    int nextA = nextNeighbor(g, 0, 1);
    printf("A(0)在B(1)之后的邻接点：预期D(3)  实际：");
    if (nextA == 3) printf("D(3) [正确]\n");
    else printf("%d [错误]\n", nextA);

    // 2.4 测试顶点A(0)在D(3)之后的下一个邻接点（无）
    int nextA2 = nextNeighbor(g, 0, 3);
    printf("A(0)在D(3)之后的邻接点：预期-1  实际：");
    if (nextA2 == -1) printf("-1 [正确]\n");
    else printf("%d [错误]\n", nextA2);
}

// 测试3：验证Get_edge_value接口
inline void testEdgeValueInterface(MGraph* g) {
    printf("\n===== 测试3：边权值接口验证 =====\n");

    // 3.1 测试A(0)-B(1)的权值
    int wAB = get_edge_value(g, 0, 1);
    printf("A-B权值：预期2  实际：%d  ", wAB);
    if (wAB == 2) printf("[正确]\n");
    else printf("[错误]\n");

    // 3.2 测试B(1)-C(2)的权值
    int wBC = get_edge_value(g, 1, 2);
    printf("B-C权值：预期3  实际：%d  ", wBC);
    if (wBC == 3) printf("[正确]\n");
    else printf("[错误]\n");

    // 3.3 测试C(2)-E(4)的权值（最小权值边）
    int wCE = get_edge_value(g, 2, 4);
    printf("C-E权值：预期1  实际：%d  ", wCE);
    if (wCE == 1) printf("[正确]\n");
    else printf("[错误]\n");

    // 3.4 测试A(0)-C(2)的权值（无边）
    int wAC = get_edge_value(g, 0, 2);
    printf("A-C权值（无边）：预期INT_MAX  实际：");
    if (wAC == INT_MAX) printf("INT_MAX [正确]\n");
    else printf("%d [错误]\n", wAC);
}

// 测试4：验证Prim算法（连通图）
inline void testPrimConnected(MGraph* g) {
    printf("\n===== 测试4：Prim算法（连通图） =====\n");
    printf("从顶点A(0)开始构建最小生成树：\n");
    printf("预期选中的边及权值：\n");
    printf("(A-B:2) → (B-C:3) → (C-E:1) → (E-D:4)  总权值：10\n");
    printf("实际输出：\n");
    prim(g, 0);  // 调用Prim算法

    printf("\n从顶点C(2)开始构建最小生成树：\n");
    printf("预期选中的边及权值：\n");
    printf("(C-E:1) → (C-B:3) → (B-A:2) → (E-D:4)  总权值：10\n");
    printf("实际输出：\n");
    prim(g, 2);  // 从另一个顶点开始
}

// 测试5：验证Prim算法（非连通图）
inline void testPrimDisconnected(MGraph* g) {
    printf("\n===== 测试5：Prim算法（非连通图） =====\n");
    printf("预期结果：提示“图不连通，无法生成最小生成树”\n");
    printf("实际输出：\n");
    prim(g, 0);  // 对非连通图调用Prim
}


// 测试Kruskal算法（连通图）
inline void testKruskalConnected() {
    MGraph graph;
    initTestGraph(&graph);
    cout << "===== 测试Kruskal算法（连通图） =====" << endl;
    cout << "预期最小生成树总权值：2+3+1+4 = 10" << endl;
    cout << "实际执行结果：" << endl;
    kruskal(&graph);
}

// 测试Kruskal算法（非连通图）
inline void testKruskalDisconnected() {
    MGraph graph;
    initDisconnectedGraph(&graph);
    cout << "\n===== 测试Kruskal算法（非连通图） =====" << endl;
    cout << "预期结果：提示图不连通" << endl;
    cout << "实际执行结果：" << endl;
    kruskal(&graph);
}



// 测试Floyd算法（连通图）
inline void testFloydConnected() {
    MGraph graph;
    initTestGraph(&graph); // 使用已有的连通图初始化函数
    printf("\n===== 测试Floyd算法（连通图）=====\n");

    // 测试多组节点对的最短路径
    printf("测试A(0)到E(4)的最短路径：\n");
    floyd(&graph, 0, 4);

    printf("\n测试B(1)到D(3)的最短路径：\n");
    floyd(&graph, 1, 3);

    printf("\n测试C(2)到A(0)的最短路径：\n");
    floyd(&graph, 2, 0);
}

// 测试Floyd算法（非连通图）
inline void testFloydDisconnected() {
    MGraph graph;
    initDisconnectedGraph(&graph); // 使用已有的非连通图初始化函数
    printf("\n===== 测试Floyd算法（非连通图）=====\n");

    // 测试连通分量内的路径
    printf("测试W(0)到X(1)的最短路径：\n");
    floyd(&graph, 0, 1);

    // 测试不同连通分量间的路径（应不可达）
    printf("\n测试W(0)到Y(2)的最短路径（非连通）：\n");
    floyd(&graph, 0, 2);
}






inline void test_graph() {
    // 初始化连通图并执行测试
    MGraph connectedGraph;
    initTestGraph(&connectedGraph);
    testGraphInit(&connectedGraph);
    testNeighborInterfaces(&connectedGraph);
    testEdgeValueInterface(&connectedGraph);
    testPrimConnected(&connectedGraph);

    // 初始化非连通图并执行测试
    MGraph disconnectedGraph;
    initDisconnectedGraph(&disconnectedGraph);
    testPrimDisconnected(&disconnectedGraph);

    testKruskalConnected();
    testKruskalDisconnected();
    testFloydConnected();
    testFloydDisconnected();

    printf("\n===== 所有测试结束 =====\n");
}