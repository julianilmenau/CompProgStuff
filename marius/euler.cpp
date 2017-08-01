#include <bits/stdc++.h>
using namespace std;

struct Graph {
	int v;	//numVertexes
	int adj[50][50];
};


int reachableDFS(Graph &g, int node, bool *visited) {
	int count = 1;
	visited[node] = 1;
	for (int j = 0; j < 50; j++) {
		int i = g.adj[node][j];
		if (i>0 && !visited[j]) {
			count += reachableDFS(g, j, visited);
		}
	}
	return count;
}


void rmvEdge(Graph &g, int u, int v)
{
	g.adj[u][v]--;
	//if (u != v)
		g.adj[v][u]--;
}
void addEdge(Graph &g, int u, int v)
{
	g.adj[u][v]++;
	//if (u != v)
		g.adj[v][u]++;
}


bool isValid(Graph &g, int start, int end) {
	int numAdj = 0;
	for (int j = 0; j < 50;j++) {
		int i = g.adj[start][j];
		if (i > 0 ) {
			numAdj += 1;
		}
	}
	if (numAdj == 1) {
		return true;
	}

	bool visited[50] = {};
	memset(visited, false, 50);
	int count1 = reachableDFS(g, start, visited);
	rmvEdge(g,start, end);
	memset(visited, false, 50);
	int count2 = reachableDFS(g, start, visited);
	addEdge(g, start, end);

	return (count1 > count2) ? false : true;

}



void printGraph(Graph g) {
	for (int i = 0; i < 50; i++) {
		cout << "Vertex: " << i << " has Edges:";
		for (int j = 0; j < g.v; j++) {
			cout << " " << g.adj[i][j];
		}
		cout << endl;
	}
}


void printEuler(Graph &g,int node) {
	for (int j = 0; j < 50;j++) {
		int i = g.adj[node][j];
		if (i > 0 && isValid(g, node, j)) {
			cout << node+1 << " " << j+1 << endl;
			rmvEdge(g, node, j);
			//printGraph(g);
			printEuler(g, j);
		}
	}

}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	freopen("sample.in", "r", stdin);
	int numCases;
	cin >> numCases;
	for (int c = 0; c<numCases; c++) {
		Graph g;
		memset(g.adj, 0, 50 * 50*sizeof(int));
		int numPieces;
		cin >> numPieces;
		int numEdges[50] = {};
		int v = 0;
		for (int i = 0; i < numPieces; i++) {
			int col1, col2;
			cin >> col1 >> col2;
			numEdges[--col1]++;
			numEdges[--col2]++;
			g.adj[col1][col2]++;
			//if (col1 != col2) {
				g.adj[col2][col1]++;

			//}
			v = col2;

		}
		int numVert = 0;
		bool isPossible = true;
		for (int i = 0; i < 50; i++) {
			if (numEdges[i] % 2 != 0) {
				isPossible = false;
			}
			if (numEdges[i] > 0) {
				numVert++;
			}
		}
		g.v = numVert;
		cout << "Case #" << c + 1 << endl;
		if (isPossible) {

			//memset(g.adj, 0, 50 * 50*sizeof(int));

			printEuler(g, v);
			//printGraph(g);
		}
		else {
			cout << "some trusses may be lost" << endl;
		}
		cout << endl;
	}
}
