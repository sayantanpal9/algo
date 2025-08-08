ll get(ll a, vector<ll>& par, vector<ll>& size) {
    return par[a] = (par[a] == a ? a : get(par[a], par, size));
}

void uni(ll a, ll b, vector<ll>& par, vector<ll>& size) {
    a = get(a, par, size);
    b = get(b, par, size);
    if (a == b) return;
    if (size[a] == size[b]) size[a]++;
    if (size[a] > size[b]) par[b] = a;
    else par[a] = b;
}
