#pragma once

//命名空间：防止函数名冲突
namespace _bubble_sort {

	//交换两个相邻元素
	void swap(int* a, int* b);

	//最基本的冒泡实现
	void bubble_sort1(int* arr, int n);
	//最基本的冒泡实现——递归
	void bubble_sort1_recursion(int* arr, int n);

	//优化1
	void bubble_sort2(int* arr, int n);

	//最终优化后冒泡排序
	void bubble_sort_final(int* arr, int n);
	void bubble_sort_final_recursion(int*arr,int n);


	//这里是测试函数,可以把代码交给AI生成一个测试函数在main中运行
	void test_bubble_sort();
}
