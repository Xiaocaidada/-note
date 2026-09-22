#include "prefix_sum.h"

//一维前缀和
void od_get_sum(int s[], int n, int a[]) {
	for (int i = 1; i <= n; i++) {
		s[i] = s[i - 1] + a[i];
	}
}

//求区间[m,n]的和
int od_search(int s[], int m, int n) {
	return s[n] - s[m - 1];
}

void td_get_sum(int s[][MAX_COUNT], int m, int n, int a[][MAX_COUNT]) {
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			s[i][j] = s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1] + a[i][j];
		}
	}

}

//求以(x1,y1)为左上角,(x2,y2)为右下角的矩阵元素和
int td_search(int s[][MAX_COUNT], int x1, int y1, int x2, int y2) {
	return s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1];
}