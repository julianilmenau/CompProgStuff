#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include <math.h>

using namespace std;



int main() {
  int nodes, edges, questions;
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> nodes >> edges >> questions;
  long ** floyd_warshall = new long*[nodes];
  for (int i = 0; i < nodes; i++) {
    floyd_warshall[i] = new long[nodes];
    for (int j = 0; j < nodes; j++) {
      floyd_warshall[i][j] = 100000000;
    }
    floyd_warshall[i][i] = 0;
  }
  for (int i = 0; i < edges; i++) {
    int a,b,w;
    cin >> a >> b >> w;
    floyd_warshall[a][b] = w;
  }
  for (int k = 0; k < nodes; k++) {
    for (int i = 0; i < nodes; i++) {
      for (int j = 0; j < nodes; j++) {
        if (!((floyd_warshall[i][k] == 100000000) || (floyd_warshall[k][j] == 100000000)) &&(floyd_warshall[i][k] + floyd_warshall[k][j] < floyd_warshall[i][j]))
          floyd_warshall[i][j] = floyd_warshall[i][k] + floyd_warshall[k][j];
      }
    }
  }
  // for (int i = 0; i < nodes; i++) {
  //   for (int j = 0; j < nodes; j++) {
  //     cout << floyd_warshall[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  for (int i = 0; i < questions; i++) {
    int a, b;
    cin >> a >> b;
    if (floyd_warshall[a][b] >= 100000000) {
      cout << "oo" << endl;
    }else {
      cout << floyd_warshall[a][b] << endl;
    }
  }


}
