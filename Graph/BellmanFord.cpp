/*
	Bellman Ford
	Author: Gabriel Duarte

	Description: SSSP in a Graph with negative cycle
	Complexity: O(VE)

*/

#include <bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f
typedef pair<int, int> ii;
typedef vector<ii> vii;

vector<vii> graph;
int V, E; // Vertex and edges

void bellmanFord(int s)
{
	vector<int> dist(V, INF);

	for(int i = 0; i < V - 1; i++)
		for(int u = 0; u < V; u++)
			for(auto v : graph[u])
				dist[v.first] = min(dist[v.first], dist[u] + v.second);
	
	bool hasNegativeCycle = false;
	for(int u = 0; u < V; u++)
		for(auto v : graph[u])
			if(dist[v.first] > dist[u] + v.second)
				hasNegativeCycle = true;

	printf("Cycle ? %d\n", hasNegativeCycle);
}

int main()
{
	V = 5;
	E = 3;
	graph.assign(V, vii());

	graph[0].push_back(ii(1, -3)); // First = Vertex - Second = Value
	graph[1].push_back(ii(0, -51));
	graph[2].push_back(ii(4, -5));

	bellmanFord(0);
	return 0;
}