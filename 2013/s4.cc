// 2013/s4 Canadian Computing Competition Solution

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Comp {
  int tall;
  int sh;

  inline bool operator< (const Comp& x) const {
    return this->tall < x.tall;
  }
};

bool IsShorter(const vector<Comp> &comp, const int x, const int y,
               const int num_people) {
  vector<bool> visited(num_people);
  vector<int> stack;

  stack.push_back(x);
  while (stack.size() > 0) {
    int t = stack.back();
    stack.pop_back();
    auto iter = lower_bound(comp.begin(), comp.end(), Comp{t, 0});
    for (; iter != comp.end() && iter->tall == t; ++iter) {
      if (iter->sh == y) {
        return true;
      }
      if (!visited[iter->sh]) {
        stack.push_back(iter->sh);
        visited[iter->sh] = true;
      }
    }
  }

  return false;
}

int main() {
  // Load problem.
  int num_people, num_comp;
  cin >> num_people >> num_comp;

  vector<vector<int>> comp(num_people);
  for (auto &c : comp) {
    int tall, sh;
    cin >> tall >> sh;
    comp[tall].push_back(sh);
  }

  // This is the majority of the cost... Maybe we shouldn't sort?
  sort(comp.begin(), comp.end());

  int x, y;
  cin >> x >> y;

  // Solve problem.
  const char *answer = "unknown";
  if (IsShorter(comp, x, y, num_people)) {
    answer = "yes";
  } else if (IsShorter(comp, y, x, num_people)) {
    answer = "no";
  }
  cout << answer << endl;
}
