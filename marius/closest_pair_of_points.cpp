#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <math.h>
#include <bits/stdc++.h>
#include <vector>

using namespace std;



struct Point
{
  unsigned long long x, y;
};

// Needed to sort array of points according to X coordinateunsigned
 int compareX(const void* a, const void* b)
{
    Point *p1 = (Point *)a,  *p2 = (Point *)b;
    return (p1->x - p2->x);
}
// Needed to sort array of points according to Y coordinateunsigned
 int compareY(const void* a, const void* b)
{
    Point *p1 = (Point *)a,   *p2 = (Point *)b;
    return (p1->y - p2->y);
}

// A utility function to find the distance between two points
float dist(Point p1, Point p2)
{
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
                 (p1.y - p2.y)*(p1.y - p2.y)
               );
}

// A Brute Force method to return the smallest distance between two points
// in P[] of size n
float bruteForce(Point P[],int n)
{
    float min = FLT_MAX;
    for (unsigned long long i = 0; i < n; ++i)
        for (unsigned long long j = i+1; j < n; ++j)
            if (dist(P[i], P[j]) < min)
                min = dist(P[i], P[j]);
    return min;
}

// A utility function to find minimum of two float values
float min(float x, float y)
{
    return (x < y)? x : y;
}


// A utility function to find the distance beween the closest points of
// strip of given size. All points in strip[] are sorted accordint to
// y coordinate. They all have an upper bound on minimum distance as d.
// Note that this method seems to be a O(n^2) method, but it's a O(n)
// method as the inner loop runs at most 6 times
float stripClosest(Point strip[],int size, float d)
{
    float min = d;  // Initialize the minimum distance as d

    // Pick all points one by one and try the next points till the difference
    // between y coordinates is smaller than d.
    // This is a proven fact that this loop runs at most 6 times
    for (unsigned long long i = 0; i < size; ++i)
        for (unsigned long long j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i],strip[j]) < min)
                min = dist(strip[i], strip[j]);

    return min;
}

// A recursive function to find the smallest distance. The array Px contains
// all points sorted according to x coordinates and Py contains all points
// sorted according to y coordinates
float closestUtil(Point Px[], Point Py[],int n)
{
    // If there are 2 or 3 points, then use brute force
    if (n <= 3)
        return bruteForce(Px, n);

    // Find the middle point
  unsigned long long mid = n/2;
    Point midPoint = Px[mid];


    // Divide points in y sorted array around the vertical line.
    // Assumption: All x coordinates are distinct.
    Point Pyl[mid+1];   // y sorted points on left of vertical line
    Point Pyr[n-mid-1];  // y sorted points on right of vertical line
  unsigned long long li = 0, ri = 0;  // indexes of left and right subarrays
    for (unsigned long long i = 0; i < n; i++)
    {
      if (Py[i].x <= midPoint.x)
         Pyl[li++] = Py[i];
      else
         Pyr[ri++] = Py[i];
    }

    // Consider the vertical line passing through the middle point
    // calculate the smallest distance dl on left of middle point and
    // dr on right side
    float dl = closestUtil(Px, Pyl, mid);
    float dr = closestUtil(Px + mid, Pyr, n-mid);

    // Find the smaller of two distances
    float d = min(dl, dr);

    // Build an array strip[] that contains points close (closer than d)
    // to the line passing through the middle point
    Point strip[n];
  unsigned long long j = 0;
    for (unsigned long long i = 0; i < n; i++)
        if (abs(Py[i].x - midPoint.x) < d)
            strip[j] = Py[i], j++;

    // Find the closest points in strip.  Return the minimum of d and closest
    // distance is strip[]
    return min(d, stripClosest(strip, j, d) );
}

 int main() {


  vector<Point>* floors = new vector<Point>[50]; //allocation on the heap
  for(unsigned long long j = 0; j < 50; j++) {
    floors[j] = vector<Point>();
    floors[j].reserve(100);
  }

unsigned long long pupils;
  cin >> pupils;

  for (unsigned long long i = 0; i < pupils; i++) {
  unsigned long long x,y,f;
    cin >> x;
    cin >> y;
    cin >> f;

    floors[f].push_back({x,y});
  }

  float min_dist = FLT_MAX;
  for (unsigned long long i = 0; i < 50; i++) {
  unsigned long long n = floors[i].size();
    if (n == 0) {
      continue;
    }
    Point Px[n] = {0,0};
    Point Py[n] = {0,0};
    for (unsigned long long j = 0; j < n; j++) {
        Px[j] = floors[i][j];
        Py[j] = floors[i][j];
    }
    qsort(Px, n,sizeof(Point), compareX);
    qsort(Py, n,sizeof(Point), compareY);
    float a = closestUtil(Px, Py, n);
    min_dist = (min_dist < a)? min_dist : a;
    //cout << a << endl;
  }
  cout << (unsigned long long)round((100*min_dist)) << endl;
}
