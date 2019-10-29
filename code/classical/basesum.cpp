/**
 *  given n, a, and b, find the smallest m>n such that the sum of the digits of m in
base a is the same as the sum of digits of m in base b.
 */

inline ll ceil_div(ll a, ll b) { return b ? ((a/b) + ((a%b) != 0)) : INF; }
inline ll add(ll a, ll b) { return (a >= INF - b) ? INF : (a + b); }
inline ll mul(ll a, ll b) { return b ? (a >= ceil_div(INF,b) ? INF : a*b) : 0; }

ll iters;

void convert(ll N, int BASE, int ans[MAXD]) {
  memset(ans,0,sizeof(ans[0])*MAXD); iters += MAXD;
  int i = 0;
  while(N) ans[i++] = (N%BASE), N /= BASE, ++iters;
  assert(i<=MAXD);
}

int tmp3[MAXD];
string convert_to_string(ll N, int BASE) {
  convert(N,BASE,tmp3);
  string ans;

  bool non_zero = false;
  FORB(i,MAXD-1,0) {
    ++iters;
    if (tmp3[i] != 0) non_zero = true;
    if (non_zero) ans += (tmp3[i] < 10 ? '0' + tmp3[i] : 'A' + tmp3[i] - 10);
  }

  if (ans.empty()) return "0";
  return ans;
}

// find the next number > N with sum K (in given BASE)
int tmp[MAXD];
ll next(ll N, int BASE, int K) {
  convert(N,BASE,tmp);

  int sum = 0;
  FOR(i,MAXD) sum += tmp[i], ++iters;

  bool found = false;
  FOR(i,MAXD) {
    ++iters;
    if (tmp[i] < BASE-1 && sum + 1 <= K && sum - tmp[i] + (BASE-1)*(i+1) >= K) {
      // we can (and should) bump up here
      K -= sum + 1;
      tmp[i]++;

      FOR(j,MAXD) {
        ++iters;
        assert(K>=0);
        if (!K) break;
        assert(j <= i);
        assert(tmp[j] <= BASE-1);
        int add = min(K, BASE-1-tmp[j]);
        tmp[j] += add;
        K -= add;
      }

      found = true;
      break;
    } else {
      // continue step
      sum -= tmp[i];
      tmp[i] = 0;
    }
  }

  if (!found) return INF;

  ll ans = 0;
  FORB(i,MAXD-1,0) {
    ++iters;
    ans = mul(ans, BASE);
    ans = add(ans, tmp[i]);
  }

  return ans;
}

int tmp2[MAXD];
ll digit_sum(ll N, int BASE) {
  convert(N,BASE,tmp2);
  int ans = 0;
  FOR(i,MAXD) ans += tmp2[i];
  return ans;
}

ll points[2*MAXS];
ll nxtA[MAXS];
ll nxtB[MAXS];

int main() {
  ll N; int A,B;
  cin >> N >> A >> B;
  N++;

  iters = 0;

  while(true) {
    ll x = digit_sum(N,A);
    ll y = digit_sum(N,B);

    if (x==y) break;

    ++iters;

    // find all points where the ranges change
    FOR(v,MAXS) {
      if (nxtA[v] > N) continue;
      nxtA[v] = next(N,A,v);
      assert(nxtA[v] > N);
    }

    FOR(v,MAXS) {
      if (nxtB[v] > N) continue;
      nxtB[v] = next(N,B,v);
      assert(nxtB[v] > N);
    }

    int K = 0;
    FOR(v,MAXS) {
      if (nxtA[v] >= INF) continue;
      points[K++] = nxtA[v];
    }

    FOR(v,MAXS) {
      if (nxtB[v] >= INF) continue;
      points[K++] = nxtB[v];
    }

    sort(points, points+K);
    K = unique(points,points+K) - points;

    // find the next point where the ranges overlap
    ll low_x = x, high_x = x;
    ll low_y = y, high_y = y;

    ll p;
    FOR(z,K) {
      p = points[z];
      ll x = digit_sum(p,A);
      low_x = min(low_x, x);
      high_x = max(high_x, x);

      ll y = digit_sum(p,B);
      low_y = min(low_y, y);
      high_y = max(high_y, y);

      if (high_x >= low_y && low_x <= high_y) {
        // they now overlap
        N = p;
        break;
      }
    }
  }

  cout << N << /*" " << convert_to_string(N,A) << " " << convert_to_string(N,B) <<*/ endl;
}










