#include <bits/stdc++.h>
using namespace std;
#define ll long long

void upd(vector<ll>& st, ll i, ll s, ll a, ll b, ll v) {
    if (b - a == 1) {
        st[s] = v;
        return;
    }
    ll m = (a + b) / 2;
    if (i < m) {
        upd(st, i, 2 * s + 1, a, m, v);
    } else {
        upd(st, i, 2 * s + 2, m, b, v);
    }
    st[s] = st[2 * s + 1] + st[2 * s + 2];
}

ll sum(vector<ll>& st, ll a, ll b, ll i, ll j, ll s) {
    if (a <= i && b >= j) {
        return st[s];
    }
    ll m = (i + j) / 2;
    if (b <= m) {
        return sum(st, a, b, i, m, 2 * s + 1);
    } else if (a >= m) {
        return sum(st, a, b, m, j, 2 * s + 2);
    } else {
        ll s1 = sum(st, a, m, i, m, 2 * s + 1);
        ll s2 = sum(st, m, b, m, j, 2 * s + 2);
        return s1 + s2;
    }
}
