#pragma once
#define MAX_COUNT 10000

/**
* 前缀和
*/


void od_get_sum(int arr[], int n, int a[]); //一维前缀和
int od_search(int arr[], int m, int n); //求区间[m,n]的和

void td_get_sum(int arr[][MAX_COUNT], int m, int n,int a[][MAX_COUNT]);
int td_search(int arr[][MAX_COUNT],int x1,int y1,int x2,int y2);  //求以(x1,y1)为左上角,(x2,y2)为右下角的矩阵元素和









