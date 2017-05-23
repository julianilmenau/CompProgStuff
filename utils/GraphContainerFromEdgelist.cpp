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

struct Node {
    vector<Edge> edgeList;
};

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
	}
}
