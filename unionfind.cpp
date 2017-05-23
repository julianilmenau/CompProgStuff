#include <bits/stdc++.h>
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
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
}
