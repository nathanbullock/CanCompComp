// 2013/s5 Canadian Computing Competition Solution

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
}
