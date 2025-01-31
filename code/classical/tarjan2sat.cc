/*
 tarjan + 2sat
You inherited a haunted house. Its floor plan is an n-by-n square grid with l lamps in fixed
locations and no interior walls. Each lamp can either illuminate its row or its column, but not both
simultaneously. The illumination of each lamp extends by r squares in both directions, so a lamp
unobstructed by an exterior wall of the house can illuminate as many as 2r + 1 squares.

n, r and l (1 < n, r, l < 1,000).
ri and ci (1 < ri, ci < n), indicating that there is a lamp in row ri and column ci.

YES if it is possible to illuminate all lamps as stated above
*/

#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <stack>

using namespace std;
typedef pair<int, int> pii;

const int MAXN = 10005;
vector<int> g[MAXN];
int d[MAXN], low[MAXN], scc[MAXN];
bool stacked[MAXN];
int ticks, current_scc;
stack<int> s;

void tarjan(int u) {
	d[u] = low[u] = ticks++;
	s.push(u);
	stacked[u] = true;
	const vector<int> &out = g[u];
	for (int k = 0, m = (int)out.size(); k < m; k++) {
		const int &v = out[k];
		if (d[v] == -1) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (stacked[v]) {
			low[u] = min(low[u], low[v]);
		}
	}
	if (d[u] == low[u]) {
		int v;
		do {
			v = s.top();
			s.pop();
			stacked[v] = false;
			scc[v] = current_scc;
		} while (u != v);
		current_scc++;
	}
}

int n, r, l;
vector<pii> lamps;

int main() {
	cin >> n >> r >> l;
	for (int i = 1; i <= l; i++) {
		int x, y;
		cin >> x >> y;
		lamps.push_back(make_pair(x, y));
	}

	memset(d, -1, sizeof(d));

	for (int i = 0; i < l; i++) {
		int mr = lamps[i].first;
		for (int j = i + 1; j < l; j++) {
			if (mr == lamps[j].first && abs(lamps[i].second - lamps[j].second) <= 2 * r) {
				g[i].push_back(j + l);
				g[j].push_back(i + l);
			}
		}
	}

	for (int i = 0; i < l; i++) {
		int mc = lamps[i].second;
		for (int j = i + 1; j < l; j++) {
			if (mc == lamps[j].second && abs(lamps[i].first - lamps[j].first) <= 2 * r) {
				g[i + l].push_back(j);
				g[j + l].push_back(i);
			}
		}
	}

	for (int i = 0; i < l * 2; i++) {
		if (d[i] == -1) tarjan(i);
	}

	for (int i = 0; i < l; i++) {
		if (scc[i] == scc[i + l]) {
			cout << "0" << endl;
			return 0;
		}
	}

	cout << "1" << endl;
	return 0;
}