//https://open.kattis.com/problems/paint
// the smallest number of slats that go unpainted with an optimal selection of painters
// dp with binary search backtrace
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
#define pb push_back
#define mp make_pair

ll n, k;

ll find_idx(vector<pll> &slabs, ll maxlen) {
    ll low = 0, high = k-1, mid;
    if (slabs[0].second > maxlen) return -1;
    while (low < high) {
        if (high == low+1) {
            if (slabs[high].second <= maxlen) return high;
            else return low;
        }
        mid = (low + high) / 2;
        if (slabs[mid].second > maxlen) high = mid;
        else low = mid;
    }
    return mid;
}

int main() {
    cin >> n >> k;
    vector<pll> slabs;
    for (ll i=0; i<k; i++) {
        ll a, b; cin >> a >> b;
        slabs.pb(mp(a, b));
    }

    sort(slabs.begin(), slabs.end(), [](pll &p1, pll &p2){return (p1.second < p2.second) || (p1.second == p2.second && p1.first < p2.first);});
    
    ll dp[k], cnt[k];
    dp[0] = slabs[0].second - slabs[0].first + 1;
    cnt[0] = 1;
    for (ll i=1; i<k; i++) {
        ll val1 = dp[i-1];
        ll idx = find_idx(slabs, slabs[i].first-1);
        ll val2 = idx < 0 ? 0 : dp[idx];
        val2 += slabs[i].second - slabs[i].first + 1;
        if (val1 > val2) {
            dp[i] = val1;
            cnt[i] = cnt[i-1];
        } else if (val1 < val2) {
            dp[i] = val2;
            cnt[i] = idx < 0 ? 1 : cnt[idx] + 1;
        } else {
            dp[i] = val1;
            cnt[i] = max(cnt[i-1], (idx < 0 ? 1 : cnt[idx] + 1));
        }
    }

    cout << n - dp[k-1] << endl;
}
