#include <iostream>
#include <limits.h>
#include <iomanip> // for std::setw
#include <algorithm> // for std::sort, std::is_sorted
#include <vector>
#include <cmath>
#include <cstring> 
#include <cassert>
#include "bucket_sort.h"
using namespace _bucket_sort;
using namespace std;

void insert_sort(Node* head,int n) {

	Node* tp = head->next;
	for (int i = 0; i < n-1; ++i) {
		Node* curr = tp->next;
		if (curr->val < tp->val) {
			Node* pointer = head;
			while (pointer->next->val < curr->val)pointer = pointer->next;
			tp->next = curr->next;
			curr->next = pointer->next;
			pointer->next = curr;
		}
		else tp = tp->next;
		
	}
}

void merge_sort(Node* head,int n,int i,int j,int*arr) {
	if (i >= j) return;
	int mid = (i + j) >> 1;
	merge_sort(head,mid-i+1,i,mid,arr);
	merge_sort(head, j-mid, mid + 1, j,arr);
	Node* l1 = nullptr; Node* r1 = nullptr; Node* l2 = nullptr;Node* r2 = nullptr;
	Node* tp = head->next;
	int m = 0;
	for (; m <= j; ++m, tp = tp->next) {
		if (m == i) l1 = tp;
		if (m == mid) {
			r1 = tp;
			l2 = tp->next;
		}
		if (m == j) r2 = tp;
	}
	int _l1=i,_l2 = mid+1,index=0;
	Node* t = l1;
	while (_l1<=mid&&_l2<=j) {
		int min_v;
		if (l1->val < l2->val) {
			min_v = l1->val;
			l1 = l1->next;
			++_l1;
		}
		else {
			min_v = l2->val;
			l2 = l2->next;
			++_l2;
		}
		arr[index++] = min_v;
	}
	while (_l1 <= mid) {
		arr[index++] = l1->val;
		l1 = l1->next;
		++_l1;
	}
	while (_l2 <= j) {
		arr[index++] = l2->val;
		l2 = l2->next;
		++_l2;
	}
	for (int i = 0; i < index; ++i) {
		if (t) {
			t->val = arr[i];
			t = t->next;
		}
	}
}

void _bucket_sort::multi_sort(Node* head,int n) {
	if (n <= 1) return;
	if (n <= 16) {
		cout << "使用了插入排序\n";
		insert_sort(head, n);
	} 
	else {
		cout << "使用了归并排序\n";
		int* arr = new int[n];
		merge_sort(head,n,0,n-1,arr);
		delete[] arr;
	}
}

Node* create_node(Node* next,int val) {
	Node* tp =(Node*) malloc(sizeof(Node));
	tp->next = next;
	tp->val = val;
	return tp;
}


void _bucket_sort::bucket_sort(int*arr,int n) {
	if (!arr || n <= 1) return;
	int bucket_num = (int)sqrt(n);
	Node** bucket = (Node**)malloc(sizeof(Node*)*bucket_num);
	for (int i = 0; i < bucket_num; ++i) {
		bucket[i] = create_node(nullptr,0);
	}

	int min_v = INT_MAX,max_v=INT_MIN;
	for (int i = 0; i < n; ++i) {
		min_v = min_v > arr[i] ? arr[i] : min_v;
		max_v = max_v < arr[i] ? arr[i] : max_v;
	}

	for (int i = 0; i < n; ++i) {
		int bucket_index = -1;
		if (min_v == max_v)bucket_index = 0;
		else
			bucket_index =(int)(((double)arr[i] - (double)min_v) / ((double)max_v - (double)min_v) * bucket_num);
		if (bucket_index >= bucket_num)--bucket_index;
		Node* tp = create_node(bucket[bucket_index]->next,arr[i]);
		bucket[bucket_index]->next = tp;
		++(bucket[bucket_index]->val);
	}

	for (int i = 0; i < bucket_num; ++i) {
		if (bucket[i]) {
			multi_sort(bucket[i],bucket[i]->val);
		}
	}
	int index = 0;
	for (int i = 0; i < bucket_num; ++i) {
		Node* tp = bucket[i];
		while (tp->next) {
			tp = tp->next;
			arr[index++] = tp->val;
		}
	}
}

// --- 测试函数 ---

void print_array(const int* arr, int size, const std::string& prefix = "") {
	std::cout << prefix;
	for (int i = 0; i < size; ++i) {
		std::cout << std::setw(5) << arr[i] << " ";
	}
	std::cout << "\n";
}

