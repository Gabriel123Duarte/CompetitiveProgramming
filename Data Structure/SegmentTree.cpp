/*
	Segment Tree for RMQ
	Author: Gabriel Duarte

	Description: Make RMQ in O(log n) and point update in O(log n)
	Complexity:
		Update - O(log n)
		Query  - O(log n)

	Here I use Range Minimum Query, if you want Maximum, just change the function
	min() to max(), and INF to NEGINF

*/

#include <bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f

class SegmentTree
{
	private:
		vector<int> st, A; // Index by 0
		int n;
		int left(int p) { return p << 1; }
		int right(int p) { return (p << 1) + 1; }	

		void build(int p, int L, int R)
		{
			if(L == R)
				st[p] = A[L];
			else
			{
				build(left(p), L, (L + R) / 2);
				build(right(p), (L + R) / 2 + 1, R);
				st[p] = min(st[left(p)], st[right(p)]);
			}
		}


		int rmq(int p, int L, int R, int i, int j)
		{
			
			if(i > R || j < L || R < L) return INF;
			if(L >= i && R <= j) return st[p];

			return min(rmq(left(p), L, (L + R) / 2, i, j),
					   rmq(right(p), (L + R) / 2 + 1, R, i, j));
		}

		void update(int p, int L, int R, int idx, int newValue)
		{
			int i = idx, j = idx;

			if(i > R || j < L)
      			return;

      		if(L == i && R == j)
      		{
      			st[p] = newValue;
      			return;
      		}
    		

			update(left(p), L, (L + R) / 2, idx, newValue);
			update(right(p), (L + R) / 2 + 1, R, idx, newValue);

			st[p] = min(st[left(p)], st[right(p)]);

		}
	
	public:
		SegmentTree(const vector<int> _A)
		{
			A = _A;
			n = A.size();
			st.assign(4 * n, 0);
			build(1, 0, n - 1);
		}

		int rmq(int i, int j)
		{
			return rmq(1, 0, n - 1, i, j);
		}
		void update(int i, int newValue)
		{
			update(1, 0, n - 1, i, newValue);
		}
};


int main()
{
	int arr[] = {1, 5, 3, 2, 7};        
	vector<int> A(arr, arr + 5);
	SegmentTree st(A);

	printf("%d\n", st.rmq(1, 4));
	st.update(1, 3);
	printf("%d\n", st.rmq(1, 4));
	st.update(2, -1);
	printf("%d\n", st.rmq(1, 4));
	return 0;
}