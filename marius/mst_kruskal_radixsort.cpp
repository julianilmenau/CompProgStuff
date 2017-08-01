#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class UnionFind {
  int *id, cnt, *sz;
 public:
  UnionFind(int n) {
    cnt = n;
    id = new int[n];
    sz = new int[n];
    for (int i = 0; i < n; i++) {
      sz[i] = 0;
      id[i] = i;
    }
  }

  ~UnionFind() {
    delete[] id;
    delete[] sz;
  }

  int find(int p) {
    //cout << "find " << p << "parent: " << id[p] << endl;
    if (p != id[p]) {
      id[p] = find(id[p]);
    }
    return id[p];
  }

  void merge(int x, int y) {
    int i = find(x);
    int j = find(y);
    //cout << x << " " << y << endl;
   // cout << "id(x): " << i << " size(x): " << sz[i] << " id(y): " << j  << " size(y): " << sz[j] << endl;
    if (i != j) {
      if (sz[i] < sz[j]) {
        id[i] = j;
      } else if (sz[i] > sz[j]) {
        id[j] = i;
      } else {
        id[j] = i;
        sz[i]++;
      }
      cnt--;
    }
   // cout << "after merge id(x): " << find(x) << " id(y): " << find(y) << endl;
  }

  bool connected(int x, int y) {
    return (find(x) == find(y));
  }

  int count() {
    return cnt;
  }
};


bool compare(int a[3], int b[3]) {
  return a[2] > b[2];
}


void countingSort(int *arr[], int n, int exp) {
  int **output = new int*[n];
  int i, count[10] = {0};
  for(i = 0; i < n; i++) {
    count[(arr[i][2]/exp)%10]++;
  }
  for(i = 1; i < 10; i++) {
    count[i] += count[i-1]; //to set to 0 maybe;
  }
  for (i = n-1; i >= 0; i--) {
    output[count[(arr[i][2]/exp)%10] -1] = arr[i];
    count[ (arr[i][2]/exp)%10]--;
  }
  for (i = 0; i < n; i++) {
    arr[i] = output[i];
  }
}

void radixsort(int **arr, int n, int m) {
  for (int exp = 1; m/exp > 0; exp *= 10) {
    countingSort(arr, n, exp);
  }
  reverse(arr,arr+n);
}

int main() {
  int test_count;
  ios::sync_with_stdio(false);
  //cin >> test_count;
  scanf("%d", &test_count);
  for (int i = 0; i < test_count; i++) {
    int vertex_count, edge_count;
    //cin >> vertex_count >> edge_count;
    scanf("%d %d", &vertex_count, &edge_count);
    //cout << "v: " << vertex_count << ", e: " << edge_count << endl;
    UnionFind uf = UnionFind(vertex_count);
    int **edge_list = new int*[edge_count];
    int max = 0;
    for (int i = 0; i < edge_count; i++) {
      int a,b,w;
      //cin >> a >> b >> w;
      scanf("%d %d %d", &a, &b, &w);
      edge_list[i] = new int[3];
      edge_list[i][0] = a;
      edge_list[i][1] = b;
      edge_list[i][2] = w;
      if (w > max)
        max = w;
    }
    radixsort(edge_list, edge_count, max);

    int it = 0;
    int sum = 0;
    while ( uf.count() > 1) {
      int x = edge_list[it][0];
      int y = edge_list[it][1];

      if (! uf.connected(x,y)) {
        uf.merge(x,y);
        sum += edge_list[it][2];
      }
      it++;
    }
    printf("%d\n",sum);
    //cout << sum << endl;
  }
}
