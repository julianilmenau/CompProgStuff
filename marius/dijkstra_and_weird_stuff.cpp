#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <unordered_map>
#include <climits>
#include <bits/stdc++.h>
#include <queue>

using namespace std;

unsigned int* adjacency_matrix = new unsigned int[4001*4001]();
uint64_t* dist = new uint64_t[4000];

void fastInput(string &s) {
    register char c;
    char chars[200];
    int i = 0;
    while ((c = getchar_unlocked()) != ' ' && (c != '\n'))
    	chars[i++] = c;
    s.assign(chars, chars + i);
}

void fastInput(unsigned int &number) {
    register unsigned int c;

    number = 0;
    while((c = getchar_unlocked()) == ' ' || (c == '\n'));
    for (; (c>47 && c<58); c=getchar_unlocked())
        number = number *10 + c - 48;
}



int dijkstra(unsigned int s, unsigned int t, vector<unsigned int> adjacency_list[], unsigned int inc){

  fill(dist, dist+inc,ULLONG_MAX/2);
  int visited[inc] = {0};
  priority_queue<pair<uint64_t, unsigned int> , vector<pair<uint64_t, unsigned int>>, greater<pair<uint64_t, unsigned int> > >  q;
  dist[s] = 0;
  vector<unsigned int> next_vec;
  q.push(make_pair(0, s));
  unsigned int next;
  uint64_t new_dist;
  while(!q.empty()){
    next = q.top().second;
    q.pop();
    if(next == t){
      cout << dist[t] << "\n";
      return 0;
    }
    if(0 ==visited[next]){
      visited[next] = 1;
    vector<unsigned int>::iterator it;
  //  min = ULLONG_MAX/2;
    next_vec = adjacency_list[next];
  for( it = next_vec.begin(); it != next_vec.end();it++){
      new_dist = dist[next] + adjacency_matrix[next*4001+*it];
      if(!(new_dist>=ULLONG_MAX/2)){
      if(adjacency_matrix[next*4001+*it] != 0 && dist[*it]>new_dist && (0 == visited[*it])){
        dist[*it] = new_dist;
        q.push(make_pair(new_dist, *it));
        }
      }
    }
     }
  }
  cout << dist[t] << "\n";
  return 0;
}


int main(void) {
  ios::sync_with_stdio(false);
  unsigned int tries;
  fastInput(tries);
  unordered_map<string, unsigned int> id_lookup = {{"Gryffindor-Common-Room", 0}};
  id_lookup.reserve(4000);
  unsigned int start = 0;
  vector<unsigned int> adjacency_list[4001];
  for(int i = 0; i < 4002; i++) {
    adjacency_list[i].reserve(4000);
  }
  bool* visited = new bool[4001*4001]();
  unsigned int inc = 1;
  unsigned int changes, weight;
  string first, second;
  unsigned int m1, m2;
  unsigned int from, to;
  unsigned int s;
  string search;
  search.reserve(250);
  first.reserve(250);
  second.reserve(250);
  unordered_map<string, unsigned int>::const_iterator it;
  for(unsigned int i = 0; i<tries; i++){
    fastInput(search);
    fastInput(changes);
    for(unsigned int j = 0; j<changes; j++){
      fastInput(first);
      fastInput(second);
      fastInput(weight);
      it = id_lookup.find(first);
      if(it == id_lookup.end()){
        id_lookup.emplace(first, inc);
        from = inc;
        inc++;
      }
      else
        from = it->second;
      it = id_lookup.find(second);
      if(id_lookup.find(second) == id_lookup.end()){
        id_lookup.emplace(second, inc);
        to = inc;
        inc++;
      } else {
        to = it->second;
      }
      m1 = from*4001 + to;
      m2 = to*4001 + from;
      int c = 0;
      if (weight == 0) {
        for (auto &e :adjacency_list[from]) {
          if (e == to) {
            adjacency_list[from].erase(adjacency_list[from].begin()+c);
            visited[m2] = false;
            break;
          }
          c++;
        }
        c = 0;
        for (auto &e : adjacency_list[to]) {
          if (e == from) {
            adjacency_list[to].erase(adjacency_list[to].begin()+c);
            visited[m2] = false;
            break;
          }
          c++;
        }
      }
      if(!visited[m1]){
        adjacency_list[from].push_back(to);
        visited[m1] = true;
      }
      if(!visited[m2]){
        adjacency_list[to].push_back(from);
        visited[m2] = true;
      }
      adjacency_matrix[m1] = weight;
      adjacency_matrix[m2] = weight;
    }
    s = id_lookup[search];
    dijkstra(start, s,adjacency_list, inc);
    start = s;
  }
  cout.flush();
}
