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
	
	vector<int> graph[3000000];
	unordered_map<int,bool> visited;
	
	for (int i=0;i<numEdges;i++) {
		cin >> edgeStart >> edgeEnd;
		graph[edgeStart].push_back(edgeEnd);
		graph[edgeEnd].push_back(edgeStart);
	}
	
	for (int i=0;i<3000000;i++) {
		if (!visited[i] && graph[i].size()!=0) {
			vector<int> line;
			queue<int> nodes;
			//cout<<"searching from "<<k.first<< endl;
			nodes.push(i);
			visited[i]=1;
			line.push_back(i);
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
