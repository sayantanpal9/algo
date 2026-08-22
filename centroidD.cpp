class centroidD
{
    vector<ll> dead;
    vector<vector<ll>> adjj;
    vector<vector<bool>> vis;
    ll n;
    ll recursion(ll a, vector<vector<ll>> &adjj, vector<ll> &dp, vector<bool> &vis)
    {
        ll k = 1;
        vis[a] = 1;
        for (auto i : adjj[a])
        {
            if (vis[i] == 0 && dead[i] == 0)
            {
                k += recursion(i, adjj, dp, vis);
            }
        }
        return dp[a] = k;
    }
    void dothis(ll a, vector<vector<ll>> &adjj, vector<ll> &dp, ll level, vector<ll> &levels)
    {
        bool p = 0;
        if (adjj[a].empty())
        {
            levels[a] = level;
            return;
        }
        while (!p)
        {
            bool p1 = 1;
            ll ind;
            for (auto i : adjj[a])
            {
                if (dead[i])
                {
                    continue;
                }
                if (dp[i] > dp[a] / 2)
                {
                    ind = i;
                    p1 = 0;
                }
            }
            if (p1)
            {
                p = 1;
                levels[a] = level;
                dead[a]++;
                for (auto i : adjj[a])
                {
                    if (dead[i])
                    {
                        continue;
                    }
                    recursion(i, adjj, dp, vis[level]);
                    dothis(i, adjj, dp, level + 1, levels);
                }
            }
            else
            {
                ll k = dp[ind];
                dp[ind] = dp[a];
                dp[a] = dp[ind] - k;
                a = ind;
            }
        }
    }

public:
    vector<ll> levels;
    centroidD(vector<vector<ll>> &adj, ll num)
    {
        n = num;
        ll logma = log2(n) + 1;
        adjj = vector<vector<ll>>(n);
        dead = vector<ll>(n);
        levels = vector<ll>(n);
        vis = vector<vector<bool>>(logma, vector<bool>(n, 0));
        for (ll i = 0; i < n; i++)
        {
            for (auto j : adj[i])
            {
                adjj[i].push_back(j);
            }
        }
        vector<ll> dp(n, -1);
        vector<bool> vis(n, 0);
        recursion(0, adjj, dp, vis);
        dothis(0, adjj, dp, 0, levels);
    }
};
