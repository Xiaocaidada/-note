#include <iostream>
#include <cassert> // 包含 assert 用于断言检查
#include <cstring> // 包含 memcpy 用于复制数组
#include "bubble_sort.h"
using namespace _bubble_sort;


//冒泡排序
/*
* 优化1：某论循环中未进行交换，则终止
* 优化2：记录每轮循环最后交换的位置i,i位置后的元素不需要再遍历
*/

void _bubble_sort::swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}


//基础版本
void _bubble_sort::bubble_sort1(int*arr,int n) {
    //进行简单判断:arr为空或者n<=1直接结束
    if (!arr || n <= 1)return;
    //进行n-1轮循环
    for (int i = 0; i < n - 1; ++i) {
        //由于每轮循环都会处理完一个数据，内部要比较的次数越来越少
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j],&arr[j+1]);
            }
        }
    }
}





void _bubble_sort::bubble_sort1_recursion(int*arr,int n) {
    //循环终止条件：n=1说明有n-1元素已经排序
    if (n <= 1) {
        return;
    }
    //比较相邻元素，让该轮最大元素放在末尾
    for (int j = 0; j < n - 1; ++j) {
        if (arr[j] > arr[j + 1]) {
            swap(&arr[j], &arr[j + 1]);
        }
    }
    //每次递归让n-1,缩小边界
    bubble_sort1_recursion(arr,n-1);
}


//优化一(非递归)：未交换提前终止
void _bubble_sort::bubble_sort2(int*arr,int n) {
    if (!arr || n <= 1)return;
    for (int i = 0; i < n - 1; ++i) {
        bool has_ex = false;
        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                has_ex = true;//记录该轮发生交换
            }
        }
        //如果未发生交换，则已经有序
        if (!has_ex)break;
    }
}





void _bubble_sort::bubble_sort_final(int* arr, int n) {
    if (!arr||n <= 1) return; 

    //unsorted_boundary记录最后一次交换位置(unsorted_boundary之后元素已经有序，不包括unsorted_boundary，换句话说：unsorted_boundary是需要参与比较的)
    int unsorted_boundary = n - 1; 

    while (unsorted_boundary > 0) {
        //记录新的最后一次交换位置
        int last_swap_index = 0; 
        //虽然i最大为unsorted_boundary-1,但i+1为unsorted_boundary，它参与比较
        for (int i = 0; i < unsorted_boundary; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                last_swap_index = i; 
            }
        }
        //将该轮最后一次交换位置赋给unsorted_boundary(如果未交换，循环会终止)
        unsorted_boundary = last_swap_index;
    }
}






void _bubble_sort::bubble_sort_final_recursion(int* arr, int n) {
    //unsorted_boundary之后元素已经排序(不包括unsorted_boundary指向元素)
    int unsorted_boundary = n - 1;
    if (!arr||unsorted_boundary <= 0)return; //与while循环条件类似
    int tp = 0;//记录新的最后一次交换位置
    for (int i = 0; i < unsorted_boundary; ++i) {
        if (arr[i] > arr[i + 1]) {
            swap(&arr[i], &arr[i + 1]);
            tp = i;
        }
    }
    //这里tp+1原因是进入下一轮递归后，tp+1值传递给n,n又会减1。
    // 多此一举原因是初始条件下用户传递n是元素数量，非最后一个元素索引
    bubble_sort_final_recursion(arr,tp+1);
}





// --- 辅助函数：打印数组 ---
void print_array(const int* arr, int size) {
    std::cout << "[";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << "]";
}

// --- 测试函数 ---
void _bubble_sort::test_bubble_sort() {
    using namespace _bubble_sort;
    std::cout << "开始测试 bubble_sort 函数...\n";

    // --- 测试用例 1: 空数组 ---
    {
        int arr[99] = {};
        int size = 0;
        print_array(arr,size);
        bubble_sort_final_recursion(arr, size); // 或者使用您原来的 bubble_sort(arr, size);
        print_array(arr, size);
        std::cout << "测试 1 (空数组): 通过 (无需验证)\n";
    }

    // --- 测试用例 2: 单个元素 ---
    {
        int arr[] = { 42 };
        int size = 1;
        int expected[] = { 42 };
        print_array(arr, size);
        bubble_sort_final(arr, size);
        assert(memcmp(arr, expected, sizeof(expected)) == 0);
        print_array(arr, size);
        std::cout << "测试 2 (单个元素): 通过\n";
    }

    // --- 测试用例 3: 已排序数组 ---
    {
        int arr[] = { 1, 2, 3, 4, 5 };
        int size = 5;
        int expected[] = { 1, 2, 3, 4, 5 };
        print_array(arr, size);
        bubble_sort_final(arr, size);
        assert(memcmp(arr, expected, sizeof(expected)) == 0);
        print_array(arr, size);
        std::cout << "测试 3 (已排序): 通过\n";
    }

    // --- 测试用例 4: 逆序数组 ---
    {
        int arr[] = { 5, 4, 3, 2, 1 };
        int size = 5;
        int expected[] = { 1, 2, 3, 4, 5 };
        print_array(arr, size);
        bubble_sort_final(arr, size);
        assert(memcmp(arr, expected, sizeof(expected)) == 0);
        print_array(arr,size);
        std::cout << "测试 4 (逆序): 通过\n";
    }

    // --- 测试用例 5: 随机顺序数组 ---
    {
        int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
        int size = 7;
        int expected[] = { 11, 12, 22, 25, 34, 64, 90 };
        print_array(arr, size);
        bubble_sort_final(arr, size);
        assert(memcmp(arr, expected, sizeof(expected)) == 0);
        print_array(arr,size);
        std::cout << "测试 5 (随机): 通过\n";
    }

    // --- 测试用例 6: 包含重复元素 ---
    {
        int arr[] = { 3, 7, 3, 1, 7, 1, 5 };
        int size = 7;
        int expected[] = { 1, 1, 3, 3, 5, 7, 7 };
        print_array(arr, size);
        bubble_sort_final(arr, size);
        assert(memcmp(arr, expected, sizeof(expected)) == 0);
        print_array(arr, size);
        std::cout << "测试 6 (重复元素): 通过\n";
    }

    // --- 测试用例 7: 两个元素 (正序) ---
    {
        int arr[] = { 2, 5 };
        int size = 2;
        int expected[] = { 2, 5 };
        print_array(arr, size);
        bubble_sort_final(arr, size);
        assert(memcmp(arr, expected, sizeof(expected)) == 0);
        print_array(arr, size);
        std::cout << "测试 7 (两元素正序): 通过\n";
    }

    // --- 测试用例 8: 两个元素 (逆序) ---
    {
        int arr[] = { 5, 2 };
        int size = 2;
        int expected[] = { 2, 5 };
        print_array(arr, size);
        bubble_sort_final(arr, size);
        assert(memcmp(arr, expected, sizeof(expected)) == 0);
        print_array(arr, size);
        std::cout << "测试 8 (两元素逆序): 通过\n";
    }


    std::cout << "所有测试用例均已通过！\n\n";
}

