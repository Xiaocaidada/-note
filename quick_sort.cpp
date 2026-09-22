#include "quick_sort.h"
#include <iostream>
using namespace std;
using namespace _quick_sort;


void _quick_sort::swap(int*a,int*b) {
	int tp = *a;
	*a = *b;
	*b = tp;
}


//霍尔法(left为基)
int _quick_sort::partion1(int*arr,int i,int j){
	int base = i;
	while (i<j) {
		while (i < j && arr[j] >= arr[base]) --j;
		while (i < j && arr[i] <= arr[base])++i;
		swap(&arr[i],&arr[j]);
	}
	swap(&arr[base], &arr[i]);
	return i;
}

//挖坑法(以left为基)
int _quick_sort::partion2(int*arr, int i,int j) {
	int tp = arr[i];
	int hole = i;
	while (i < j) {
		while (i < j && arr[j] >= tp)--j;
		arr[hole] = arr[j];
		hole = j;
		while (i < j && arr[i] <= tp)++i;
		arr[hole] = arr[i];
		hole = i;
	}
	arr[hole] = tp;
	return i;
}

//同向指针法
int _quick_sort::partion3(int*arr,int i,int j) {
	int prev = i - 1;
	int curr = i,base=i;
	while (curr<=j) {
		if (arr[curr] <= arr[base] && ++prev != curr) {
			swap(&arr[curr],&arr[prev]);
		}
		++curr;
	}
	swap(&arr[prev],&arr[base]);
	return prev;
}

//三路划分法
void _quick_sort::partion4(int*arr,int i,int j) {
	if (i >= j) return;
	int l = i;
	int r = j;
	int curr = i;
	int base_val = arr[i];
	while (curr <= r) {
		if (arr[curr] < base_val) swap(&arr[l++], &arr[curr++]);
		else if (arr[curr] > base_val) swap(&arr[curr], &arr[r--]); //right处的值还需要再判断一次，curr不能后走
		else ++curr;
	}
	partion4(arr,i,l-1);
	partion4(arr,r+1,j);
}





void quick_sort_recursion(int*arr,int i,int j) {
	if (i >= j) return;
	int mid= partion1(arr,i,j);
	quick_sort_recursion(arr,i,mid);
	quick_sort_recursion(arr, mid+1, j);
}






void _quick_sort::quick_sort(int* arr,int n) {
	if (!arr || n <= 1) return;
	int i = 0;
	int j = n - 1;
	quick_sort_recursion(arr,i,j);
}




