#pragma once


namespace _quick_sort {
	void swap(int* a,int*b);

	int partion1(int* arr, int i, int j);
	int partion2(int*arr,int i,int j);
	int partion3(int*arr,int i,int j);
	void partion4(int*arr,int i,int j);

	void quick_sort(int* arr,int n);

	void test_quick_sort();


}