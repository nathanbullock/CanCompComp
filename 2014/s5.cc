// 2014/s5 Canadian Computing Competition Solution

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Treat {
  int x;
  int y;
  int count;
  int distance;
  int old;
};

struct Edge {
  int p1;
  int p2;
  int distance;

  inline bool operator< (const Edge& x) const {
    return this->distance < x.distance;
  }
};

int main() {
  vector<Treat> treats;
  vector<Edge> edges;

  {
    int count;
    cin >> count;

    // 1st treat is the origin.
    treats.push_back({0,0});
    for (int i = 0; i < count; ++i) {
      int x, y;
      cin >> x >> y;
      treats.push_back({x,y});
    }

    // For every pair of treats, create an edge.
    for (int i = 0; i < count + 1; ++i) {
      for (int j = i + 1; j < count + 1; ++j) {
        int x = treats[j].x - treats[i].x;
        int y = treats[j].y - treats[i].y;
        edges.push_back({i, j, x*x + y*y});
      }
    }
  }

  // Sort the edges in ascending order.
  sort(edges.begin(), edges.end());

  for (auto &e1 : edges) {
    // Duplicating edges here, instead of above, makes the sort much cheaper.
    for (auto &e : {Edge{e1.p1, e1.p2, e1.distance},
                    Edge{e1.p2, e1.p1, e1.distance}}) {
      // Since we are working backwards, never start from the origin.
      if (e.p1 == 0) { continue; }

      // n1's count may have already been incremented, if so use old.
      Treat &n1 = treats[e.p1];
      int count = (e.distance == n1.distance) ? n1.old : n1.count;

      Treat &n2 = treats[e.p2];
      // Set old to the current count, so that if another edge starts from
      // this point but has the same distance, it can use the "old" value
      // instead of the new value that already used this distance.
      if (e.distance != n2.distance) {
        n2.old = n2.count;
        n2.distance = e.distance;
      }
      n2.count = max(count + 1, n2.count);
    }
  }

  cout << treats[0].count << endl;
}
