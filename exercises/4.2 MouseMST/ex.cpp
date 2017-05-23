#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct node {
	node *father;
	int key;
	int numNodes;
	};
	
bool compare(const pair<int,pair<int,int>> &a,const pair<int,pair<int,int>> &b) {
	return a.first>b.first;
}
	
node makeSet(int key) {
	node result = {NULL,key,1};
	return result;
}

int find(node &pnode) {
	node *temp=&pnode;
	while (temp->father!=NULL) {
		temp=temp->father;
	}
	if (!(pnode.father==NULL)) {
		pnode.father=temp;
	}
	//cout<<"   is: "<<temp->key<<endl;
	return temp->key;
}

void Union(node &x,node &y) {
	y.father = &x;
	y.numNodes+=x.numNodes;
}

int main() {
    
	int numCases,numNodes,numEdges;
	cin>>numCases;
	for (int j=0;j<numCases;j++) {
		cin>>numNodes>>numEdges;
		pair<int,pair<int,int>> edges[numEdges];
		for (int i=0;i<numEdges;i++) {
			int start,end,weight;
			cin >> start >> end >> weight;
			edges[i].first=weight;
			edges[i].second.first=start;
			edges[i].second.second=end;
		    

		}
		sort(edges,edges+numEdges,compare);
	
		vector<node> nodes(numNodes);
		for (int i=0;i<numNodes;i++) {
		    nodes[i]=makeSet(i);
	    
		}
		pair<int,pair<int,int>> *iter=&edges[0];
		int numTrees=numNodes;
		int weightSum=0;
		while (numTrees>1) {
			node x=nodes[iter->second.first];
		    node y=nodes[iter->second.second];
		    //cout<<"Checking edge:("<<x.key<<","<<y.key<<")"<<endl;
		    //cout<<"  found:("<<find(x)<<","<<find(y)<<")"<<endl;
		    //cout<<"  numNodes:("<<x.numNodes<<","<<y.numNodes<<")"<<endl;
		    
		    if (!(find(x)==find(y))) {
		    	//cout<<"   different Trees"<<endl;
		    	if (x.numNodes>y.numNodes) {
		            node temp=x;
		            x=y;
		            y=temp;
		        }
		        Union(nodes[find(nodes[x.key])],nodes[find(nodes[y.key])]);
		        //cout<<" father of: "<<nodes[y.key].key<<" is now: "<<nodes[y.key].father->key<<endl;;
		        numTrees--;
		        weightSum+=iter->first;
			    }
		    
		    iter++;
		}
		cout<<weightSum<<endl;
	}
}
