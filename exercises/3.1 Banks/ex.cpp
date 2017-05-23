#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>


using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	int numEdges, edgeStart, edgeEnd;
	cin >> numEdges;
	
	typedef vector<int> edgeList;
	
	unordered_map<int,edgeList> graph;
	unordered_map<int,bool> visited;
	
	for (int i=0;i<numEdges;i++) {
		cin >> edgeStart >> edgeEnd;
		if (!graph.count(edgeStart)) {
            graph.emplace(edgeStart,vector<int>{});
			visited.emplace(edgeStart,0);
		}
		if (!graph.count(edgeEnd)) {
            graph.emplace(edgeEnd,vector<int>{});
            visited.emplace(edgeEnd,0);
		}
		graph[edgeStart].push_back(edgeEnd);
		graph[edgeEnd].push_back(edgeStart);
	}
	
	for (auto k:graph) {
		if (!visited[k.first]) {
			vector<int> line;
			queue<int> nodes;
			//cout<<"searching from "<<k.first<< endl;
			nodes.push(k.first);
			visited[k.first]=1;
			line.push_back(k.first);
			while(!nodes.empty()) {
				int node=nodes.front();
				nodes.pop();
				//cout<<"  over node:"<<node<<endl;
				for (int i=0;i<graph[node].size();i++) {
					int child=graph[node][i];
					if (!visited[child]) {
						//cout<<"    found node:" << child<<endl;
						visited[child]=1;
						nodes.push(child);
						line.push_back(child);
					}
				}
			}
			sort(line.begin(),line.end());
			cout<<line.front();
			line.erase(line.begin());
			for (auto j:line) {
				cout<<", "<<j;
			}
			cout<<endl;
		}	
	}
}
