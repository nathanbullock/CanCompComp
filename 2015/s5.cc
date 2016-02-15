// 2015/s5 Canadian Computing Competition Solution
//
// Dynamic programming solution.
//
// One observation. The order of the inserted pies doesn't matter, only if
// they are counted or not. As a result if we sort the pies we can take the
// pies we are going to count from the top and the others from the bottom.
//
// First look at the problem without inserting pies, we can define two values
// for any position, Include (where the last pie isn't counted) and Exclude
// (where the last pie is counted). The value of any position can be built up
// based on the values of the previous positions.
//
// Include(n) = max(
//   Exclude(n-1) + Value(n))
//
// Exclude(n) = max(
//   Include(n-1),
//   Exclude(n-1))
//
// Now we can define two more variables, m, for the number of pies we inserted
// and counted and, M, for the number of pies we inserted but did not count.
//
// Include(n, m, M) = max(
//   Exclude(n, m-1, M) + Value(m),
//   Exclude(n-1, m, M) + Value(n))
//
// Exclude(n, m, M) = max(
//   Exclude(n, m, M-1),
//   Exclude(n-1, m, M),
//   Include(n, m, M-1),
//   Include(n-1, m, M))
//
// The general idea for this solution came from Daniel Whitney, Newmarket High
// School, my improvements make the solution simpler and faster.

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct IncExc {
  int include;
  int exclude;
};

int main() {
  int length;

  cin >> length;
  vector<int> pies(length);
  for (int i = 0; i < length; i++) {
    cin >> pies[i];
  }

  cin >> length;
  vector<int> alternates(length);
  for (int i = 0; i < length; i++) {
    cin >> alternates[i];
  }
  sort(alternates.rbegin(), alternates.rend());

  const int N = pies.size();
  const int P = alternates.size();

  // Values from the previous step.
  vector<vector<IncExc>> pre(P+1, vector<IncExc>(P+1));

  // Values we are calculating in the current step.
  vector<vector<IncExc>> curr(P+1, vector<IncExc>(P+1));

  for (int p = 0; p < N+P; ++p) {
    swap(pre, curr);
    for (int m = 0; m < P+1; ++m) {
      for (int M = 0; M < P+1-m; ++M) {
        const int n = p - m - M;

        if (n < 0 || n >= N) {
          continue;
        }

        // Calculate Include(n, m, M)
        int v = 0;
        v = max(v, pre[m][M].exclude + pies[n]);
        if (m > 0) {
          v = max(v, pre[m-1][M].exclude + alternates[m-1]);
        }
        curr[m][M].include = v;

        // Calculate Exclude(n, m, M)
        v = 0;
        v = max(v, pre[m][M].exclude);
        v = max(v, pre[m][M].include);
        if (M > 0) {
          v = max(v, pre[m][M-1].include);
          v = max(v, pre[m][M-1].exclude);
        }
        curr[m][M].exclude = v;
      }
    }
  }

  // Take the max of the various valid combinations of how we could include
  // or exclude the pies from our alternate pile.
  int max_score = 0;
  for (int i = 0; i < P+1; i++) {
    max_score = max(max_score, curr[i][P-i].include);
    max_score = max(max_score, curr[i][P-i].exclude);
  }

  cout << max_score << endl;
}
