#include "binary_search.h"


//查找具体一个元素（如果重复，返回最左边索引）
int binary_search_q(int arr[], int n, int target) {
	if (n <= 0 && arr == nullptr) return -1;
	int i = 0;
	int j = n - 1;
	while (i <= j) {
		int mid = (i + j) >> 1;
		if (target < arr[mid]) j = mid - 1;
		else if (target > arr[mid]) i = mid + 1;
		else {
			while (mid >= 0 && arr[--mid] == target);
			return ++mid;
		}
	}
	return -1;
}

//查找小于等于目标的最大元素
int  binary_search_le(int arr[], int n, int target) {
	if (n <= 0 && arr == nullptr) return -1;
	int i = 0;
	int j = n - 1;
	while (i <= j) {
		int mid = (i + j) >> 1;
		if (arr[mid] <= target) i = mid + 1;
		else j = mid - 1;
	}
//j可能为-1,此时数组不存在小于target的元素,外界需要进行判断
	return j;
}
//查找小于目标的最大元素
int binary_search_l(int arr[], int n, int target) {
	if (n <= 0&&arr==nullptr) return -1;
	int i = 0;
	int j = n - 1;
	while (i <= j) {
		int mid = (i + j) >> 1;
		if (arr[mid] < target) i = mid + 1;
		else  j = mid - 1;
	}
	//j可能为-1,此时数组不存在小于target的元素,外界需要进行判断
	return j;  
}
//查找大于等于目标的最小元素
int binary_search_ge(int arr[], int n, int target){
	if (n <= 0 && arr == nullptr) return -1;
	int i = 0;
	int j = n - 1;
	while (i <= j) {
		int mid = (i + j) >> 1;
		if (arr[mid] < target) i = mid + 1;
		else  j = mid - 1;
	}

	//如果数组中所有值小于target,返回数组长度
	return i;
}



//查找大于目标的最小元素
int binary_search_g(int arr[], int n, int target) {
	if (n <= 0 && arr == nullptr) return -1;
	int i = 0;
	int j = n - 1;
	while (i <= j) {
		int mid = (i + j) >> 1;
		if (arr[mid] <= target) i = mid + 1;
		else  j = mid - 1;
	}
	//如果数组中所有值小于等于target,返回数组长度
	return i;
}



