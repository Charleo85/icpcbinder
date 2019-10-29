// https://open.kattis.com/problems/rainbowroads
/*
You are given a tree with n nodes (stations), conveniently numbered from 1 to n. 
Each edge in this tree has one of n colors. 
A path in this tree is called a rainbow if all adjacent edges in the path have different colors. 
Also, a node is called good if every simple path with that node as one of its endpoints is a rainbow path. 
(A simple path is a path that does not repeat any vertex or edge.)

Find all the good nodes in the given tree.
*/
#include <iostream>
#include <map>
#include <vector>
#include <cstdio>

using namespace std;

map<int, vector<int> > adj[50005];
int last[50005];
bool locked[50005];

void mark(int src, int dst) {
  if (locked[dst]) return;
  if (last[dst] == 0) {
    last[dst] = src;
    for (auto entry : adj[dst]) {
      for (auto next : entry.second) {
        if (next != src) mark(dst, next);
      }
    }
  } else if (last[dst] != src) {
    mark(dst, last[dst]);
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    adj[a][c].push_back(b);
    adj[b][c].push_back(a);
  }

  for (int i = 1; i <= n; i++) {
    if (locked[i]) continue;
    for (auto entry : adj[i]) {
      if (entry.second.size() > 1) {
        for (auto next : entry.second) mark(i, next);
      }
    }
  }

  int count = 0;
  for (int i = 1; i <= n; i++) {
    if (last[i] == 0) count++;
  }
  cout << count << endl;
  for (int i = 1; i <= n; i++) {
    if (last[i] == 0) cout << i << endl;
  }
}

