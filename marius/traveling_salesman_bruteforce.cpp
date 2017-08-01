


typedef struct Point {
  int x;
  int y;
} Point;


int distance(Point a, Point b) {
  return abs(a.x - b.x) + abs(a.y - b.y);
}

int main() {

  int list_count;
  fastInput(list_count);
  for (int i = 0; i < list_count; i++) {
      int x,y, coins;
      Point start;
      fastInput(x);
      fastInput(y);
      fastInput(start.x);
      fastInput(start.y);
      fastInput(coins);
      vector<Point> coin_positions;
      int distances[coins][coins];
      coin_positions.resize(coins);
      for (int j = 0; j < coins; j++) {
        fastInput(coin_positions[j].x);
        fastInput(coin_positions[j].y);
        for (int k = 0; k <= j; k++) {
          distances[j][k] = distance(coin_positions[j], coin_positions[k]);
          distances[k][j] = distances[j][k];
        }
      }
      int min = INT_MAX/2;
      int permutations[coins];
      for (int j = 0; j < coins; j++) {
        permutations[j] = j;
      }
      do {
        int round_trip = distance(start, coin_positions[permutations[0]]);
        for (int j = 1; j < coins; j++) {
          round_trip += distances[permutations[j-1]][permutations[j]];
        }
        round_trip += distance(start, coin_positions[permutations[coins - 1]]);
        min = min > round_trip? round_trip : min;
      } while (next_permutation(permutations, permutations+coins));
      cout << min << endl;
  }
}
