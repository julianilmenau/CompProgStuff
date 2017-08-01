#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;



int main() {
  int list_count;
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> list_count;
  //cout << 18446744073709551615;
  for (int i = 0; i < list_count; i++) {
    uint64_t upper, lower = 1;
    uint64_t edge = 1;
    char difficulty = 'h';
    while (true) {
      cout << "a " << edge << endl;
      cin >> difficulty;
      if (difficulty == 't') {
        upper = edge;
        break;
      }
      edge *= 2;
      if (edge == 0) {
        upper = 18446744073709551615;
        edge = upper;
        break;
      }
    }
    lower = edge/2;
    while (true) {
      edge = lower + (upper - lower)/2;
      cout << "a " << edge << endl;
      cin >> difficulty;
      if (difficulty == 'h') {
        lower = edge;
      } else {
        upper = edge;
      }
      if (upper  == lower +1) {
        cout << "i " << upper << endl;
        break;
      }
    }
  }
}
