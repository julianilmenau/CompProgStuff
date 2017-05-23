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
	x = find(x);
	y = find(y);
	if (y.numNodes > x.numNodes) {
		node tmp = x;
		x = y;
		y = tmp;
	y.father = &x;
	y.numNodes += x.numNodes;
}
