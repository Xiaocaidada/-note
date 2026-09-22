#pragma once

/**
* 选择排序优化：同时选出最大值和最小值，以及去除与自身的交换
* 
* 
*/

namespace _selection_sort {
	void swap(int* a, int* b);


	void selection_sort(int* arr, int n);


	void test_selection_sort();
}

