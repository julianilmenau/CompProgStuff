#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

//dont use map, use unordered map (but only if neccessary), unsigned int[] are the best things
//maximum-spanning-tree kruskal can be found in 4_2, topologic sort in 4_1


//compare function for unsigned int_n_sign_posn
bool compare(unsigned int a, unsigned int b) {
  return a < b;
}




unsigned int dp(unsigned int *scores, vector<unsigned int> *adjacency_list, bool *visited, unsigned int *storage, unsigned int current_node){

  visited[current_node] = true;
  if (storage[current_node] != 0) {
    return storage[current_node];
  }
  unsigned int sum_incl = scores[current_node], sum_excl = scores[current_node] / 2;
  for (auto &e : adjacency_list[current_node]) {
    if (! visited[e]) {
      //cout << "current child " << e << endl;
      sum_excl += dp(scores, adjacency_list, visited, storage, e);
      sum_incl += scores[e]/ 2; // adjacent nodes are weighted half!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      for (auto &i : adjacency_list[e]) {
        if (0 != storage[i]) {
          //cout << "current grandchild " << i << endl;
          sum_incl += dp(scores, adjacency_list, visited, storage, i);
          //sum_incl += storage[i];
        }
      }
    }
  }
  //cout << "setting sum for " << current_node;
  if (sum_incl > sum_excl) {
    //cout << " to incl ";
    storage[current_node] = sum_incl;
  } else {
    //cout << " to excl ";
    storage[current_node] = sum_excl;
  }
  //cout << storage[current_node] << endl;
  return storage[current_node];
}


int main() {

  //IO optimization, you should either use c or c++ I/O but don't mix
  ios::sync_with_stdio(false);
  //cin.tie(NULL);

  unsigned int operation_count;
  fastInput(operation_count);
  //you can read everything first, and evaluate it afterwards
  for (unsigned int i = 0; i < operation_count; i++) {
      unsigned int systems, score, planet_a, planet_b;
      fastInput(systems);
      vector<unsigned int> adjacency_list[systems];
      // for (unsigned int j = 0; j < systems;j++) {
      //   adjacency_list[systems].reserve(500);
      // }
      bool visited[systems] = {0};
      // unsigned int *scores = new unsigned int[systems]; //allocation on the heap
      // unsigned int *storage = new unsigned int[systems];
      unsigned int storage[systems] = {0};
      unsigned int scores[systems] = {0};
      for (unsigned int j = 0; j < systems; j++) {
        fastInput(score);
        scores[j] = score * 2;
      }
      for (unsigned int j = 1; j < systems; j++) {
        fastInput(planet_a);
        fastInput(planet_b);
        adjacency_list[planet_a].push_back(planet_b);
        adjacency_list[planet_b].push_back(planet_a);
      }
      dp(scores, adjacency_list, visited, storage, 0);
      //for (unsigned int j = 0; j < systems; j++)
        cout << storage[0] / 2 << endl;
      //cout << endl;
  }
}
