/*
	Sparse Table
	Author: Gabriel Duarte

	Description: Answer query like: min{arr[L]...arr[R]} 
	Complexity: <O(NlogN), O(1)>
*/

#include <bits/stdc++.h>

using namespace std;

#define MAXN 100100
#define LOG  17     // ~log2(MAXN)

int arr[MAXN], st[MAXN][LOG];

void build(int n)
{
	for(int i = 0; i < n; i++)
		st[i][0] = arr[i];

	for(int j = 1; (1 << j) <= n; j++)
		for(int i = 0; i + (1 << j) - 1 < n; i++)
			st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}

int query(int l, int r)
{
	int k = floor(log2((double)r - l + 1));
	return min(st[l][k], st[r - (1 << k) + 1][k]);
}

int main()
{
	int n = 5;
	arr[0] = 5;
	arr[1] = 1;
	arr[2] = 10;
	arr[3] = 2;
	arr[4] = 7;

	build(n);

	printf("Min [%d, %d] is = %d\n", 0, 1, query(0, 1));
	printf("Min [%d, %d] is = %d\n", 2, 4, query(2, 4));
	printf("Min [%d, %d] is = %d\n", 0, 4, query(0, 4));
	printf("Min [%d, %d] is = %d\n", 4, 4, query(4, 4));
	return 0;
}
