#include <climits>
#include <iostream>
#include "count_sort.h"
using namespace _count_sort;


void _count_sort::count_sort(int* arr, int n) {
    if (!arr || n <= 1) return;
	int max_v = INT_MIN;
	int min_v = INT_MAX;
	for (int i = 0; i < n; ++i) {
		if (min_v > arr[i]) min_v = arr[i];
		if (max_v < arr[i]) max_v = arr[i];
	}
	int range = max_v - min_v + 1;
	int* tp = new int[range];
	for (int i = 0; i < range; ++i) {
		tp[i] = 0;
	}
	for (int i = 0; i < n; ++i) {
		++tp[arr[i] - min_v];
	}
	for (int i = 1; i < range; ++i) {
		tp[i] = tp[i - 1] + tp[i];
	}
	int* res = new int[n];
	int _n = n;
	while (n--) {
		int target_index = tp[arr[n]-min_v] - 1;
		--tp[arr[n]-min_v];
		res[target_index] = arr[n];
	}
	for (int i = 0; i < _n; ++i) {
		arr[i] = res[i];
	}
	delete[] tp;
	delete[] res;
}

void _count_sort::test_count_sort() {
    std::cout << "开始测试 count_sort...\n";

    // 测试用例 1: 基本正数
    {
        int arr[] = { 4, 2, 2, 8, 3, 3, 1 };
        int size = sizeof(arr) / sizeof(arr[0]);
        std::cout << "\n测试用例 1 (基本正数):\n";
        std::cout << "排序前: ";
        for (int i = 0; i < size; ++i) std::cout << arr[i] << " ";
        std::cout << "\n";

        count_sort(arr, size);

        std::cout << "排序后: ";
        for (int i = 0; i < size; ++i) std::cout << arr[i] << " ";
        std::cout << "\n";
    }

    // 测试用例 2: 包含负数
    {
        int arr[] = { 3, -1, 2, -5, 0, 4, -2 };
        int size = sizeof(arr) / sizeof(arr[0]);
        std::cout << "\n测试用例 2 (包含负数):\n";
        std::cout << "排序前: ";
        for (int i = 0; i < size; ++i) std::cout << arr[i] << " ";
        std::cout << "\n";

        count_sort(arr, size);

        std::cout << "排序后: ";
        for (int i = 0; i < size; ++i) std::cout << arr[i] << " ";
        std::cout << "\n";
    }

    // 测试用例 3: 已排序
    {
        int arr[] = { 1, 2, 3, 4, 5 };
        int size = sizeof(arr) / sizeof(arr[0]);
        std::cout << "\n测试用例 3 (已排序):\n";
        std::cout << "排序前: ";
        for (int i = 0; i < size; ++i) std::cout << arr[i] << " ";
        std::cout << "\n";

        count_sort(arr, size);

        std::cout << "排序后: ";
        for (int i = 0; i < size; ++i) std::cout << arr[i] << " ";
        std::cout << "\n";
    }

    // 测试用例 4: 逆序
    {
        int arr[] = { 9, 7, 5, 3, 1 };
        int size = sizeof(arr) / sizeof(arr[0]);
        std::cout << "\n测试用例 4 (逆序):\n";
        std::cout << "排序前: ";
        for (int i = 0; i < size; ++i) std::cout << arr[i] << " ";
        std::cout << "\n";

        count_sort(arr, size);

        std::cout << "排序后: ";
        for (int i = 0; i < size; ++i) std::cout << arr[i] << " ";
        std::cout << "\n";
    }

    // 测试用例 5: 所有元素相同
    {
        int arr[] = { 7, 7, 7, 7 };
        int size = sizeof(arr) / sizeof(arr[0]);
        std::cout << "\n测试用例 5 (所有元素相同):\n";
        std::cout << "排序前: ";
        for (int i = 0; i < size; ++i) std::cout << arr[i] << " ";
        std::cout << "\n";

        count_sort(arr, size);

        std::cout << "排序后: ";
        for (int i = 0; i < size; ++i) std::cout << arr[i] << " ";
        std::cout << "\n";
    }

    // 测试用例 6: 单个元素
    {
        int arr[] = { 42 };
        int size = sizeof(arr) / sizeof(arr[0]);
        std::cout << "\n测试用例 6 (单个元素):\n";
        std::cout << "排序前: ";
        for (int i = 0; i < size; ++i) std::cout << arr[i] << " ";
        std::cout << "\n";

        count_sort(arr, size);

        std::cout << "排序后: ";
        for (int i = 0; i < size; ++i) std::cout << arr[i] << " ";
        std::cout << "\n";
    }

    // 测试用例 7: 空数组 (边界情况)
    {
        int* arr = nullptr; // 或者 int arr[0]; // C++允许零长度数组，但指针更常见
        int size = 0;
        std::cout << "\n测试用例 7 (空数组):\n";
        std::cout << "排序前: (空)\n";

        // 调用应能安全处理
        count_sort(arr, size);

        std::cout << "排序后: (空) - 安全处理\n";
    }


    std::cout << "\n测试完成。\n";
}