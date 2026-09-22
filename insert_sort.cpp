#include <iostream>
#include "insert_sort.h"
using namespace _insert_sort;
void _insert_sort::insert_sort(int* arr, int n) {
	if (!arr || n <= 0) return;
	for (int i = 1; i < n; ++i) {
		if (arr[i] < arr[i - 1]) {
			int m = i - 1;
			int temp = arr[i];
			while (m >= 0 && arr[m] > temp) {
				arr[m + 1] = arr[m];
				--m;
			}
			arr[m + 1] = temp;
		}
	}
}

// --- 辅助函数：打印数组 ---
void printArray(const int* arr, int n) {
    if (!arr || n <= 0) {
        std::cout << "[]"; // 打印空数组表示
        return;
    }
    std::cout << "[";
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i];
        if (i < n - 1) {
            std::cout << ", "; // 元素间用逗号和空格分隔
        }
    }
    std::cout << "]";
}
void _insert_sort::insert_sort_test() {
    std::cout << "Testing Insertion Sort:\n" << std::endl;

    // --- 测试用例 1: 一般无序数组 ---
    std::cout << "--- Test Case 1: Random Array ---" << std::endl;
    int arr1[] = { 64, 34, 25, 12, 22, 11, 90 };
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    std::cout << "Original array: ";
    printArray(arr1, n1);
    std::cout << std::endl;

    insert_sort(arr1, n1);

    std::cout << "Sorted array:   ";
    printArray(arr1, n1);
    std::cout << "\n" << std::endl;

    // --- 测试用例 2: 已经排序好的数组 ---
    std::cout << "--- Test Case 2: Already Sorted Array ---" << std::endl;
    int arr2[] = { 5, 10, 15, 20, 25 };
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    std::cout << "Original array: ";
    printArray(arr2, n2);
    std::cout << std::endl;

    insert_sort(arr2, n2);

    std::cout << "Sorted array:   ";
    printArray(arr2, n2);
    std::cout << "\n" << std::endl;


    // --- 测试用例 3: 逆序数组 ---
    std::cout << "--- Test Case 3: Reverse Sorted Array ---" << std::endl;
    int arr3[] = { 9, 7, 5, 3, 1 };
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    std::cout << "Original array: ";
    printArray(arr3, n3);
    std::cout << std::endl;

    insert_sort(arr3, n3);

    std::cout << "Sorted array:   ";
    printArray(arr3, n3);
    std::cout << "\n" << std::endl;

    // --- 测试用例 4: 包含重复元素的数组 ---
    std::cout << "--- Test Case 4: Array with Duplicates ---" << std::endl;
    int arr4[] = { 4, 5, 3, 3, 1, 2 };
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    std::cout << "Original array: ";
    printArray(arr4, n4);
    std::cout << std::endl;

    insert_sort(arr4, n4);

    std::cout << "Sorted array:   ";
    printArray(arr4, n4);
    std::cout << "\n" << std::endl;

    // --- 测试用例 5: 单个元素 ---
    std::cout << "--- Test Case 5: Single Element Array ---" << std::endl;
    int arr5[] = { 42 };
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    std::cout << "Original array: ";
    printArray(arr5, n5);
    std::cout << std::endl;

    insert_sort(arr5, n5);

    std::cout << "Sorted array:   ";
    printArray(arr5, n5);
    std::cout << "\n" << std::endl;

    // --- 测试用例 6: 空数组 (或大小为0) ---
    std::cout << "--- Test Case 6: Empty Array ---" << std::endl;
    int* arr6 = nullptr; // 模拟空指针
    int n6 = 0;
    std::cout << "Attempting to sort an empty/null array..." << std::endl;
    insert_sort(arr6, n6); // 应该安全返回，不崩溃
    std::cout << "Sort function handled null pointer correctly." << std::endl;
    std::cout << "\n" << std::endl;

    // --- 测试用例 7: 两个元素 ---
    std::cout << "--- Test Case 7: Two Elements Array ---" << std::endl;
    int arr7[] = { 2, 1 };
    int n7 = sizeof(arr7) / sizeof(arr7[0]);
    std::cout << "Original array: ";
    printArray(arr7, n7);
    std::cout << std::endl;

    insert_sort(arr7, n7);

    std::cout << "Sorted array:   ";
    printArray(arr7, n7);
    std::cout << "\n" << std::endl;



    std::cout << "All test cases completed." << std::endl;

}