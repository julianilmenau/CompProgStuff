#include <string>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int main() {
  int test_count;
  ios::sync_with_stdio(false);
  cin >> test_count;
  for (int i = 0; i < test_count; i++) {
    int station_count, train_count;
    cin >> station_count >> train_count;
    vector<int> adjacency_list[station_count];
    int input_edge_count[station_count] = {0};
    for (int j = 0; j < train_count; j++) {
      int start_point, end_point;
      cin >> start_point >> end_point;
      adjacency_list[start_point].push_back(end_point);
      input_edge_count[end_point]++;
    }
  vector<int> empty;
    for (int k = 0; k < station_count; k++){
      if (input_edge_count[k] == 0) {
        empty.push_back(k);
      }
    }
    while (!empty.empty()) {
      int to_visit = empty[0];
      for(int h: adjacency_list[to_visit]) {
        input_edge_count[h]--;
        if(input_edge_count[h] == 0) {
          empty.push_back(h);
        }
      }
      cout << to_visit << endl;
      empty.erase(empty.begin());
    }
  }
}
