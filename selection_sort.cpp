#include <iostream>
#include <cassert>
#include "selection_sort.h"

inline void _selection_sort::swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void _selection_sort::selection_sort(int* arr,int n) {
	if (!arr || n <= 0)return;
	int left = 0;
	int right = n - 1;
	while (left < right) {
		int minIndex = left;
		int maxIndex = right;
		for (int i = left; i <= right; ++i) {
			if (arr[i] < arr[minIndex]) minIndex = i;
			if (arr[i] > arr[maxIndex]) maxIndex = i;
		}
		if (minIndex != left) {
			swap(&arr[minIndex],&arr[left]);
			if (maxIndex == left) maxIndex = minIndex;
		}
		if (maxIndex != right) swap(&arr[maxIndex],&arr[right]);
		++left;
		--right;
	}


}

void _selection_sort::test_selection_sort() {
    using namespace  _selection_sort;
    std::cout << "开始测试 selection_sort 函数...\n";

    // --- Test Case 1: Normal unsorted array ---
    {
        int arr[] = { 64, 25, 12, 22, 11, 90, 5 };
        int n = sizeof(arr) / sizeof(arr[0]);
        std::cout << "\n测试用例 1 - 普通无序数组:\n";
        std::cout << "排序前: ";
        for (int i = 0; i < n; ++i) std::cout << arr[i] << " ";
        std::cout << "\n";

        selection_sort(arr, n);

        std::cout << "排序后: ";
        bool is_sorted = true;
        for (int i = 0; i < n; ++i) {
            std::cout << arr[i] << " ";
            if (i > 0 && arr[i] < arr[i - 1]) {
                is_sorted = false;
            }
        }
        std::cout << "\n";
        assert(is_sorted); // Basic check if sorted
        std::cout << "断言通过: 数组已正确排序。\n";
    }

    // --- Test Case 2: Already sorted array ---
    {
        int arr[] = { 1, 2, 3, 4, 5 };
        int n = sizeof(arr) / sizeof(arr[0]);
        std::cout << "\n测试用例 2 - 已排序数组:\n";
        std::cout << "排序前: ";
        for (int i = 0; i < n; ++i) std::cout << arr[i] << " ";
        std::cout << "\n";

        selection_sort(arr, n);

        std::cout << "排序后: ";
        bool is_sorted = true;
        for (int i = 0; i < n; ++i) {
            std::cout << arr[i] << " ";
            if (i > 0 && arr[i] < arr[i - 1]) {
                is_sorted = false;
            }
        }
        std::cout << "\n";
        assert(is_sorted);
        std::cout << "断言通过: 已排序数组保持不变。\n";
    }

    // --- Test Case 3: Reverse sorted array ---
    {
        int arr[] = { 10, 9, 8, 7, 6 };
        int n = sizeof(arr) / sizeof(arr[0]);
        std::cout << "\n测试用例 3 - 逆序数组:\n";
        std::cout << "排序前: ";
        for (int i = 0; i < n; ++i) std::cout << arr[i] << " ";
        std::cout << "\n";

        selection_sort(arr, n);

        std::cout << "排序后: ";
        bool is_sorted = true;
        for (int i = 0; i < n; ++i) {
            std::cout << arr[i] << " ";
            if (i > 0 && arr[i] < arr[i - 1]) {
                is_sorted = false;
            }
        }
        std::cout << "\n";
        assert(is_sorted);
        std::cout << "断言通过: 逆序数组已正确排序。\n";
    }

    // --- Test Case 4: Array with duplicates ---
    {
        int arr[] = { 5, 2, 8, 2, 9, 1, 5, 4 };
        int n = sizeof(arr) / sizeof(arr[0]);
        std::cout << "\n测试用例 4 - 包含重复元素的数组:\n";
        std::cout << "排序前: ";
        for (int i = 0; i < n; ++i) std::cout << arr[i] << " ";
        std::cout << "\n";

        selection_sort(arr, n);

        std::cout << "排序后: ";
        bool is_sorted = true;
        for (int i = 0; i < n; ++i) {
            std::cout << arr[i] << " ";
            if (i > 0 && arr[i] < arr[i - 1]) {
                is_sorted = false;
            }
        }
        std::cout << "\n";
        assert(is_sorted);
        std::cout << "断言通过: 包含重复元素的数组已正确排序。\n";
    }


    // --- Test Case 5: Single element array ---
    {
        int arr[] = { 42 };
        int n = sizeof(arr) / sizeof(arr[0]);
        std::cout << "\n测试用例 5 - 单元素数组:\n";
        std::cout << "排序前: ";
        for (int i = 0; i < n; ++i) std::cout << arr[i] << " ";
        std::cout << "\n";

        selection_sort(arr, n);

        std::cout << "排序后: ";
        for (int i = 0; i < n; ++i) std::cout << arr[i] << " ";
        std::cout << "\n";
        std::cout << "单元素数组无需排序，测试完成。\n";
    }

    // --- Test Case 6: Empty array (n=0) ---
    {
        int* arr = nullptr; // Represents an empty array
        int n = 0;
        std::cout << "\n测试用例 6 - 空数组 (n=0):\n";
        std::cout << "尝试对空数组排序...\n";
        selection_sort(arr, n); // Should handle gracefully
        std::cout << "空数组处理完成 (无崩溃)。\n";
    }

    // --- Test Case 7: Null pointer ---
    {
        int* arr = nullptr;
        int n = 5; // Size doesn't matter if arr is null
        std::cout << "\n测试用例 7 - 空指针 (arr=nullptr):\n";
        std::cout << "尝试对空指针排序...\n";
        selection_sort(arr, n); // Should handle gracefully
        std::cout << "空指针处理完成 (无崩溃)。\n";
    }


    std::cout << "\n所有测试用例均已通过!\n";
}