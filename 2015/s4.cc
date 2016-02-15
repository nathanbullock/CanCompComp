// 2015/s4 Canadian Computing Competition Solution

#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Route {
  int begin;
  int end;
  int time;
  int cost;

  // Sort based on which island the route begins from.
  inline bool operator< (const Route &rhs) const {
    return this->begin < rhs.begin;
  }
};

struct Visit {
  int island;
  int time;
  int cost;

  // Yes this is backwards, but we want a min-heap.
  inline bool operator< (const Visit &rhs) const {
    return this->time > rhs.time ||
         (this->time == rhs.time && this->cost > rhs.cost);
  }
};

int main() {
  int max_cost, goal;
  vector<Route> routes;
  vector<Visit> islands;
  priority_queue<Visit, vector<Visit>> visits;

  // Load problem.
  {
    cin >> max_cost;

    int num_islands;
    cin >> num_islands;

    int num_routes;
    cin >> num_routes;

    // Load each route from a to b and from b to a.
    for (int i = 0; i < num_routes; ++i) {
      Route r{};
      cin >> r.begin >> r.end >> r.time >> r.cost;
      routes.push_back(r);
      swap(r.begin, r.end);
      routes.push_back(r);
    }

    int start;
    cin >> start >> goal;

    sort(routes.begin(), routes.end());
    // Add 1 to the size so we can use 1 based index.
    islands.resize(num_islands + 1, {0, INT_MAX, INT_MAX});
    visits.push({start, 0, 0});
  }

  // Solve problem.
  while (!visits.empty()) {
    auto visit = visits.top();
    visits.pop();

    int island = visit.island;
    int cost = visit.cost;
    int time = visit.time;

    // We are at our goal.
    if (island == goal) {
      cout << time << endl;
      return 0;
    }

    /* If we have already seen this island with the same time or a cost
     * that is no greater, no need to do so again. */
    if (islands[island].time == time || islands[island].cost <= cost) {
      continue;
    }

    islands[island] = visit;

    // Find all the routes that begin with the current island and add the time
    // and cost of the next leg of the trip.
    auto iter = lower_bound(routes.begin(), routes.end(), Route{island});
    for (; iter != routes.end() && iter->begin == island; ++iter) {
      if (cost + iter->cost < max_cost) {
        Visit tmp_v{iter->end, time + iter->time, cost + iter->cost};
        visits.push(tmp_v);
      }
    }
  }
  cout << -1 << endl;
}
