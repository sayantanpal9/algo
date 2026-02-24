#include <bits/stdc++.h>
using namespace std;
// operations --> apply xor with x on segment [l,r-1] and get sum of segment [l,r-1], important lazypropagation trick
#define ll long long int
#define ull unsigned long long int
#define sort(a) sort(a.begin(),a.end())
#define printv(a) for(auto v:a) cout<<v<<" "
#define MOD 1e9+7
#define vecll(a,aa) vector<ll>aa(a)
#define vecll2(a,aa,v) vector<ll>aa(a,v)
#define pb push_back
#define fir first
#define sec second
#define endl '\n'
#define yes cout<<"YES"<<endl
#define no cout<<"NO"<<endl
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

ll binpow(ll a,ll b,ll m=MOD){
    if(b==0){
        return 1%m;
    }
    if(b%2==1){
        return (a*binpow((a*a)%m,b/2))%m;
    }
    else{
        return (binpow((a*a)%m,b/2))%m;
    }
}



void upd(vector<ll>& st,vector<ll>& st2, ll i, ll s, ll a, ll b, ll v) {
    if(2*s+2<st.size()){
        if(st2[s]%2!=st2[2*s+1]%2){
            st[2 * s + 1] = (b-a) / 2 - st[2 * s + 1];
            st2[2 * s + 1] --;
            if(2*(2*s+1)+2<st.size()){
                st2[2 * (2 * s + 1) + 2]++;
                st2[2 * (2 * s + 1) + 1]++;
            }
            
        }
        if(st2[s]%2!=st2[2*s+2]%2){
            st[2 * s + 2] = (b-a) / 2 - st[2 * s + 2];
            // st2[2 * s + 2] ++;
            st2[2 * s + 2] --;
            if(2*(2*s+2)+2<st.size()){
                st2[2 * (2 * s + 2) + 2]++;
                st2[2 * (2 * s + 2) + 1]++;
            }
        }
    }
    if (b - a == 1) {
        st[s] = v;
        return;
    }
    ll m = (a + b) / 2;
    if (i < m) {
        upd(st,st2, i, 2 * s + 1, a, m, v);
    } else {
        upd(st,st2, i, 2 * s + 2, m, b, v);
    }
    st[s] = st[2 * s + 1] + st[2 * s + 2];
}

void upd2(vector<ll>& st,vector<ll>& st2, ll a, ll b, ll i, ll j, ll s) {
    if(2*s+2<st.size()){
        if(st2[s]%2!=st2[2*s+1]%2){
            st[2 * s + 1] = (j - i) / 2 - st[2 * s + 1];
            st2[2 * s + 1] --;
            if(2*(2*s+1)+2<st.size()){
                st2[2 * (2 * s + 1) + 2]++;
                st2[2 * (2 * s + 1) + 1]++;
            }
            
        }
        if(st2[s]%2!=st2[2*s+2]%2){
            st[2 * s + 2] = (j - i) / 2 - st[2 * s + 2];
            // st2[2 * s + 2] ++;
            st2[2 * s + 2] --;
            if(2*(2*s+2)+2<st.size()){
                st2[2 * (2 * s + 2) + 2]++;
                st2[2 * (2 * s + 2) + 1]++;
            }
        }
    }
    if (a <= i && b >= j) {
        st[s] = (j - i) - st[s];
        if(2*s+2<st.size()){
            st2[2 * s + 1]++;
            st2[2 * s + 2]++;
        }
        return;
    }
    // st2[s]++;
    ll m = (i + j) / 2;
    if (b <= m) {
        upd2(st,st2, a, b, i, m, 2 * s + 1);
    } else if (a >= m) {
        upd2(st,st2, a, b, m, j, 2 * s + 2);
    } else {
        upd2(st,st2, a, m, i, m, 2 * s + 1);
        upd2(st,st2, m, b, m, j, 2 * s + 2);
        
    }
    st[s] = st[2 * s+1] + st[2 * s + 2];
}

ll sum(vector<ll>& st,vector<ll>& st2, ll a, ll b, ll i, ll j, ll s) {
    if(2*s+2<st.size()){
        if(st2[s]%2!=st2[2*s+1]%2){
            st[2 * s + 1] = (j - i) / 2 - st[2 * s + 1];
            st2[2 * s + 1] --;
            if(2*(2*s+1)+2<st.size()){
                st2[2 * (2 * s + 1) + 2]++;
                st2[2 * (2 * s + 1) + 1]++;
            }
            
        }
        if(st2[s]%2!=st2[2*s+2]%2){
            st[2 * s + 2] = (j - i) / 2 - st[2 * s + 2];
            // st2[2 * s + 2] ++;
            st2[2 * s + 2] --;
            if(2*(2*s+2)+2<st.size()){
                st2[2 * (2 * s + 2) + 2]++;
                st2[2 * (2 * s + 2) + 1]++;
            }
        }
    }
    if (a <= i && b >= j) {
        return st[s];
    }
    ll m = (i + j) / 2;
    if (b <= m) {
        return sum(st,st2, a, b, i, m, 2 * s + 1);
    } else if (a >= m) {
        return sum(st,st2, a, b, m, j, 2 * s + 2);
    } else {
        ll s1 = sum(st,st2, a, m, i, m, 2 * s + 1);
        ll s2 = sum(st,st2, m, b, m, j, 2 * s + 2);
        return s1 + s2;
    }

}

int main(){
    fast;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ll t=1;
    // cin>>t;
    while(t--){
        ll n;
        cin>>n;
        vector<ll> op(n);
        ll s = 1;
        while(s<n)
            s *= 2;
        vector<vector<ll>> seg(33, vector<ll>(2 * s, 0));
        vector<vector<ll>> seg2(33, vector<ll>(2 * s, 0));
        for (ll i = 0;i<n;i++){
            cin >> op[i];
            for (ll j = 0; j < 31;j++){
                if(op[i]&(1<<j)){
                    upd(seg[j],seg2[j], i, 0, 0, s, 1);
                }
            }
        }
        ll q;
        cin >> q;
        while(q--){
            ll op;
            cin >> op;
            if(op==1){
                ll l, r;
                cin >> l >> r;
                ll sums = 0;
                for (ll i = 0; i < 31;i++){
                    ll ss = sum(seg[i], seg2[i], l-1, r, 0, s, 0);
                    sums += (ss * (1 << i));
                }
                cout << sums << endl;
            }
            else{
                ll l, r, x;
                cin >> l >> r >> x;
                // cout << x << " ";
                for (ll i = 0; i < 31;i++){
                    if(x&(1<<i)){
                        upd2(seg[i], seg2[i], l-1 , r, 0, s, 0);
                        // cout << (1 << i) << " ";
                    }
                }
            }
        }
    }
    return 0;
}
