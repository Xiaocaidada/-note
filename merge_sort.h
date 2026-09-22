#pragma once

//命名空间：防止函数命名冲突
namespace _merge_sort {
	
	//插入排序，用于优化归并排序（其他排序也可以）
	void insert_sort(int* arr, int m, int n);

	//基本的归并排序——递归版
	void merge_base_recursion(int* arr,int i,int j);

	//基本的归并排序——非递归版
	void merge_base(int*arr,int n);

	//三个优化结合后的优化版本——递归版
	void final_merge_recursion(int*arr,int i,int j,int*tp);

	//三个优化结合后的优化版本——非递归版
	void final_merge(int*arr,int n);

	//归并排序，这个只是提供接口，进行简单合法判断，不进行排序
	void merge_sort(int*arr,int n);

	//这个是测试代码，用来测试排序正确性，可以把代码提交给AI，生成一份测试代码
	void test_merge_sort();
}