#include <cassert>
#include <iostream>
#include <vector>
#include "shell_sort.h"

void _shell_sort::shell_sort(int* arr,int n) {
	if (arr == nullptr || n <= 0) return;
	for (int gap = n >> 1; gap > 0; gap/=2) 
		for (int i = gap; i < n; ++i) {
			int temp = arr[i];
			int left = i-gap;
			while (left >= 0 && arr[left] > temp) {
				arr[left+gap] = arr[left];
				left-= gap;
			}
			arr[left + gap] = temp;
		}

}
// 辅助函数：打印数组
void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// 辅助函数：检查数组是否已排序（升序）
bool isSorted(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

// 辅助函数：创建一个整数数组的副本（用于测试）
std::vector<int> createVector(const int* arr, int size) {
    std::vector<int> vec;
    for (int i = 0; i < size; ++i) {
        vec.push_back(arr[i]);
    }
    return vec;
}

void _shell_sort::test_shell_sort() {
    std::cout << "开始测试希尔排序..." << std::endl;

    // ==================== 测试用例 1: 正常情况 ====================
    std::cout << "\n--- 测试用例 1: 正常情况 ---" << std::endl;
    int arr1[] = { 64, 34, 25, 12, 22, 11, 90 };
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    // 保存原始副本用于打印
    std::vector<int> original1 = createVector(arr1, n1);

    std::cout << "原始数组: ";
    printArray(original1); // 打印原始副本

    // 调用你的排序函数 (直接对 C 数组操作)
    _shell_sort::shell_sort(arr1, n1);

    std::vector<int> sorted1 = createVector(arr1, n1); // 创建排序后副本用于验证和打印
    std::cout << "排序后数组: ";
    printArray(sorted1);

    // 验证结果 (使用 vector 副本)
    assert(isSorted(sorted1));
    std::cout << " 测试用例 1 通过！" << std::endl;

    // ==================== 测试用例 2: 已排序数组 ====================
    std::cout << "\n--- 测试用例 2: 已排序数组 ---" << std::endl;
    int arr2[] = { 1, 2, 3, 4, 5, 6 };
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    std::vector<int> original2 = createVector(arr2, n2);

    std::cout << "原始数组: ";
    printArray(original2);

    _shell_sort::shell_sort(arr2, n2);

    std::vector<int> sorted2 = createVector(arr2, n2);
    std::cout << "排序后数组: ";
    printArray(sorted2);

    // 验证结果
    assert(isSorted(sorted2));
    std::cout << " 测试用例 2 通过！" << std::endl;

    // ==================== 测试用例 3: 逆序数组 ====================
    std::cout << "\n--- 测试用例 3: 逆序数组 ---" << std::endl;
    int arr3[] = { 6, 5, 4, 3, 2, 1 };
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    std::vector<int> original3 = createVector(arr3, n3);

    std::cout << "原始数组: ";
    printArray(original3);

    _shell_sort::shell_sort(arr3, n3);

    std::vector<int> sorted3 = createVector(arr3, n3);
    std::cout << "排序后数组: ";
    printArray(sorted3);

    // 验证结果
    assert(isSorted(sorted3));
    std::cout << " 测试用例 3 通过！" << std::endl;

    // ==================== 测试用例 4: 单个元素 ====================
    std::cout << "\n--- 测试用例 4: 单个元素 ---" << std::endl;
    int arr4[] = { 42 };
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    std::vector<int> original4 = createVector(arr4, n4);

    std::cout << "原始数组: ";
    printArray(original4);

    _shell_sort::shell_sort(arr4, n4);

    std::vector<int> sorted4 = createVector(arr4, n4);
    std::cout << "排序后数组: ";
    printArray(sorted4);

    // 验证结果
    assert(isSorted(sorted4));
    std::cout << " 测试用例 4 通过！" << std::endl;

    // ==================== 测试用例 5: 空数组 ====================
    std::cout << "\n--- 测试用例 5: 空数组 ---" << std::endl;
    int* arr5 = nullptr;
    int n5 = 0;

    std::cout << "调用排序函数处理空数组 (指针为 nullptr, 大小为 0) ..." << std::endl;

    _shell_sort::shell_sort(arr5, n5);

    std::cout << " 测试用例 5 通过！(没有崩溃)" << std::endl;

    // ==================== 测试用例 6: 零大小数组 (非nullptr) ====================
    std::cout << "\n--- 测试用例 6: 零大小数组 (非nullptr) ---" << std::endl;
    int arr_dummy; // Just to have an address, value doesn't matter
    int* arr6 = &arr_dummy; // Point to some valid memory (value irrelevant)
    int n6 = 0; // But size is 0

    std::cout << "调用排序函数处理零大小数组 (指针有效, 大小为 0) ..." << std::endl;

    _shell_sort::shell_sort(arr6, n6);

    std::cout << " 测试用例 6 通过！(没有崩溃)" << std::endl;


    // ==================== 测试用例 7: 重复元素 ====================
    std::cout << "\n--- 测试用例 7: 重复元素 ---" << std::endl;
    int arr7[] = { 5, 2, 8, 2, 9, 1, 5, 5 };
    int n7 = sizeof(arr7) / sizeof(arr7[0]);
    std::vector<int> original7 = createVector(arr7, n7);

    std::cout << "原始数组: ";
    printArray(original7);

    _shell_sort::shell_sort(arr7, n7);

    std::vector<int> sorted7 = createVector(arr7, n7);
    std::cout << "排序后数组: ";
    printArray(sorted7);

    // 验证结果
    assert(isSorted(sorted7));
    std::cout << " 测试用例 7 通过！" << std::endl;

    // ==================== 测试用例 8: 边界值 (最大最小) ====================
    std::cout << "\n--- 测试用例 8: 边界值 ---" << std::endl;
    int arr8[] = { INT_MAX, INT_MIN, 0, 100, -50, INT_MAX - 1, INT_MIN + 1 };
    int n8 = sizeof(arr8) / sizeof(arr8[0]);
    std::vector<int> original8 = createVector(arr8, n8);

    std::cout << "原始数组: ";
    printArray(original8);

    _shell_sort::shell_sort(arr8, n8);

    std::vector<int> sorted8 = createVector(arr8, n8);
    std::cout << "排序后数组: ";
    printArray(sorted8);

    // 验证结果
    assert(isSorted(sorted8));
    std::cout << " 测试用例 8 通过！" << std::endl;

    // ==================== 总结 ====================
    std::cout << "\n🎉 所有测试用例均通过！希尔排序实现正确。" << std::endl;

}