bool arrays_equal(const int* a, const int* b, int size) {
	for (int i = 0; i < size; ++i) {
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;
}

void run_test_case(const std::string& name, int* original_arr, int size) {
	std::cout << "\n--- Test Case: " << name << " (Size: " << size << ") ---\n";
	if (size <= 50) { // Only print small arrays for readability
		print_array(original_arr, size, "Original: ");
	}

	// Create a copy for our bucket sort
	int* arr_to_sort = new int[size];
	std::memcpy(arr_to_sort, original_arr, sizeof(int) * size);

	// Create another copy for standard library sort to compare against
	int* expected_arr = new int[size];
	std::memcpy(expected_arr, original_arr, sizeof(int) * size);
	std::sort(expected_arr, expected_arr + size);

	// Apply bucket sort
	_bucket_sort::bucket_sort(arr_to_sort, size);

	if (size <= 50) {
		print_array(arr_to_sort, size, "Sorted:   ");
		print_array(expected_arr, size, "Expected: ");
	}

	// Verify correctness
	bool is_correct = arrays_equal(arr_to_sort, expected_arr, size); //std::is_sorted(arr_to_sort, arr_to_sort + size) && 
	std::cout << "Result: " << (is_correct ? "PASS" : "FAIL") << "\n";

	if (!is_correct) {
		std::cerr << "ERROR in " << name << ": Sorting failed!\n";
	}

	delete[] arr_to_sort;
	delete[] expected_arr;
}

void _bucket_sort::test_bucket_sort() {
	std::cout << "Starting comprehensive bucket sort tests...\n";

	// 1. Empty array
	run_test_case("Empty Array", nullptr, 0); // Test null pointer handling
	int empty_arr[99] = {};
	run_test_case("Empty Array 2", empty_arr, 0);

	// 2. Single element
	int single_arr[] = { 42 };
	run_test_case("Single Element", single_arr, 1);

	// 3. Already sorted (ascending)
	int sorted_arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	run_test_case("Already Sorted Asc", sorted_arr, 10);

	// 4. Reverse sorted (descending)
	int reverse_arr[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	run_test_case("Reverse Sorted", reverse_arr, 10);

	// 5. Array with duplicates
	int dup_arr[] = { 5, 2, 8, 2, 9, 1, 5, 5 };
	run_test_case("With Duplicates", dup_arr, 8);

	// 6. Random array
	int random_arr[] = { 34, 7, 23, 32, 5, 62, 77, 12, 91, 4, 55, 38, 19, 82, 27 };
	run_test_case("Random Order", random_arr, 15);

	// 7. All elements the same
	int same_arr[] = { 7, 7, 7, 7, 7, 7, 7 };
	run_test_case("All Same Elements", same_arr, 7);

	// 8. Array with negative numbers
	int neg_arr[] = { -3, -1, -4, -1, -5, 9, 2, 6 };
	run_test_case("With Negative Numbers", neg_arr, 8);

	// 9. Large value range
	int large_range_arr[] = { INT_MAX, 0, INT_MIN, 100, -100 };
	run_test_case("Large Value Range", large_range_arr, 5);

	// 10. Size 16 (boundary for insertion sort switch)
	int size16_arr[16];
	for (int i = 0; i < 16; ++i) size16_arr[i] = 16 - i; // Fill with 16, 15, ..., 1
	run_test_case("Size 16 (Insertion Sort Boundary)", size16_arr, 16);

	// 11. Size 17 (boundary for merge sort switch)
	int size17_arr[17];
	for (int i = 0; i < 17; ++i) size17_arr[i] = 17 - i; // Fill with 17, 16, ..., 1
	run_test_case("Size 17 (Merge Sort Boundary)", size17_arr, 17);

	// 12. Larger random array
	const int large_size = 200;
	int* large_random_arr = new int[large_size];
	for (int i = 0; i < large_size; ++i) {
		large_random_arr[i] = rand() % 1000; // Random numbers 0-999
	}
	run_test_case("Larger Random Array (Size 10000)", large_random_arr, large_size);
	delete[] large_random_arr;

	// 13. Array with many duplicates
	int many_dup_arr[] = { 1, 3, 2, 3, 1, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2 };
	run_test_case("Many Duplicates", many_dup_arr, 15);

	std::cout << "\n--- All tests completed. ---\n";
}

