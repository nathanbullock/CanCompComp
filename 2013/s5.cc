// 2013/s5

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int target;
  cin >> target;

  int total_cost = 0;
  while (target > 1) {
    int cost = target - 1;
    int factor = 1;
    for (int j = 2; j * j <= target; ++j) {
      if (target % j == 0) {
        cost = j - 1;
        factor = target / j;
        break;
      }
    }
    target -= factor;
    total_cost += cost;
  }
  cout << total_cost << endl;


  /*
  vector<int> x(target + 5);
  x[2] = 1;

  for (int i = 2; i < target; ++i) {
    for (int j = 1; j * j <= i; ++j) {
      if (i % j == 0) {
        int k = i / j;
        if (i + j <= target) {
          x[i + j] = x[i + j] ? min(x[i] + k, x[i + j]) : x[i] + k;
        }
        if (i + k <= target) {
          x[i + k] = x[i + k] ? min(x[i] + j, x[i + k]) : x[i] + j;
        }
      }
    }
  }
  cout << x[target] << endl;
  */
}