// 辅助函数：打印数组
void printArray(const int arr[], int size, const std::string& title) {
    std::cout << title << ": ";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
// 辅助函数：打印数组
void printArray_p4(const int arr[], int size, const std::string& title) {
    std::cout << title << ": ";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
// 辅助函数：检查数组是否已排序
bool isSorted_p4(const int arr[], int size) {
    for (int i = 1; i < size; ++i) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}
// 专门为 partion4 设计的测试函数
void test_partion4() {
    std::cout << "\n--- 开始测试 partion4 (三路划分快速排序) ---" << std::endl;

    // 注意：partion4 是一个 void 函数，直接对数组进行原地排序
    // 我们需要将它当作一个完整的排序算法来测试

    // 测试用例1: 随机数组 (包含重复元素)
    {
        int arr[] = { 4, 5, 3, 3, 7, 4, 1, 3, 9, 4 };
        int n = sizeof(arr) / sizeof(arr[0]);
        printArray_p4(arr, n, "P4测试1 - 排序前 (随机+重复)");
        _quick_sort::partion4(arr, 0, n - 1); // 调用 partion4 进行排序
        printArray_p4(arr, n, "P4测试1 - 排序后 (随机+重复)");
        std::cout << "P4测试1 - 是否已排序: " << (isSorted_p4(arr, n) ? "是" : "否") << std::endl;
        std::cout << std::endl;
    }

    // 测试用例2: 所有元素相同
    {
        int arr[] = { 5, 5, 5, 5, 5 };
        int n = sizeof(arr) / sizeof(arr[0]);
        printArray_p4(arr, n, "P4测试2 - 排序前 (全部相同)");
        _quick_sort::partion4(arr, 0, n - 1);
        printArray_p4(arr, n, "P4测试2 - 排序后 (全部相同)");
        std::cout << "P4测试2 - 是否已排序: " << (isSorted_p4(arr, n) ? "是" : "否") << std::endl;
        std::cout << std::endl;
    }

    // 测试用例3: 已经排序好的数组
    {
        int arr[] = { 1, 2, 3, 4, 5, 6 };
        int n = sizeof(arr) / sizeof(arr[0]);
        printArray_p4(arr, n, "P4测试3 - 排序前 (已排序)");
        _quick_sort::partion4(arr, 0, n - 1);
        printArray_p4(arr, n, "P4测试3 - 排序后 (已排序)");
        std::cout << "P4测试3 - 是否已排序: " << (isSorted_p4(arr, n) ? "是" : "否") << std::endl;
        std::cout << std::endl;
    }

    // 测试用例4: 逆序数组
    {
        int arr[] = { 9, 8, 7, 6, 5 };
        int n = sizeof(arr) / sizeof(arr[0]);
        printArray_p4(arr, n, "P4测试4 - 排序前 (逆序)");
        _quick_sort::partion4(arr, 0, n - 1);
        printArray_p4(arr, n, "P4测试4 - 排序后 (逆序)");
        std::cout << "P4测试4 - 是否已排序: " << (isSorted_p4(arr, n) ? "是" : "否") << std::endl;
        std::cout << std::endl;
    }

    // 测试用例5: 单个元素
    {
        int arr[] = { 42 };
        int n = sizeof(arr) / sizeof(arr[0]);
        printArray_p4(arr, n, "P4测试5 - 排序前 (单元素)");
        _quick_sort::partion4(arr, 0, n - 1); // i=0, j=0
        printArray_p4(arr, n, "P4测试5 - 排序后 (单元素)");
        std::cout << "P4测试5 - 是否已排序: " << (isSorted_p4(arr, n) ? "是" : "否") << std::endl;
        std::cout << std::endl;
    }

    // 测试用例6: 空范围 (i > j)
    {
        int arr[] = { 1, 2, 3 }; // 数组内容无关紧要
        int n = sizeof(arr) / sizeof(arr[0]);
        std::cout << "P4测试6 - 调用 partion4(arr, 2, 1) (空范围 i>j)" << std::endl;
        _quick_sort::partion4(arr, 2, 1); // 应该立即返回，不改变数组
        printArray_p4(arr, n, "P4测试6 - 调用后数组状态");
        std::cout << "(应无变化且无崩溃)" << std::endl;
        std::cout << std::endl;
    }

    // 测试用例7: 两个元素
    {
        int arr1[] = { 2, 1 }; // 需要交换
        int n1 = sizeof(arr1) / sizeof(arr1[0]);
        printArray_p4(arr1, n1, "P4测试7a - 排序前 (两元素-需交换)");
        _quick_sort::partion4(arr1, 0, n1 - 1);
        printArray_p4(arr1, n1, "P4测试7a - 排序后 (两元素-需交换)");

        int arr2[] = { 1, 2 }; // 已排序
        int n2 = sizeof(arr2) / sizeof(arr2[0]);
        printArray_p4(arr2, n2, "P4测试7b - 排序前 (两元素-已排序)");
        _quick_sort::partion4(arr2, 0, n2 - 1);
        printArray_p4(arr2, n2, "P4测试7b - 排序后 (两元素-已排序)");
        std::cout << std::endl;
    }


    std::cout << "--- partion4 (三路划分快速排序) 测试结束 ---\n" << std::endl;
}
void _quick_sort::test_quick_sort() {
    std::cout << "--- 开始测试快速排序 ---" << std::endl;

    // 测试用例1: 随机数组
    {
        int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
        int n = sizeof(arr) / sizeof(arr[0]);
        printArray(arr, n, "测试1 - 排序前 (随机)");
        _quick_sort::quick_sort(arr, n);
        printArray(arr, n, "测试1 - 排序后 (随机)");
        std::cout << std::endl;
    }

    // 测试用例2: 已经排序好的数组
    {
        int arr[] = { 5, 10, 15, 20, 25 };
        int n = sizeof(arr) / sizeof(arr[0]);
        printArray(arr, n, "测试2 - 排序前 (已排序)");
        _quick_sort::quick_sort(arr, n);
        printArray(arr, n, "测试2 - 排序后 (已排序)");
        std::cout << std::endl;
    }

    // 测试用例3: 逆序数组
    {
        int arr[] = { 30, 25, 20, 15, 10, 5 };
        int n = sizeof(arr) / sizeof(arr[0]);
        printArray(arr, n, "测试3 - 排序前 (逆序)");
        _quick_sort::quick_sort(arr, n);
        printArray(arr, n, "测试3 - 排序后 (逆序)");
        std::cout << std::endl;
    }

    // 测试用例4: 包含重复元素
    {
        int arr[] = { 4, 2, 4, 2, 4, 2 };
        int n = sizeof(arr) / sizeof(arr[0]);
        printArray(arr, n, "测试4 - 排序前 (重复元素)");
        _quick_sort::quick_sort(arr, n);
        printArray(arr, n, "测试4 - 排序后 (重复元素)");
        std::cout << std::endl;
    }

    // 测试用例5: 单个元素
    {
        int arr[] = { 42 };
        int n = sizeof(arr) / sizeof(arr[0]);
        printArray(arr, n, "测试5 - 排序前 (单元素)");
        _quick_sort::quick_sort(arr, n);
        printArray(arr, n, "测试5 - 排序后 (单元素)");
        std::cout << std::endl;
    }

    // 测试用例6: 空指针 (边界条件)
    {
        int* arr = nullptr;
        int n = 5;
        std::cout << "测试6 - 排序前 (空指针): arr = nullptr" << std::endl;
        _quick_sort::quick_sort(arr, n); // 应该安全地处理
        std::cout << "测试6 - 排序后 (空指针): (无崩溃即成功)" << std::endl;
        std::cout << std::endl;
    }

    // 测试用例7: 元素个数为0 (边界条件)
    {
        int arr[99] = {}; // 这种方式定义大小为0的数组在C++中不标准，但通常有效
        int n = 0;       // 显式设置为0更安全
        // printArray对于n=0是安全的，会打印空行
        printArray(arr, n, "测试7 - 排序前 (零元素)");
        _quick_sort::quick_sort(arr, n); // 应该安全地处理
        printArray(arr, n, "测试7 - 排序后 (零元素)");
        std::cout << std::endl;
    }

    // 可选：如果你想测试不同的 partition 方法(partion2, partion3)，可以修改 quick_sort_recursion 内部调用
    // 或者创建一个带参数的版本来指定使用哪种 partition 方法。
    test_partion4();


    std::cout << "--- 快速排序测试结束 ---" << std::endl;
}