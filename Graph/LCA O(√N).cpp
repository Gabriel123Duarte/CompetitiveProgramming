/*
	LCA - Lowest Common Ancestor
	Author: Gabriel Duarte

	Description: Given two nodes of a tree the algorithm
				 output the LCA using sqrt-decomposition
	Complexity: <O(N), O(√N)>
*/

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

vector<vi> tree;
vi height, parent, superParent;
int root;

void dfs(int u, int p, int sp, int h)
{
	height[u] = h;
	parent[u] = p;
	superParent[u] = sp;

	if(h % root == 0)
		sp = u;

	for(auto v : tree[u])
		if(p != v)
			dfs(v, u, sp, h + 1);
}

void lca(int u, int v)
{
	int U = u, V = v;

	while(superParent[u] != superParent[v])
	{
		if(height[u] > height[v])
			u = superParent[u];
		else
			v = superParent[v];
	}

	while(u != v)
	{
		if(height[u] > height[v])
			u = parent[u];
		else
			v = parent[v];
	}

	int x = u;
	int val = height[U] + height[V] - 2 * height[x];
	printf("LCA(%d, %d) is %d with distance = %d\n", U, V, x, val);
}

int main()
{
	int nodes = 7;
	tree.assign(nodes, vi());

	tree[0].push_back(1);
	tree[0].push_back(4);
	tree[1].push_back(2);
	tree[1].push_back(3);
	tree[4].push_back(6);
	tree[3].push_back(5);


	height.assign(nodes, 0);
	parent.assign(nodes, 0);
	superParent.assign(nodes, 0);
	root = sqrt(nodes);

	dfs(0, 0, 0, 1); // Process O(N)

	lca(1, 6);
	lca(2, 4);
	lca(2, 5);
	lca(2, 3);
	return 0;
}