// 2014/s4 Canadian Computing Competition Solution

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
  int edge;
  bool start;
  int tint;
  int rectangle;

  inline bool operator< (const Edge& x) const {
    return this->edge < x.edge;
  }
};

int main() {
  int tint_threshold;

  vector<bool> rectangles;
  vector<Edge> x_edges;
  vector<Edge> y_edges;

  // Load the problem.
  {
    int count;
    cin >> count;
    cin >> tint_threshold;

    for (int i = 0; i < count; ++i) {
      int x1, x2, y1, y2, tint;
      cin >> x1 >> y1 >> x2 >> y2 >> tint;
      x_edges.push_back(Edge{x1, true, tint, i});
      x_edges.push_back(Edge{x2, false, tint, i});
      y_edges.push_back(Edge{y1, true, tint, i});
      y_edges.push_back(Edge{y2, false, tint, i});
    }

    rectangles.resize(count);
  }

  sort(x_edges.begin(), x_edges.end());
  sort(y_edges.begin(), y_edges.end());

  // Solve problem.
  uint64_t max_score = 0;

  // Scan through the X edges, keep track of total tint.
  int x_tint = 0;
  for (size_t i = 0; i + 1 < x_edges.size(); ++i) {
    auto &x1 = x_edges[i], &x2 = x_edges[i+1];
    x_tint += x1.start ? x1.tint : -x1.tint;
    rectangles[x1.rectangle] = x1.start;

    // If this is not an actual X slice or we don't have enough tint.
    if (x1.edge == x2.edge && x_tint < tint_threshold) {
      continue;
    }

    // Scan through the Y edges, keep track of tint levels.
    int y_tint = 0;
    for (size_t j = 0; j + 1 < y_edges.size(); ++j) {
      auto &y1 = y_edges[j], &y2 = y_edges[j+1];

      // If this rectrangle is in the current Y slice, count it.
      if (rectangles[y1.rectangle]) {
        y_tint += y1.start ? y1.tint : -y1.tint;
      }
      // Check if this is a rectangle that exceeds the tint threshold.
      if (y1.edge != y2.edge && y_tint >= tint_threshold) {
        max_score += (uint64_t)(x2.edge - x1.edge) * (y2.edge - y1.edge);
      }
    }
  }

  cout << max_score << endl;
}
