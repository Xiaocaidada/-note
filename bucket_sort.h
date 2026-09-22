#pragma once

namespace _bucket_sort {
	struct Node {
		int val;
		Node* next;
		Node(int val) :val(val) {}
	};

	void multi_sort(Node*start,int n);
	
	void bucket_sort(int*arr,int n);

	void test_bucket_sort();
}