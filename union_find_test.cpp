#include <stdio.h>
#include <stdlib.h>
#include "union_find.h"

// 定义最大节点数量（需与实现中保持一致）
#define MAX_NODE_COUNT 10

// 打印并查集数组当前状态
inline void printUnionFind(int arr[], int size) {
    printf("并查集当前状态: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

inline void test_union_find() {
    int uf[MAX_NODE_COUNT];

    // 测试1: 初始化并查集
    printf("=== 测试初始化 ===\n");
    init(uf,MAX_NODE_COUNT);  // 初始化每个节点为独立集合（值为-1）
    printUnionFind(uf, MAX_NODE_COUNT);

    // 测试2: 初始状态下的查找操作
    printf("\n=== 测试初始查找 ===\n");
    for (int i = 0; i < 5; i++) {
        printf("节点%d的根节点: %d\n", i, find(uf, i));
    }

    // 测试3: 合并操作及效果验证
    printf("\n=== 测试合并操作 ===\n");
    _union(uf, 0, 1);  // 合并0和1
    printf("合并0和1后: ");
    printUnionFind(uf, MAX_NODE_COUNT);
    printf("节点0的根: %d, 节点1的根: %d (应相同)\n", find(uf, 0), find(uf, 1));

    _union(uf, 2, 3);  // 合并2和3
    printf("合并2和3后: ");
    printUnionFind(uf, MAX_NODE_COUNT);

    _union(uf, 0, 2);  // 合并0和2（间接合并1、3）
    printf("合并0和2后: ");
    printUnionFind(uf, MAX_NODE_COUNT);
    printf("节点1的根: %d, 节点3的根: %d (应相同)\n", find(uf, 1), find(uf, 3));

    // 测试4: 路径压缩效果验证
    printf("\n=== 测试路径压缩 ===\n");
    // 构建一条较长的链
    _union(uf, 4, 5);
    _union(uf, 5, 6);
    _union(uf, 6, 7);
    printf("合并4-5-6-7后: ");
    printUnionFind(uf, MAX_NODE_COUNT);

    find(uf, 7);  // 触发路径压缩
    printf("查找节点7后（路径压缩）: ");
    printUnionFind(uf, MAX_NODE_COUNT);
    printf("节点7的根: %d, 节点5的根: %d (应相同且路径被压缩)\n", find(uf, 7), find(uf, 5));

    // 测试5: 按大小合并验证
    printf("\n=== 测试按大小合并 ===\n");
    // 合并两个不同大小的集合
    _union(uf, 0, 4);  // 0的集合大小为4，4的集合大小为4（等大合并）
    printf("合并0和4的集合后: ");
    printUnionFind(uf, MAX_NODE_COUNT);
    printf("新根节点的值: %d (应等于-8，即两个大小为4的集合合并)\n", find(uf, 0));


}
