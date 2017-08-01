#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
#include <limits.h>

using namespace std;



int main() {

  int list_count;
  fastInput(list_count);
  for (int i = 0; i < list_count; i++) {

    int parcels;
    fastInput(parcels);
    vector<int> stack_a; stack_a.resize(parcels+1);
    vector<int> stack_b; stack_b.resize(parcels+1);
    int** dp = new int*[parcels+1];
    int sum_list_a[parcels+1] = {0};
    int sum_list_b[parcels+1] = {0};
    for (int j = 0; j < parcels+1; j++) {
      dp[j] = new int[parcels+1]();
      for (int k = 0; k < parcels+1; k++) {
        dp[j][k] = INT_MAX/2;
      }
    }
    for (int j = 0; j < parcels; j++) {
      int volume;
      fastInput(volume);
      stack_a[j+1] = volume;
    }
    for (int j = 0; j < parcels; j++) {
      int weight;
      fastInput(weight);
      stack_b[j+1] = weight;
    }

    for (int j = 0; j < parcels; j++) {
      sum_list_a[j+1] = sum_list_a[j] + stack_a[j+1];
      sum_list_b[j+1] = sum_list_b[j] + stack_b[j+1];
    }
    dp[0][0] = 0;
    for (int j = 1; j < parcels+1; j++) {
      for (int k = 1; k < parcels+1; k++) {
        if ((k == parcels && j != parcels) || (j == parcels && k != parcels)) {
          continue;
        }
        for (int a = 0; a < j; a++) {

            if (dp[j][k] < dp[a][k-1]) {
              continue;
            }
            int product = ((sum_list_b[k] - sum_list_b[k-1] - 1) * (sum_list_a[j] - sum_list_a[a] - j + a)) + dp[a][k-1];
            if (product < dp[j][k]) {
              dp[j][k] = product;
            }
        }
        for (int b = 0; b < k; b++) {
            if (dp[j][k] < dp[j-1][b]) {
              continue;
            }
            int product = ((sum_list_b[k] - sum_list_b[b] - k + b) * (sum_list_a[j] - sum_list_a[j-1] - 1)) + dp[j-1][b];
            if (product < dp[j][k]) {
              dp[j][k] = product;
            }
        }
      }
    }

    cout << dp[parcels][parcels] << endl;


  }
}
