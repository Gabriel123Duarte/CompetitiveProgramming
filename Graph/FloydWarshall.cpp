/*
	Floyd Warshall
	Author: Gabriel Duarte

	Description: ASSP in a Graph
	Complexity: O(V³)

*/

#include <bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 100

int graph[MAXN][MAXN];
int V, E; // V = Vertex - E = Edges

void floydWarshall()
{
	for(int k = 0; k < V; k++)
		for(int i = 0; i < V; i++)
			for(int j = 0; j < V; j++)
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
}

int main()
{
	V = 5;
	E = 3;
	
	for(int i = 0; i < V; i++)
	{
		for(int j = 0; j < V; j++)
			graph[i][j] = INF;
		graph[i][i] = 0;
	}

	graph[0][1] = 3;
	graph[1][0] = 51;
	graph[2][4] = 112;

	floydWarshall();
	return 0;
}
