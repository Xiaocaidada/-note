#pragma once

namespace _heap_sort {

	void swap(int* a,int *b);
	void make_heap(int* arr,int n);
	void down(int* arr,int size,int index);
	void heap_sort(int*arr,int n);
	void test_heap_sort();

}