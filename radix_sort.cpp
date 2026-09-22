#include "radix_sort.h"
#include <limits.h>
#include <stdio.h>
using namespace std;
using namespace _radix_sort;


void _radix_sort::swap(int*a,int*b) {
	int tp = *a;
	*a = *b;
	*b = tp;
}


void bubble_sort(int*  arr,int n,int exp) {
	int last_exchange = n - 1;
	while (last_exchange) {
		int tp_last_ex = 0;
		for (int i = 0; i < last_exchange; ++i) {
			int curr = (arr[i] /exp) % 10;
			int next = (arr[i + 1] / exp) % 10;
			if (curr > next) {
				int tp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tp;
				tp_last_ex = i;
			}
		}
		last_exchange = tp_last_ex;
	}
}
//快排每次都独立，只会以最后一次比较为准
void quick_sort(int*arr, int exp, int p,int q) {
	if (p >= q) return;
    int base = (arr[p] / exp) % 10;
	int left = p;
	int right = q;
	int pointer = p;
	while (pointer <= right) {
		int curr = (arr[pointer] / exp) %10;
		if (curr < base) swap(&arr[left++], &arr[pointer++]);
		else if (curr > base)swap(&arr[right--], &arr[pointer]);
		else ++pointer;
	}
	quick_sort(arr,exp,p,left-1);
	quick_sort(arr,exp,right+1,q);
}



void _radix_sort::multi_sort(int*arr,int n,int exp) {
	if (n <= 16) {
		printf("调用冒泡排序\n");
		bubble_sort(arr, n, exp);
	}
	else {
		printf("调用快排\n");
		quick_sort(arr, exp, 0, n - 1);
	}
}

int find_max(int* arr, int n) {
	int max_v = INT_MIN;
	while (n--) {
		max_v = max_v < arr[n] ? arr[n] : max_v;
	}
	return max_v;
}

void _radix_sort::radix_sort(int*arr,int n) {
	if (!arr || n <= 1) return;
	int max_v = find_max(arr,n);
	for (int i = 1; max_v / i > 0;i*=10) {
		multi_sort(arr,n,i);
	}
}



void _radix_sort::test_radix_sort() {
    printf("--- 开始测试基数排序 ---\n");

    // 测试用例1：基本情况
    {
        printf("\n测试用例 1: 基本整数数组\n");
        int arr1[] = { 170, 45, 75, 90, 2, 802, 24, 66 };
        int n1 = sizeof(arr1) / sizeof(arr1[0]);

        printf("排序前: ");
        for (int i = 0; i < n1; i++) printf("%d ", arr1[i]);
        printf("\n");

        _radix_sort::radix_sort(arr1, n1);

        printf("最终排序后: ");
        for (int i = 0; i < n1; i++) printf("%d ", arr1[i]);
        printf("\n");
    }

    // 测试用例2：包含较小数组（触发冒泡排序）
    {
        printf("\n测试用例 2: 包含小规模子数组的情况\n");
        int arr2[] = { 102, 201, 30, 4, 500, 60, 7, 80, 9, 4000,3000,1000, 11, 12, 13, 14, 15, 16, 17,7000,6000,5000 };
        int n2 = sizeof(arr2) / sizeof(arr2[0]);

        printf("排序前: ");
        for (int i = 0; i < n2; i++) printf("%d ", arr2[i]);
        printf("\n");

        _radix_sort::radix_sort(arr2, n2);

        printf("最终排序后: ");
        for (int i = 0; i < n2; i++) printf("%d ", arr2[i]);
        printf("\n");
    }

    // 测试用例3：已排序数组
    {
        printf("\n测试用例 3: 已排序数组\n");
        int arr3[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        int n3 = sizeof(arr3) / sizeof(arr3[0]);

        printf("排序前: ");
        for (int i = 0; i < n3; i++) printf("%d ", arr3[i]);
        printf("\n");

        _radix_sort::radix_sort(arr3, n3);

        printf("最终排序后: ");
        for (int i = 0; i < n3; i++) printf("%d ", arr3[i]);
        printf("\n");
    }

    // 测试用例4：逆序数组
    {
        printf("\n测试用例 4: 逆序数组\n");
        int arr4[] = { 90, 80, 70, 60, 50, 40, 30, 20, 10 };
        int n4 = sizeof(arr4) / sizeof(arr4[0]);

        printf("排序前: ");
        for (int i = 0; i < n4; i++) printf("%d ", arr4[i]);
        printf("\n");

        _radix_sort::radix_sort(arr4, n4);

        printf("最终排序后: ");
        for (int i = 0; i < n4; i++) printf("%d ", arr4[i]);
        printf("\n");
    }

    // 测试用例5：包含负数 (注意：标准LSD Radix Sort 对负数处理需要特殊逻辑，你的实现可能无法正确处理)
    {
        printf("\n测试用例 5: 包含负数 (注意: 标准LSD实现可能无法正确排序负数!)\n");
        int arr5[] = { -5, 170, -1, 45, 75, -200, 90, 2, 802, 24, 66 };
        int n5 = sizeof(arr5) / sizeof(arr5[0]);

        printf("排序前: ");
        for (int i = 0; i < n5; i++) printf("%d ", arr5[i]);
        printf("\n");

        _radix_sort::radix_sort(arr5, n5);

        printf("最终排序后 (可能不正确): ");
        for (int i = 0; i < n5; i++) printf("%d ", arr5[i]);
        printf("\n");
    }

    // 测试用例6：单个元素
    {
        printf("\n测试用例 6: 单个元素\n");
        int arr6[] = { 42 };
        int n6 = sizeof(arr6) / sizeof(arr6[0]);

        printf("排序前: ");
        for (int i = 0; i < n6; i++) printf("%d ", arr6[i]);
        printf("\n");

        _radix_sort::radix_sort(arr6, n6);

        printf("最终排序后: ");
        for (int i = 0; i < n6; i++) printf("%d ", arr6[i]);
        printf("\n");
    }

    // 测试用例7：空指针和零长度
    {
        printf("\n测试用例 7: 空指针和零长度\n");
        int* arr7 = nullptr;
        int n7 = 5;

        printf("测试空指针 (应无操作):\n");
        _radix_sort::radix_sort(arr7, n7);

        int arr7_empty[99] = {};
        int n7_empty = 0;
        printf("测试零长度数组 (应无操作):\n");
        _radix_sort::radix_sort(arr7_empty, n7_empty);
        printf("完成。\n");
    }


    printf("\n--- 基数排序测试结束 ---\n");

}
