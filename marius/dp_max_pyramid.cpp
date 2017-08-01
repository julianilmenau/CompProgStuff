#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

struct dp_field {
  int left_fields, largestPyramid, largestPyramidReversed, upper_fields, largestPyramidTurned, largestPyramidTurnedReversed;
};



int main() {

  int list_count;
  cin >> list_count;
  for (int i = 0; i < list_count; i++) {
    int width, height;
    cin >> width >> height;
    bool **matrix = new bool*[height]();
    dp_field **dp_matrix = new dp_field*[height]();
    int maxi = 0;
    for(int j = 0; j < height; j++) {
      matrix[j] = new bool[width]();
      dp_matrix[j] = new dp_field[width]();
      for(int k = 0; k < width; k++) {
        dp_matrix[j][k] = {0,0,0,0,0,0};
        char used;
        cin >> used;
        if (used == 'f') {
          matrix[j][k] = false;
          dp_matrix[j][k] = {1,1,1,1,1,1};
          maxi = 1;
          if (k != 0) {
            dp_matrix[j][k].left_fields = 1 + dp_matrix[j][k-1].left_fields;
          }
          if (j != 0) {
            dp_matrix[j][k].upper_fields = 1 + dp_matrix[j-1][k].upper_fields;
          }
        } else {
          matrix[j][k] = true;
        }
        // cout << dp_matrix[j][k].upper_fields << " ";
      }
      // cout << endl;
    }
    for (int j = 0; j < height; j++) {
      for(int k = 0; k < width; k++) {
        if (j != 0 && dp_matrix[j][k].largestPyramid != 0 && dp_matrix[j-1][k].largestPyramid > 0) {
          int a = dp_matrix[j-1][k].largestPyramid, b = ((a+1) / 2) + k;
          while ((b >= width) || (b > k && dp_matrix[j][b].left_fields < a + 2)) {
            a = a - 2;
            b--;
          }
          dp_matrix[j][k].largestPyramid = a + 2;
          if (a+2 > maxi) {
            maxi = a+2;
          }
        }
        if (j != 0 && dp_matrix[height-j-1][k].largestPyramidReversed != 0 && dp_matrix[height-(j)][k].largestPyramidReversed > 0) {
          int a = dp_matrix[height-(j)][k].largestPyramidReversed, b = ((a+1) / 2) + k;
          while ((b >= width) || (b > k && dp_matrix[height-j-1][b].left_fields < a + 2)) {
            a = a - 2;
            b--;
          }
          dp_matrix[height-j-1][k].largestPyramidReversed = a + 2;
          if (a+2 > maxi) {
            maxi = a+2;
          }
        }


      }
    }

    for (int k = 0; k < width; k++) {
      for(int j = 0; j < height; j++) {
        if (k != 0 && dp_matrix[j][k].largestPyramidTurned != 0 && dp_matrix[j][k-1].largestPyramidTurned > 0) {
          int a = dp_matrix[j][k-1].largestPyramidTurned, b = ((a+1) / 2) + j;
          while ((b >= height) || (b > j && dp_matrix[b][k].upper_fields < a + 2)) {
            a = a - 2;
            b--;
          }
          dp_matrix[j][k].largestPyramidTurned = a + 2;
          if (a+2 > maxi) {
            maxi = a+2;
          }
        }
        if (k != 0 && dp_matrix[j][width-k-1].largestPyramidTurnedReversed != 0 && dp_matrix[j][width-k].largestPyramidTurnedReversed > 0) {
          int a = dp_matrix[j][width-k].largestPyramidTurnedReversed, b = ((a+1) / 2) + j;
          while ((b >= height) || (b > j && dp_matrix[b][width - k - 1].upper_fields < a + 2)) {
            a = a - 2;
            b--;
          }
          dp_matrix[j][width-k-1].largestPyramidTurnedReversed = a + 2;
          if (a+2 > maxi) {
            maxi = a+2;
          }
        }


      }
    }


    int sum = 0;
    while (maxi > 0) {
      sum += maxi;
      maxi -= 2;
    }
    cout << sum << endl;
  }
}
