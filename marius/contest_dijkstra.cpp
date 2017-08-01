#include <bits/stdc++.h>
using namespace std;

void fastInput(string &s) //not thread safe
{
    register char c;
    char chars[200];
    int i = 0;
    while ((c = getchar_unlocked()) != ' ' && (c != '\n'))
    	chars[i++] = c;
    s.assign(chars, chars + i);
}

void fastInput(long &number) //not thread safe
{
    register long c;

    number = 0;
    while((c = getchar_unlocked()) == ' ' || (c == '\n'));
    for (; (c>47 && c<58); c=getchar_unlocked())
        number = number *10 + c - 48;
}

void dijkstra(vector<pair<long, long>>* adjacency_list, long* dist, long numNodes, long s) {  //distances from node with id s (nodes[s])
	bool visited[numNodes] = { };
	typedef pair<long, long> P;
	priority_queue<P, vector<P>, greater<P>> q;
	for (long i = 0; i < numNodes; i++)
		dist[i] = LONG_MAX;
	dist[s] = 0;
	q.push(make_pair(0, s));
	for (long i = 0; i < numNodes; i++) {
		while (visited[q.top().second])
			q.pop();
		pair<long, long> topNode = q.top();
		q.pop();
		visited[topNode.second] = true;
		for (auto &e : adjacency_list[topNode.second])
			if (dist[e.first] > dist[topNode.second] + e.second) {
				dist[e.first] = dist[topNode.second] + e.second;
				q.push(make_pair(dist[e.first], e.first));
			}
	}
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	long tries;
	fastInput(tries);
	vector<pair<long, long>> adjacency_list[4000];
	long dist[4000];
	string from, to;
	long from_int, to_int, changed, weight;
	unordered_map<string, long> id_lookup;
	id_lookup["Gryffindor-Common-Room"] = 0;
  int counter = 1;
	long currentStart = 0;
	for (long i=0;i<tries;i++) {
		fastInput(to);
		if (id_lookup.find(to) == id_lookup.end())
			id_lookup[to] = counter++;
		long next = id_lookup[to];
		fastInput(changed);
		for (long j = 0; j < changed; j++) {
			fastInput(from);
			fastInput(to);
			fastInput(weight);
			if (id_lookup.find(from) == id_lookup.end())
				id_lookup[from] = counter++;
			if (id_lookup.find(to) == id_lookup.end())
				id_lookup[to] = counter++;
			from_int = id_lookup[from];
			to_int = id_lookup[to];
			bool alreadyThere = false;
			long c = 0;
			for (auto &e : adjacency_list[from_int]) {
				if (e.first == to_int) {
					if (weight == 0)
						adjacency_list[from_int].erase(adjacency_list[from_int].begin()+c);
					else
						e.second = weight;
					alreadyThere = true;
					break;
				}
				c++;
			}
			c = 0;
			if (alreadyThere) {
				for (auto &e : adjacency_list[to_int]) {
					if (e.first == from_int) {
						if (weight == 0)
							adjacency_list[to_int].erase(adjacency_list[to_int].begin()+c);
						else
							e.second = weight;
						break;
					}
					c++;
				}
			} else {
				//cout<<"new edge "<<from_int<<" -> "<<to_int<<": w = "<<l<<endl;
				adjacency_list[from_int].push_back(make_pair(to_int, weight));
				adjacency_list[to_int].push_back(make_pair(from_int, weight));
			}
		}
		dijkstra(adjacency_list, dist, id_lookup.size(), currentStart);
		cout << dist[next] << endl;
		currentStart = next;
	}
}
