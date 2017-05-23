#include <iostream>
using namespace std;
struct node {
	int key;
	node *father;
	};
 
 
node* find(node *pnode) {
	if (pnode->father==NULL) {
	    return pnode;
	}
	node *temp=pnode;
	while (temp->father!=NULL) {
		temp=temp->father;
	}
	pnode->father=temp;
	return temp;
}
 
void Union(node*x,node *y) {
	y->father = x;
}
int main() {

	ios_base::sync_with_stdio(false);
	int numGames;
	cin>>numGames;
	for (int i=0;i<numGames;i++) {
	    int numEvents,numChairs;
	    cin>>numChairs>>numEvents;
	    node *chairs[numChairs];
	    for (int j=0;j<numChairs;j++) {
	    	chairs[j]=new node();
	    	chairs[j]->key=j;
	    }
	   	for (int j=0;j<numEvents;j++) {
	        string event;int index,nextIndex;
	        cin>>event>>index;
	        nextIndex = (index==numChairs-1)? 0 : index+1;
	        //cout<<event<<"  "<<index<<"  "<<nextIndex<<endl;
	        node *chair=chairs[index];
	        node *nextchair=chairs[nextIndex];
	        if (event.compare("taken")==0) {
				Union(chairs[nextIndex],chairs[index]);
	        } else {
	        	//cout<<chairs[index]->key;
	            node *freeChair=find(chairs[index]);
	            //cout<<"found : "<<freeChair->key<<endl;
	            if (freeChair==chairs[index]) {
	                cout<<index<<endl;     
	            } else {
	                cout<<freeChair->key<<endl; 
	            }
	        }
	    }    
	}
	
	return 0;
}