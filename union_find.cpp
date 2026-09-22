#include "union_find.h"


/**
*原理：数组索引代表该元素,值指为指向父节点的索引
* 优化：路径压缩、降低树高度
* 
*/


void init(int arr[],int length) {
	for (int i = 0; i < length; i++) {
		arr[i] = -1;
	}
}


//返回元素i所处的集合
int find(int arr[], int i) {
	if (arr[i] <0) return i;
	int parent = find(arr, arr[i]);
	//路径压缩
	arr[i] = parent;
	return parent;
}



//将两个元素合并为一个集合
void _union(int arr[], int i, int j) {
	int i_parent = find(arr, i);
	int j_parent = find(arr, j);
	if (i_parent == j_parent) {
		return;
	}
	//将小树合并到大树中
	if (arr[i_parent] > arr[j_parent]) {
		arr[j_parent] += arr[i_parent];
		//i为小树
		arr[i_parent] = j_parent;
	}
	else {
		arr[i_parent] += arr[j_parent];
		arr[j_parent] = i_parent;

	}
}


