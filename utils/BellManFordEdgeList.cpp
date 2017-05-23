#include <bits/stdc++.h>
using namespace std;

//################################    INPUT     ######################################

void fastInput(int &number) //not thread safe
{
    bool negative = false;
    register int c;

    number = 0;

    c = getchar_unlocked();
    if (c=='-')
    {
        negative = true;
        c = getchar_unlocked();
    }
    for (; (c>47 && c<58); c=getchar_unlocked())
        number = number *10 + c - 48;

    if (negative)
        number *= -1;
}

// ##########################################################################################

struct Edge {
    int start;
    int end;
    int weight;
};

struct GraphEdgeList {
    int numEdges;
    int numNodes;
    vector<Edge> edgeList;
};

//############################################### BellmanFord #####################################

void BellmanFord(struct GraphEdgeList* graph, int src)
{
	int V = graph->numNodes;
	int E = graph->numEdges;
	int dist[V];
	
	// Step 1: Initialize distances from src to all other vertices
	// as INFINITE
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX;
	dist[src] = 0;

	// Step 2: Relax all edges |V| - 1 times. A simple shortest 
	// path from src to any other vertex can have at-most |V| - 1 
	// edges
	for (int i = 1; i <= V-1; i++)
	{
		for (int j = 0; j < E; j++)
		{
			int u = graph->edgeList[j].start;
			int v = graph->edgeList[j].end;
			int weight = graph->edgeList[j].weight;
			if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
				dist[v] = dist[u] + weight;
		}
	}

	// Step 3: check for negative-weight cycles. The above step 
	// guarantees shortest distances if graph doesn't contain 
	// negative weight cycle. If we get a shorter path, then there
	// is a cycle.
	for (int i = 0; i < E; i++)
	{
		int u = graph->edgeList[i].start;
		int v = graph->edgeList[i].end;
		int weight = graph->edgeList[i].weight;
		if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
			printf("Graph contains negative weight cycle");
	}
	for (int i=0;i<V;i++) {
	    cout<<dist[i]<<endl;
	}
}


//################################    MAIN     ######################################

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int numCases,numNodes,numEdges;
	fastInput(numCases);
	for (int j=0;j<numCases;j++) {
		fastInput(numNodes);
		fastInput(numEdges);
		vector<Edge> newList;
		GraphEdgeList edges = {numEdges,numNodes,newList};
		for (int i=0;i<numEdges;i++) {
			int start,end,weight;
			fastInput(start);
			fastInput(end);
			fastInput(weight);
			edges.edgeList.push_back({start,end,weight});
		}
		int res[numNodes];
		BellmanFord(&edges,0);
		
	}
}

