class hld{
    vector<vector<pair<ll,ll>>> adj;
    ll n;
    void find(ll a, vector<ll> &par, vector<vector<pair<ll, ll>>> &adj, vector<ll> &stresz, vector<vector<ll>> &ref, vector<ll> &tem)
    {
        if(adj[a].size()==1&&a!=0){
            ref.pb(tem);
            return;

        }
        ll ind, cnt = 0;
        for (auto i:adj[a]){
            if(i.first!=par[a]&&cnt<stresz[i.first]){
                cnt = stresz[i.first];
                ind = i.first;
            }
        }
        tem.push_back(ind);
        find(ind, par, adj, stresz, ref, tem);
        for (auto i:adj[a]){
            if(i.first!=par[a]&&i.first!=ind){
                vector<ll> t;
                t.pb(i.first);
                find(i.first, par, adj, stresz, ref, t);
            }
        }
    }

    ll find1(ll a, vector<ll>&par, vector<vector<pair<ll,ll>>>&adj,vector<ll>&stresz){
        for(auto i :adj[a]){
            if(par[a]!=i.first){
                stresz[a] += find1(i.first, par, adj, stresz);
            }
        }
        return stresz[a];
    }
    
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
        if(a>=b){
            return 0ll;
        }
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

    public:
        vector<vector<ll>> segs;
        ll segnums;
        vector<ll> in1, in2;
        vector<vector<ll>> ref;
        vector<ll> weights;
        vector<ll> par;
        hld(vector<vector<pair<ll,ll>>> &adj, ll n) : adj(adj), n(n)
        {
            par=vector<ll>(n,-1);
            weights =in2=in1= vector<ll>(n);
            queue<ll> q;
            par[0] = 0;
            q.push(0);
            while(!q.empty()){
                auto a = q.front();
                q.pop();
                for (auto i:adj[a]){
                    if(par[i.first]==-1){
                        weights[i.first] = i.second;
                        par[i.first] = a;
                        q.push(i.first);
                    }
                }
            }
            vector<vector<ll>> temp;
            ref = segs = temp;
            vector<ll> stresz(n, 1);
            find1(0, par, adj, stresz);
            vector<ll> tem(1, 0);
            find(0, par, adj, stresz, ref, tem);
            segnums = ref.size();
            for (ll i = 0; i < segnums;i++){
                ll cc = ref[i].size();
                ll s = 1;
                while(s<cc){
                    s *= 2;
                }
                vector<ll> seg(2 * s);
                for (ll j = 0; j < ref[i].size();j++){
                    in1[ref[i][j]] = i;
                    in2[ref[i][j]] = j;
                    upd(seg, j, 0, 0, s, weights[ref[i][j]]);
                }
                segs.pb(seg);
            }
        }
        void editw(ll v, ll w){
            ll s = 1;
            weights[v] = w;
            while(s<ref[in1[v]].size()){
                s *= 2;
            }
            upd(segs[in1[v]], in2[v], 0, 0, s, w);
        }
        ll finddist(ll pa, ll v){
            if(pa==v){
                return 0ll;
            }
            if(par[v]==pa){
                return weights[v];
            }
            if(in1[pa]==in1[v]){
                ll s = 1;
                while(s<ref[in1[v]].size()){
                    s *= 2;
                }
                return sum(segs[in1[v]], in2[pa] + 1, in2[v]+1, 0, s, 0);
            }
            else{
                ll s = 1;
                while(s<ref[in1[v]].size()){
                    s *= 2;
                }
                return finddist(pa, par[ref[in1[v]][0]]) + sum(segs[in1[v]], 0, in2[v]+1, 0, s, 0);
            }
        }
}; // note: i have assumed i can implement lca all by myself since it is easy to implement, and also not handled for edge cases like n = 1
