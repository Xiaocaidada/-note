#include <stdio.h>
#include "binary_search.h"

// 辅助函数：打印测试结果
inline void print_result(const char* func_name, int result, int expected) {
    printf("%s: ", func_name);
    if (result == expected) {
        printf("PASS (结果: %d)\n", result);
    }
    else {
        printf("FAIL (实际: %d, 预期: %d)\n", result, expected);
    }
}

inline int test_binary_() {
    // 测试用例1：正常有序数组（无重复元素）
    int arr1[] = { 1, 3, 5, 7, 9 };
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("=== 测试用例1：无重复元素数组 {1,3,5,7,9} ===\n");

    // 测试 binary_search_q（查找等于目标值）
    print_result("binary_search_q(3)", binary_search_q(arr1, n1, 3), 1);
    print_result("binary_search_q(6)", binary_search_q(arr1, n1, 6), -1);
    print_result("binary_search_q(9)", binary_search_q(arr1, n1, 9), 4);

    // 测试 binary_search_le（小于等于目标值的最大元素）
    print_result("binary_search_le(6)", binary_search_le(arr1, n1, 6), 2); // 5<=6
    print_result("binary_search_le(0)", binary_search_le(arr1, n1, 0), -1); // 无元素<=0
    print_result("binary_search_le(9)", binary_search_le(arr1, n1, 9), 4);

    // 测试 binary_search_l（小于目标值的最大元素）
    print_result("binary_search_l(5)", binary_search_l(arr1, n1, 5), 1); // 3<5
    print_result("binary_search_l(1)", binary_search_l(arr1, n1, 1), -1); // 无元素<1
    print_result("binary_search_l(10)", binary_search_l(arr1, n1, 10), 4);

    // 测试 binary_search_ge（大于等于目标值的最小元素）
    print_result("binary_search_ge(6)", binary_search_ge(arr1, n1, 6), 3); // 7>=6
    print_result("binary_search_ge(10)", binary_search_ge(arr1, n1, 10), 5); // 超出范围
    print_result("binary_search_ge(3)", binary_search_ge(arr1, n1, 3), 1);

    // 测试 binary_search_g（大于目标值的最小元素）
    print_result("binary_search_g(5)", binary_search_g(arr1, n1, 5), 3); // 7>5
    print_result("binary_search_g(9)", binary_search_g(arr1, n1, 9), 5); // 超出范围
    print_result("binary_search_g(0)", binary_search_g(arr1, n1, 0), 0);


    // 测试用例2：含重复元素的数组
    int arr2[] = { 2, 2, 4, 4, 4, 6, 6 };
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("\n=== 测试用例2：含重复元素数组 {2,2,4,4,4,6,6} ===\n");

    print_result("binary_search_q(4)", binary_search_q(arr2, n2, 4), 2); // 返回第一个匹配的索引（视实现而定）
    print_result("binary_search_le(4)", binary_search_le(arr2, n2, 4), 4); // 最后一个<=4的元素索引
    print_result("binary_search_l(4)", binary_search_l(arr2, n2, 4), 1); // 最后一个<4的元素索引
    print_result("binary_search_ge(4)", binary_search_ge(arr2, n2, 4), 2); // 第一个>=4的元素索引
    print_result("binary_search_g(4)", binary_search_g(arr2, n2, 4), 5); // 第一个>4的元素索引


    // 测试用例3：空数组
    int* arr3 =nullptr;
    int n3 = 0;
    printf("\n=== 测试用例3：空数组 ===\n");
    print_result("binary_search_q(0)", binary_search_q(arr3, n3, 0), -1);
    print_result("binary_search_le(0)", binary_search_le(arr3, n3, 0), -1);


    // 修复建议：修正 binary_search_g 的逻辑
    printf("\n注意：原代码中 binary_search_ge 和 binary_search_g 实现重复，建议修正：\n");
    printf("binary_search_g 应改为：\n");
    printf("if (arr[mid] <= target) i = mid + 1;  // 小于等于目标值时右移\n");
    printf("else j = mid - 1;\n");

    return 0;
}