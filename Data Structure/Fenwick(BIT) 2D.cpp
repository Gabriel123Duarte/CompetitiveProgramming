/*
	Fenwick Tree (BIT) - 2D
	Author: Gabriel Duarte

	Description: Make range query and point update in a 2D grid
	Complexity:
		Build - O(1)
		Build from array O(m log² n)
		Update - O(log² n)
		Query  - O(log² n)

*/

#include <bits/stdc++.h>

using namespace std;

class Fenwick
{
	private:
		vector<vector<int> > ft;
	public:
		Fenwick(int x, int y) // Grid size
		{
			// Don't use index 0
			ft.assign(x + 1, vector<int>());
			for(int i = 0; i <= x; i++)
				ft[i].assign(y + 1, 0);
		}
		void update(int x, int y, int value)
		{
			for(; x < ft.size(); x += x & (-x))
				for(int j = y; j < ft[0].size(); j += j & (-j))
					ft[x][j] += value;
		}
		int query(int x, int y) // [(1, 1)..(x, y)]
		{
			int ans = 0;
			for(; x; x -= x & (-x))
				for(int j = y; j; j -= j & (-j))
					ans += ft[x][j];
			return ans;
		}
		int query(int x1, int y1, int x2, int y2) // [(x1, y1) ... (x2, y2)]
		{
			return query(x2, y2) + query(x1 - 1, y1 - 1) -
				   query(x2, y1 - 1) - query(x1 - 1, y2);
		}
};

int main()
{
	Fenwick ft(5, 5);
	ft.update(2, 2, 10);
	printf("%d\n", ft.query(1, 1, 5, 5));
	ft.update(3, 5, 11);
	printf("%d\n", ft.query(1, 1, 5, 5));
}