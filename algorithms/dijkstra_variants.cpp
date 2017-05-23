#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int start;
    int end;
    int weight;
};

struct Node {
    vector<Edge> edgeList;
};

struct ListItem {
	ListItem* next;
	ListItem* prev;
	int id;
};

//###############################    DIJKSTRA    #####################################

void dijkstra(Node* nodes, int* dist, int numNodes, int s) {  //distances from node with id s (nodes[s])
	bool visited[numNodes];
	//INITIALZE ARRAYS
	for (int i = 0; i < numNodes; i++) {
		if (i == s) {
			dist[i] = 0;
		} else {
			dist[i] = INT_MAX;
		}
		visited[i] = false;
	}
	//ITERATE NODES
	for (int i = 0; i < numNodes; i++) {
		int jmin = -1;
		int min_dist = INT_MAX;
		for (int j = 0; j < numNodes; j++) {
			if (dist[j] < min_dist && !visited[j]) {
				min_dist = dist[j];
				jmin = j;
			}
		}
		visited[jmin] = true;
		Node minNode = nodes[jmin];
		for (auto edge : minNode.edgeList) {
			dist[edge.end] = min(dist[edge.end], dist[jmin] + edge.weight);
		}
	}
	return;
}

void dijkstraWithCS(Node* nodes, int* dist, int numNodes, int s) {  //distances from node with id s (nodes[s])
	int maxWeight = -1;
	bool visited[numNodes];
	//INITIALZE ARRAYS AND FIND MAX WEIGHT
	for (int i = 0; i < numNodes; i++) {
		if (i == s) {
			dist[i] = 0;
		} else {
			dist[i] = INT_MAX;
		}
		for (auto e : nodes[i].edgeList) {
			if (e.weight > maxWeight) {
				maxWeight = e.weight;
			}
		}
		visited[i] = false;
	}
	ListItem* buckets[numNodes * maxWeight] = {{ }};
	buckets[0] = new ListItem {nullptr, nullptr, s};
	//ITERATE BUCKETS (Zugriff auf buckets noch zu fixen)
	for (int i = 0; i < numNodes * maxWeight; i++) {
		if (buckets[i] != 0) {
			cout<<i<<endl;
			ListItem* iter = buckets[i];
			while (iter->next != nullptr) {
				for (auto edge : nodes[iter->id].edgeList) {
					if (dist[iter->id] + edge.weight < dist[edge.end]) {
						int oldDist = dist[edge.end];
						dist[edge.end] = dist[iter->id] + edge.weight;
						if (!visited[edge.end]) {
							visited[edge.end] = true;
							if (buckets[dist[edge.end]] == 0) {
								buckets[dist[edge.end]] = new ListItem {nullptr, nullptr, edge.end};
							} else {
								buckets[dist[edge.end]] = new ListItem {buckets[dist[edge.end]], nullptr, edge.end};
							}
						} else {
							if (buckets[dist[edge.end]] == 0) {
								buckets[dist[edge.end]] = new ListItem {nullptr, nullptr, edge.end};
							} else {
								buckets[dist[edge.end]] = new ListItem {buckets[dist[edge.end]], nullptr, edge.end};
							}
							ListItem* i = buckets[oldDist];
							while (i->id != edge.end) {
								i = iter->next;
							}
							i->prev->next = i->next;
							i->next->prev = i->prev;
						}
					}
				}
			}
		}
	}
	return;
}

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

//################################    PRINT GRAPH     ######################################

void printGraph(Node * firstNode,int n) {
    for (int i=0;i<n;i++) {
        cout<<"Node: "<<i<<" Edges: "<<firstNode[i].edgeList.size()<<endl;
        for (int j=0;j<firstNode[i].edgeList.size();j++){
            Edge k=firstNode[i].edgeList[j];
            cout<<"   start:"<<k.start<<" end: "<<k.end<<" weight: "<<k.weight<<endl;
            
        }    
    }
}

//################################    MAIN     ######################################

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	freopen("../graph_sample.in", "r", stdin);

	int numCases,numNodes,numEdges;
	fastInput(numCases);
	for (int j=0;j<numCases;j++) {
		fastInput(numNodes);
		fastInput(numEdges);
		Node nodes[numNodes];
		for (int i=0;i<numEdges;i++) {
			int start,end,weight;
			fastInput(start);
			fastInput(end);
			fastInput(weight);
			nodes[start].edgeList.push_back({start,end,weight});
		}
		printGraph(&nodes[0],numNodes);
		int dist[numNodes];
		dijkstraWithCS(nodes, dist, numNodes, 0);
		int min_dist = INT_MAX;
		int imin = -1;
		int max_dist = -1;
		int imax = -1;
		for (int i = 0; i < numNodes; i++) {
			if (dist[i] < min_dist && dist[i] > 0) {
				min_dist = dist[i];
				imin = i;
			}
			if (dist[i] > max_dist) {
				max_dist = dist[i];
				imax = i;
			}
		}
		cout<<"0 -> "<<imin<<" with "<<min_dist<<" is minimal"<<endl;
		cout<<"0 -> "<<imax<<" with "<<max_dist<<" is maximal"<<endl;
	}
}

