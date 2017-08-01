#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

//dont use map, use unordered map (but only if neccessary), unsigned int[] are the best things
//maximum-spanning-tree kruskal can be found in 4_2, topologic sort in 4_1
 int start, end;

//compare function for unsigned int_n_sign_posn
bool compare(unsigned int a, unsigned int b) {
  return a < b;
}


pair<unsigned int,unsigned int> bfs(unsigned int start_node, unsigned int nodes, unsigned int **adjacency_matrix, vector<unsigned int> *adjacency_list) {
  queue<pair<unsigned int, unsigned int> > q;
  bool visited[nodes] = {0};
  q.push(make_pair(start_node, 0));
  pair <unsigned int, unsigned int> max_pair = make_pair(start_node, 0);
  while (! q.empty()) {
    pair<unsigned int, unsigned int> p = q.front();
    //cout << "popped " << p.first << " with distance " << p.second << endl;
    visited[p.first] = true;
    q.pop();
    vector<unsigned int> &v = adjacency_list[p.first];
    vector<unsigned int>::iterator it;
    for (it = v.begin(); it != v.end(); it++) {
      if (!visited[*it]) {
        pair <unsigned int, unsigned int> new_pair = make_pair(*it, p.second + adjacency_matrix[*it][p.first]);
        q.push(new_pair);
        if (new_pair.second > max_pair.second) {
          max_pair = new_pair;
        }
      }
    }
  }
  return max_pair;
}


int main() {

  //IO optimization, you should either use c or c++ I/O but don't mix
  ios::sync_with_stdio(false);
  //cin.tie(NULL);

      unsigned int nodes, length, node_a, node_b;
      fastInput(nodes);
      vector<unsigned int> adjacency_list[nodes];
      unsigned int longest_path[nodes] = {0};
      unsigned int height[nodes] = {0};
      unsigned int **adjacency_matrix = new unsigned int*[nodes]();
      for (int j = 0; j < nodes; j++) {
        adjacency_matrix[j] = new unsigned int[nodes];
      }
      for (unsigned int j = 1; j < nodes; j++) {
        fastInput(node_a);
        fastInput(node_b);
        fastInput(length);
        //cout << "a: " << node_a << " b: " << node_b << " length: " << length << endl;
        adjacency_list[node_a].push_back(node_b);
        adjacency_list[node_b].push_back(node_a);
        adjacency_matrix[node_a][node_b] = length;
        adjacency_matrix[node_b][node_a] = length;
      }
      //dp(adjacency_matrix, adjacency_list, visited, longest_path, 0, height);
      //for (unsigned int j = 0; j < nodes; j++)
        //cout << longest_path[0] << endl;
      //cout << endl;
      unsigned int a = bfs(0,nodes, adjacency_matrix,adjacency_list).first;
      pair<unsigned int, unsigned int> p = bfs(a,nodes, adjacency_matrix,adjacency_list);
      cout << p.second << "\n" << a << "\n" << p.first << endl;
  }
