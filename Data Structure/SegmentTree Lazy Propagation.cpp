/*
	Segment Tree with Lazy Propagation
	Author: Gabriel Duarte

	Description: Make range sum query in O(log n) and range update in O(log n)
	Complexity:
		Update range - O(log n)
		Query  RSQ   - O(log n)

*/

#include <bits/stdc++.h>

using namespace std;

class SegmentTree
{
	private:
		vector<int> st, lazy, A; // Index by 0
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
				st[p] = st[left(p)] + st[right(p)];
			}
		}


		int rsq(int p, int L, int R, int i, int j)
		{
			
			if(lazy[p] != 0)
			{
				st[p] += (R - L + 1) * lazy[p];
				if(L != R)
				{
					lazy[left(p)] += lazy[p];
					lazy[right(p)] += lazy[p];
				}
				lazy[p] = 0;
			}

			if(i > R || j < L || R < L) return 0;
			if(L >= i && R <= j) return st[p];

			return rsq(left(p), L, (L + R) / 2, i, j) + rsq(right(p), (L + R) / 2 + 1, R, i, j);
		}

		void updateRange(int p, int L, int R, int i, int j, int newValue)
		{
			if(lazy[p] != 0)
			{
				st[p] += (R - L + 1) * lazy[p];

				if(L != R)
				{
					lazy[left(p)] += lazy[p];
					lazy[right(p)] += lazy[p];
				}
				lazy[p] = 0;
			}

			if(L > R || L > j || R < i)
				return;
			if(L >= i && R <= j)
			{
				st[p] += (R - L + 1) * newValue;
				if(L != R)
				{
					lazy[left(p)] += newValue;
					lazy[right(p)] += newValue;
				}
				return;
			}

			updateRange(left(p), L, (L + R) / 2, i, j, newValue);
			updateRange(right(p), (L + R) / 2 + 1, R, i, j, newValue);

			st[p] = st[left(p)] + st[right(p)];

		}
	
	public:
		SegmentTree(const vector<int> _A)
		{
			A = _A;
			n = A.size();
			st.assign(4 * n, 0);
			lazy.assign(4 * n, 0);
			build(1, 0, n - 1);
		}

		int rsq(int i, int j)
		{
			return rsq(1, 0, n - 1, i, j);
		}
		void updateRange(int i, int j, int newValue)
		{
			updateRange(1, 0, n - 1, i, j, newValue);
		}
};


int main()
{
	int arr[] = {1, 1, 1, 1, 1};        
	vector<int> A(arr, arr + 5);
	SegmentTree st(A);

	printf("%d\n", st.rsq(1, 4));
	st.updateRange(1, 4, 3);
	printf("%d\n", st.rsq(1, 4));
	return 0;
}