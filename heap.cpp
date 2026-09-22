#include <iostream>
#include <vector>
#include <algorithm> 
#include <cassert>   
#include "heap.h"
using namespace _heap_sort;
/*
*堆排序
*/

//下沉
void _heap_sort::swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
//建堆
//最后一个非叶子节点2/n-1,往左遍历
void _heap_sort::make_heap(int* arr, int n) {
	for (int i = n / 2 - 1; i >= 0; --i) {
		down(arr,n,i);
	}
}

//堆排序
void _heap_sort:: down(int* arr, int size, int index) {
	int tp = arr[index];
	int parent = index;
	while (1) {
		int m_val = (parent << 1) + 1;
		int r = (parent << 1) + 2;
		if (r<size && arr[r]>arr[m_val]) m_val = r;
		if (m_val >= size || arr[m_val] <= tp) {
			arr[parent] = tp;
			break;
		}
		arr[parent] = arr[m_val];
		parent = m_val;
	}
 }


void _heap_sort::heap_sort(int* arr, int n) {
	if (!arr || n <= 1) return;
	make_heap(arr,n);
	for (int i = n - 1; i > 0; --i) {
		swap(&arr[0],&arr[i]);
		down(arr,i,0);
	}

}






// 辅助函数：打印数组
void printArray(const std::vector<int>& arr, const std::string& description = "") {
	if (!description.empty()) {
		std::cout << description << ": ";
	}
	for (const int& element : arr) {
		std::cout << element << " ";
	}
	std::cout << std::endl;
}

// 测试函数：对给定数组执行堆排序并验证结果
void testHeapSort(std::vector<int> arr, const std::string& testName) {
	std::cout << "\n--- Running Test: " << testName << " ---" << std::endl;
	printArray(arr, "Original Array");

	// 调用你的堆排序函数
	// 注意：需要传递底层数组指针和大小
	heap_sort(arr.data(), static_cast<int>(arr.size()));

	printArray(arr, "Sorted Array");

	// 验证排序结果是否正确 (升序)
	bool isCorrectlySorted = std::is_sorted(arr.begin(), arr.end());
	if (isCorrectlySorted) {
		std::cout << "Test Result: PASSED" << std::endl;
	}
	else {
		std::cout << "Test Result: FAILED" << std::endl;
	}
	assert(isCorrectlySorted && "Array should be sorted in ascending order!");
}


void  _heap_sort::test_heap_sort() {
	std::cout << "Testing Heap Sort Implementation..." << std::endl;

	// --- 测试用例 ---

	// 1. 普通无序数组
	testHeapSort({ 64, 34, 25, 12, 22, 11, 90 }, "Random Array");

	// 2. 已经排序好的数组 (最好情况)
	testHeapSort({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }, "Already Sorted Array");

	// 3. 逆序数组 (最坏情况 - 对堆排序来说，各种情况复杂度相近)
	testHeapSort({ 9, 8, 7, 6, 5, 4, 3, 2, 1 }, "Reverse Sorted Array");

	// 4. 包含重复元素的数组
	testHeapSort({ 5, 2, 8, 2, 9, 1, 5, 4 }, "Array with Duplicates");

	// 5. 单个元素
	testHeapSort({ 42 }, "Single Element Array");

	// 6. 空数组 (边界条件)
	std::vector<int> empty_arr = {};
	std::cout << "\n--- Running Test: Empty Array ---" << std::endl;
	printArray(empty_arr, "Original Array");
	heap_sort(empty_arr.data(), static_cast<int>(empty_arr.size()));
	printArray(empty_arr, "Sorted Array");
	std::cout << "Test Result: PASSED (Empty array handled)" << std::endl;

	// 7. 两个元素
	testHeapSort({ 2, 1 }, "Two Elements Array");

	// 8. 较大随机数组
	std::vector<int> large_random_arr;
	// 生成一个较大的随机数组进行测试
	const int LARGE_SIZE = 1000;
	large_random_arr.reserve(LARGE_SIZE);
	srand(42); // 固定种子以便复现
	for (int i = 0; i < LARGE_SIZE; ++i) {
		large_random_arr.push_back(rand() % 10000); // 0 到 9999 的随机数
	}
	testHeapSort(large_random_arr, "Large Random Array (Size 1000)");

	std::cout << "\nAll tests completed." << std::endl;

}