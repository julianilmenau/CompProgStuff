#include <bits/stdc++.h>
using namespace std;

void dfsvisit(vector<int> *graph,bool *visited,int i) {
	*(visited+i)=1;
	vector<int> adj=*(graph+i);
	for (int j:adj) {
		if (!(*(visited+j))) {
			//NEEDS OUTPUT OR SO
			//i.e. nNodes++; or totalWeight += graph[i][j].weight or so:
			dfsvisit(graph,visited,j);
		}
	}

}


int main() {
	ios_base::sync_with_stdio(false);
	int numEdges, edgeStart, edgeEnd,numCases,numNodes;
	cin >> numCases;
	for (int k=0;k<numCases;k++) {
		typedef vector<int> edgeList;
		cin>>numNodes>>numEdges;
		vector<int> graph[numNodes];
		bool visited[numNodes]={};
		for (int i=0;i<numEdges;i++) {
			cin >> edgeStart >> edgeEnd;
			graph[edgeStart].push_back(edgeEnd);
		}
		//cout<<numNodes<<endl;
		for (int i=0;i<numNodes;i++) {
			//cout<<visited[i]<<endl;
			if (!visited[i]){
				dfsvisit(&graph[0],&visited[0],i);
			}
		}
	}
}
