#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

struct Point {
  double x,y;
};

Point p0;

double distSq(Point p1, Point p2) {
    return (p1.x - p2.x)*(p1.x - p2.x) +
          (p1.y - p2.y)*(p1.y - p2.y);
}


// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
double orientation(Point p, Point q, Point r){
   double val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
    //cout << val << endl;
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

bool compare1(const Point p1, const Point p2){
   // Find orientation
  double o = orientation(p0, p1, p2);
   if (o == 0)
     return (distSq(p0, p2) >= distSq(p0, p1))? true : false;

   return (o == 2)? true: false;
}

void swap(Point &a, Point &b) {
  Point tmp =  a;
  a = b;
  b = tmp;
}

Point nextToTop(stack<Point> &S){
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}


int main() {

  cout.setf(ios::fixed,ios::floatfield);
  cout.precision(3);
  int list_count;
  cin >> list_count;

  for (int i = 0; i < list_count; i++) {
      int point_count;
      cin >> point_count;
      Point* points = new Point[point_count];
      for (int j = 0; j < point_count; j++) {
        int x,y;
        cin >> x;
        cin >> y;
        points[j].x = (double)x;
        points[j].y = (double)y;
      }

     int ymin = points[0].y, min = 0;
      for (int j = 0; j < point_count; j++) {
        if ((points[j].y < ymin) || (points[j].y == ymin && points[j].x < points[min].x) ) {
          ymin = points[j].y;
          min = j;
        }
      }
      swap(points[0], points[min]);
      p0 = points[0];

      sort(points + 1, points + point_count, compare1);

     int m = 1;
      for (int j = 1; j< point_count; j++) {
        while (j < point_count-1 && orientation(p0, points[j], points[j+1]) == 0) {
          j++;
        }

        points[m] = points[j];
        m++;
      }
      //cout << "m: " << m << endl;
      if (m < 2) {
        cout << 0 << endl;
        continue;
      }
      if (m == 2) {
        cout << sqrt(distSq(points[0],points[1])) << endl;
        continue;
      }

      stack<Point> S;
      S.push(points[0]);
      S.push(points[1]);
      S.push(points[2]);
      for (int j = 3; j < m; j++) {
        while (orientation(nextToTop(S), S.top(), points[j]) != 2) {
          //cout << "Popped " << S.top().x << " " << S.top().y << endl;
          S.pop();
        }
        S.push(points[j]);
      }
      double sum = sqrt(distSq(p0,S.top()));
      Point a,b = S.top();
      S.pop();
      while (! S.empty()) {
        a = b;
        b = S.top();
        S.pop();
        sum += sqrt(distSq(a,b));
      }
      cout << sum << "\n";
  }
  cout.flush();
}
