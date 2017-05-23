
void dfsvisit(vector<int> *graph,bool *visited,int i) {
	*(visited+i)=1;
	vector<int> adj=*(graph+i);
	for (int j:adj) {
		if (!(*(visited+j))) {
			dfsvisit(graph,visited,j);
		}
	}
	result.push(i);
}
