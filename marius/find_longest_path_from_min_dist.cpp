#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <queue>

using namespace std;


void fill_buf(uint32_t* buf, uint32_t count) {
    uint32_t remaining = count * 4;
    uint8_t* bbuf = (uint8_t*)buf;

    while (remaining > 0) {
        auto r = read(0, bbuf, remaining);
        if (r <= 0) {
            std:://cerr << "Error reading input" << std::endl;
            exit(33);
        }
        remaining -= (uint32_t)r;
        bbuf += r;
    }
}

/// Read one unsigned 32bit integer from standard input.
uint32_t read_int() {
    uint32_t buf;
    fill_buf(&buf, 1);
    return buf;
}

/// Overwrite the contents of vec with `size` 32bit integers read from standard
/// input.
void read_vec(vector<uint32_t> &vec, uint32_t size) {
    vec.resize(size);
    fill_buf(vec.data(), size);
}



//dont use map, use unordered map (but only if neccessary), int[] are the best things
//maximum-spanning-tree kruskal can be found in 4_2, topologic sort in 4_1





int main() {

  //IO optimization, you should either use c or c++ I/O but don't mix
  ios::sync_with_stdio(false);
  //cerr << "starting" << endl;
  uint32_t list_count = read_int();
  //you can read everything first, and evaluate it afterwards
  //cerr << "list_count: " << list_count << endl;
  for (uint32_t i = 0; i < list_count; i++) {
      //code belongs here
      uint32_t nodes = read_int(), start_point = read_int();
      //cerr << "nodes: " << nodes << " start_point: " << start_point << endl;
      vector<vector<uint32_t> > adjacency_matrix(nodes);
      for (uint32_t j = 0; j < nodes; j++) {
        read_vec(adjacency_matrix[j], nodes);
      }
      uint32_t *hops = new uint32_t[nodes]();
      uint32_t *dist = new uint32_t[nodes]();
      for(int j = 0; j < nodes; j++) {
        for(int k = 0; k < nodes; k++) {
          //cerr << adjacency_matrix[j][k] << " ";
        }
        //cerr << endl;
      }
      queue<int> q;
      q.push(start_point);
      while (!q.empty()) {
        uint32_t next_node = q.front();
        q.pop();
        for (uint32_t j = 0; j < nodes; j++) {
          if (dist[next_node] + adjacency_matrix[next_node][j] == adjacency_matrix[start_point][j] && hops[next_node] >= hops[j] && next_node != j) {
            hops[j] = hops[next_node] + 1;
            dist[j] = adjacency_matrix[start_point][j];
            q.push(j);
          }
        }
      }
      uint32_t max_hops = 0, farest_node = start_point;
      for (uint32_t j = 0; j < nodes; j++) {
        if (hops[j] > max_hops) {
          max_hops = hops[j];
          farest_node = j;
        }
      }
      cout << farest_node << " " << max_hops << endl;
  }
}
