Edge chasing (2 sample inputs in the end):

#include <bits/stdc++.h>
using namespace std;
bool deadlock(int probeInit, int current, vector<vector<bool>> &depends,
              vector<bool> &covered, vector<int> &homeSites) {
  // probeInit == current is a redundant condition because if current/probeInit
  // is covered => Deadlock exits
  if (covered[current]) {
    return true;
  }
  covered[current] = true;
  for (int i = 0; i < depends[current].size(); i++) {
    if (!depends[current][i])
      continue;
    if (i == current)
      return true;
    if (homeSites[current] != homeSites[i])
      cout << "Probe is sent: (" << probeInit + 1 << "," << current + 1 << ","
           << i + 1 << ")" << endl;
    return deadlock(probeInit, i, depends, covered, homeSites);
  }
  return false;
}
int main() {
  int sites;
  vector<int> homeSites;
  vector<bool> covered;
  vector<vector<bool>> depends;
  cout << "Enter number of sites: ";
  cin >> sites;
  cout << endl;
  int x, count = 0;
  for (int i = 0; i < sites; i++) {
    cout << "Enter number of sites in site " << i + 1 << ": ";
    cin >> x;
    for (int j = 0; j < x; j++) {
      homeSites.push_back(i);
    }
    count += x;
  }
  depends.resize(count, vector<bool>(count, false));
  covered.resize(count, false);
  while (1) {
    int a, b;
    cout << "Enter the Dependencies(-1 to stop):" << endl;
    cin >> a;
    if (a == -1)
      break;
    cin >> b;
    depends[a - 1][b - 1] = true;
  }
  cout << "Enter node to start probe: ";
  int probeInit;
  cin >> probeInit;
  probeInit--;
  if (deadlock(probeInit, probeInit, depends, covered, homeSites))
    cout << "A Deadlock exists" << endl;
  // Detects atleast one deadlock (depends on order)
  else
    cout << "No Deadlock doesn't exist" << endl;
  return 0;
}
/*
2
3 2
1 2
2 3
3 4
4 5
-1
1
*/
/*
2
3 2
1 2
2 3
3 4
2 4
4 5
5 1
-1
1
*/
