// find smallest possible substring S'+S'+ +S' = S cabcabca abc
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef uint64_t ull;

ull prime = (ull) (1e9+7);

ull hashstr(string s) {
    ull hash = 0;
    ull expo = 1;
    for (int k=0; k<s.length(); k++) {
        hash = (hash + (ull)(s[k] - 'a'+1) * expo) % prime;
        expo = (expo * 32) % prime;
    }
    return hash;
}

int main() {
    int n; cin >> n;
    string s; cin >> s;

    vector<ull> lhash(n), rhash(n), expos(n);
    ull hash = 0;
    ull expo = 1;
    for (int k=0; k<n; k++) {
        hash = (hash + (ull)(s[k] - 'a'+1) * expo) % prime;
        lhash[k] = hash;
        expos[k] = expo;
        expo = (expo * 32) % prime;
    }
    hash = 0;
    for (int k=n-1; k>=0; k--) {
        hash = (hash * 32 + (ull)(s[k] - 'a'+1)) % prime;
        rhash[k] = hash;
    }
    int l;
    for (l=1; l<n; l++) if (rhash[l] == lhash[n-l-1]) break;
    cout << l << endl;
}
