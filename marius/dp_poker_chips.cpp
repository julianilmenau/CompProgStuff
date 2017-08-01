#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>

using namespace std;


void fastInput(int &number) {
    register int c;

    number = 0;
    while((c = getchar_unlocked()) == ' ' || (c == '\n'));
    for (; (c>47 && c<58); c=getchar_unlocked())
        number = number *10 + c - 48;
    ////cout << number << endl;
}

void fastInput(string &s) {
    register char c;
    char chars[200];
    int i = 0;
    while ((c = getchar_unlocked()) != ' ' && (c != '\n'))
    	chars[i++] = c;
    s.assign(chars, chars + i);
}






int main() {

  //IO optimization, you should either use c or c++ I/O but don't mix
  ios::sync_with_stdio(false);
  int case_count;
  fastInput(case_count);
  for (int k = 0; k < case_count; k++) {
    int stack_count, sum = 0, chip_count;
    int stacks[5] = {0};
    int **full_chips = new int*[5]();
    fastInput(stack_count);
    if (stack_count < 2) { //shortcut
      return 0;
    }
    for (int i = 0; i < 5 ;i++) {
      stacks[i] = 0;
    }
    for (int i = 0; i < stack_count; i++) {
        fastInput(stacks[i]);
    }
    for (int i = 0; i < 5; i++) {
      full_chips[i] = new int[stacks[i] + 1]();
      for (int j = 0; j < stacks[i]; j++) {
        fastInput(full_chips[i][j]);
      }
      full_chips[i][stacks[i]] = -1;
    }
    for (int i = 0; i < 5; i++) {
      //cout << stacks[i] << " ";
    }
    //cout << endl;
    long *****maximum_array = new long****[stacks[0]+1]();
    for(int a = 0; a < stacks[0] + 1; a++) {
      maximum_array[a] = new long***[stacks[1]+1]();
      for(int b = 0; b < stacks[1] + 1; b++) {
        maximum_array[a][b] = new long**[stacks[2]+1]();
        for(int c = 0; c < stacks[2] + 1; c++) {
          maximum_array[a][b][c] = new long*[stacks[3]+1]();
          for(int d = 0; d < stacks[3] + 1; d++) {
            maximum_array[a][b][c][d] = new long[stacks[4]+1]();
            for (int e = 0; e < stacks[4] + 1; e++){
              maximum_array[a][b][c][d][e] = 0;
              //cout << "hallo" << endl;
            }
          }
        }
      }
    }
    long maximum;
    for(int a = 0; a < stacks[0] + 1; a++) {
      for(int b = 0; b < stacks[1] + 1; b++) {
        for(int c = 0; c < stacks[2] + 1; c++) {
          for(int d = 0; d < stacks[3] + 1; d++) {
            for (int e = 0; e < stacks[4] + 1; e++){
              maximum = 0;
              if (a != 0)
                maximum = maximum_array[a-1][b][c][d][e];
              if (b != 0)
                maximum = max(maximum,maximum_array[a][b-1][c][d][e]);
              if (c != 0)
                maximum = max(maximum,maximum_array[a][b][c-1][d][e]);
              if (d != 0)
                maximum = max(maximum,maximum_array[a][b][c][d-1][e]);
              if (e != 0)
                maximum = max(maximum,maximum_array[a][b][c][d][e-1]);

              if (a != 0 && b != 0 && full_chips[0][a-1] == full_chips[1][b-1])
                maximum = max(maximum_array[a-1][b-1][c][d][e] +1, maximum);
              if (a != 0 && c != 0 && full_chips[0][a-1] == full_chips[2][c-1])
                maximum = max(maximum_array[a-1][b][c-1][d][e] +1, maximum);
              if (a != 0 && d != 0 && full_chips[0][a-1] == full_chips[3][d-1])
                maximum = max(maximum_array[a-1][b][c][d-1][e] +1, maximum);
              if (a != 0 && e != 0 && full_chips[0][a-1] == full_chips[4][e-1])
                maximum = max(maximum_array[a-1][b][c][d][e-1] +1, maximum);
            if (b != 0 && c != 0 && full_chips[1][b-1] == full_chips[2][c-1])
              maximum = max(maximum_array[a][b-1][c-1][d][e] +1, maximum);
            if (b != 0 && d != 0 && full_chips[1][b-1] == full_chips[3][d-1])
              maximum = max(maximum_array[a][b-1][c][d-1][e] +1, maximum);
            if (b != 0 && e != 0 && full_chips[1][b-1] == full_chips[4][e-1])
              maximum = max(maximum_array[a][b-1][c][d][e-1] +1, maximum);

            if (c != 0 && d != 0 && full_chips[2][c-1] == full_chips[3][d-1])
              maximum = max(maximum_array[a][b][c-1][d-1][e] +1, maximum);
            if (c != 0 && e != 0 && full_chips[2][c-1] == full_chips[4][e-1])
              maximum = max(maximum_array[a][b][c-1][d][e-1] +1, maximum);

            if (d != 0 && e != 0 && full_chips[3][d-1] == full_chips[4][e-1])
              maximum = max(maximum_array[a][b][c][d-1][e-1] +1, maximum);
            if (a != 0 && b != 0 && c != 0 && full_chips[0][a-1] == full_chips[1][b-1] && full_chips[0][a-1] == full_chips[2][c-1])
              maximum = max(maximum_array[a-1][b-1][c-1][d][e] +2, maximum);
            if (a != 0 && b != 0 && d != 0 && full_chips[0][a-1] == full_chips[1][b-1] && full_chips[0][a-1] == full_chips[3][d-1])
              maximum = max(maximum_array[a-1][b-1][c][d-1][e] +2, maximum);
            if (a != 0 && b != 0 && e != 0 && full_chips[0][a-1] == full_chips[1][b-1] && full_chips[0][a-1] == full_chips[4][e-1])
              maximum = max(maximum_array[a-1][b-1][c][d][e-1] +2, maximum);
            if (a != 0 && c != 0 && d != 0 && full_chips[0][a-1] == full_chips[2][c-1] && full_chips[0][a-1] == full_chips[3][d-1])
              maximum = max(maximum_array[a-1][b][c-1][d-1][e] +2, maximum);
            if (a != 0 && c != 0 && e != 0 && full_chips[0][a-1] == full_chips[2][c-1] && full_chips[0][a-1] == full_chips[4][e-1])
              maximum = max(maximum_array[a-1][b][c-1][d][e-1] +2, maximum);
            if (a != 0 && d != 0 && e != 0 && full_chips[0][a-1] == full_chips[3][d-1] && full_chips[0][a-1] == full_chips[4][e-1])
              maximum = max(maximum_array[a-1][b][c][d-1][e-1] +2, maximum);
            if (b != 0 && c != 0 && d != 0 && full_chips[1][b-1] == full_chips[2][c-1] && full_chips[1][b-1] == full_chips[3][d-1])
              maximum = max(maximum_array[a][b-1][c-1][d-1][e] +2, maximum);
            if (b != 0 && c != 0 && e != 0 && full_chips[1][b-1] == full_chips[2][c-1] && full_chips[1][b-1] == full_chips[4][e-1])
              maximum = max(maximum_array[a][b-1][c-1][d][e-1] +2, maximum);
            if (b != 0 && d != 0 && e != 0 && full_chips[1][b-1] == full_chips[3][d-1] && full_chips[1][b-1] == full_chips[4][e-1])
              maximum = max(maximum_array[a][b-1][c][d-1][e-1] +2, maximum);
            if (c != 0 && d != 0 && e != 0 && full_chips[2][c-1] == full_chips[3][d-1] && full_chips[2][c-1] == full_chips[4][e-1])
              maximum = max(maximum_array[a][b][c-1][d-1][e-1] +2, maximum);
            if (a != 0 && b != 0 && c != 0 && d != 0 && full_chips[0][a-1] == full_chips[1][b-1] && full_chips[0][a-1] == full_chips[2][c-1] && full_chips[0][a-1] == full_chips[3][d-1])
              maximum = max(maximum_array[a-1][b-1][c-1][d-1][e] +4, maximum);
            if (a != 0 && b != 0 && c != 0 && e != 0 && full_chips[0][a-1] == full_chips[1][b-1] && full_chips[0][a-1] == full_chips[2][c-1] && full_chips[0][a-1] == full_chips[4][e-1])
              maximum = max(maximum_array[a-1][b-1][c-1][d][e-1] +4, maximum);
            if (a != 0 && b != 0 && d != 0 && e != 0 && full_chips[0][a-1] == full_chips[1][b-1] && full_chips[0][a-1] == full_chips[4][e-1] && full_chips[0][a-1] == full_chips[3][d-1])
              maximum = max(maximum_array[a-1][b-1][c][d-1][e-1] +4, maximum);
            if (a != 0 && c != 0 && d != 0 && e != 0 && full_chips[0][a-1] == full_chips[4][e-1] && full_chips[0][a-1] == full_chips[2][c-1] && full_chips[0][a-1] == full_chips[3][d-1])
              maximum = max(maximum_array[a-1][b][c-1][d-1][e-1] +4, maximum);
            if (e != 0 && b != 0 && c != 0 && d != 0 && full_chips[4][e-1] == full_chips[1][b-1] && full_chips[4][e-1] == full_chips[2][c-1] && full_chips[4][e-1] == full_chips[3][d-1])
              maximum = max(maximum_array[a][b-1][c-1][d-1][e-1] +4, maximum);

            if (a != 0 && b != 0 && c != 0 && d != 0 && e != 0 && full_chips[0][a-1] == full_chips[1][b-1] && full_chips[0][a-1] == full_chips[2][c-1] && full_chips[0][a-1] == full_chips[3][d-1] && full_chips[0][a-1] == full_chips[4][e-1])
              maximum = max(maximum_array[a-1][b-1][c-1][d-1][e-1] +8, maximum);
            //cout << "setting " << a << " " << b << " " << c << " " << d << " " << e << " to " << maximum << endl;
            maximum_array[a][b][c][d][e] = maximum;
            }
          }
        }
      }
    }
    //cout << maximum << endl;
    //cout << "asfd" << endl;
    cout << maximum_array[stacks[0]][stacks[1]][stacks[2]][stacks[3]][stacks[4]] << endl;
  }
}
