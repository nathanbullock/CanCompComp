// 2013/s4 Canadian Computing Competition Solution

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Breadth first search.
bool IsShorter(const vector<vector<int>> &comp, const int num_people,
               const int x, const int y) {
  // Once we have visited a position once, no need to do it again.
  vector<bool> visited(num_people);

  // Keep track of the next nodes we want to search from.
  vector<int> stack;

  stack.push_back(x);
  while (stack.size() > 0) {
    int t = stack.back();
    stack.pop_back();
    for (auto shorter : comp[t]) {
      if (shorter == y) {
        return true;
      }
      if (!visited[shorter]) {
        stack.push_back(shorter);
        visited[shorter] = true;
      }
    }
  }

  return false;
}

int main() {
  // Makes program three times faster. Most of the time is spent reading data.
  std::ios_base::sync_with_stdio(false);

  // Load problem.
  int num_people, num_comp;
  cin >> num_people >> num_comp;

  vector<vector<int>> comp(num_people + 1);
  for (int i = 0; i < num_comp; ++i) {
    int tall, sh;
    cin >> tall >> sh;
    comp[tall].push_back(sh);
  }

  int x, y;
  cin >> x >> y;

  // Solve problem.
  const char *answer = "unknown";
  if (IsShorter(comp, num_people, x, y)) {
    answer = "yes";
  } else if (IsShorter(comp, num_people, y, x)) {
    answer = "no";
  }
  cout << answer << endl;
}
