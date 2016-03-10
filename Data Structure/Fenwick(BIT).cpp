/*
	Fenwick Tree (BIT)
	Author: Gabriel Duarte - Based on book CP3

	Description: Make range query in O(log n) and point update in O(log n)
	Complexity:
		Build - O(1)
		Build from array O(m log n)
		Update - O(log n)
		Query  - O(log n)

*/

#include <bits/stdc++.h>

using namespace std;

class Fenwick
{
	private:
		vector<int> ft;
	public:
		Fenwick(int n)
		{
			// Don't use index 0
			ft.assign(n + 1, 0);
		}
		void update(int idx, int value)
		{
			for(; idx < ft.size(); idx += idx & (-idx))
				ft[idx] += value;
		}
		int query(int idx) // [1..idx]
		{
			int ans = 0;
			for(; idx; idx -= idx & (-idx))
				ans += ft[idx];
			return ans;
		}
		int query(int a, int b) // [a..b]
		{
			return query(b) - (a == 1 ? 0 : query(a - 1));
		}
};

int main()
{
	Fenwick ft(5);
	ft.update(1, 5);
	printf("%d\n", ft.query(1, 5));
}