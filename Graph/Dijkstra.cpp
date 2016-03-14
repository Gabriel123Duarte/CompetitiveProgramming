/*
	Dijkstra
	Author: Gabriel Duarte

	Description: SSSP in a Graph without negative cycle
	Complexity: O((V + E)log E)

*/

#include <bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f
typedef pair<int, int> ii;
typedef vector<ii> vii;

vector<vii> graph;
int V, E; // V = Vertex - E = Edges

void dijkstra(int s)
{
	vector<int> dist(V, INF); // Contains distances from s to all other vertex
	dist[s] = 0;
	priority_queue<ii, vector<ii>, greater<ii> > pq;
	pq.push(ii(0, s));

	while(!pq.empty())
	{
		int d = pq.top().first, u = pq.top().second;
		pq.pop();

		if(d > dist[u])
			continue;

		for(auto v : graph[u])
		{
			if(dist[u] + v.second < dist[v.first])
			{
				dist[v.first] = dist[u] + v.second;
				pq.push(ii(dist[v.first], v.first));
			}
		}
	}
}

int main()
{
	V = 5;
	E = 3;
	graph.assign(V, vii());

	graph[0].push_back(ii(1, 3)); // First = Vertex - Second = Value
	graph[1].push_back(ii(0, 51));
	graph[2].push_back(ii(4, -5));

	dijkstra(0);
	return 0;
}
