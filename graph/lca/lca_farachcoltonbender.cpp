#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
ll n;
vector<vector<ll>> adj;

ll block_size, block_cnt;
vector<ll> first_visit;
vector<ll> euler_tour;
vector<ll> height;
vector<ll> log_2;
vector<vector<ll>> st;
vector<vector<vector<ll>>> blocks;
vector<ll> block_mask;

void dfs(ll v, ll p, ll h) {
    first_visit[v] = euler_tour.size();
    euler_tour.push_back(v);
    height[v] = h;

    for (ll u : adj[v]) {
        if (u == p)
            continue;
        dfs(u, v, h + 1);
        euler_tour.push_back(v);
    }
}

ll min_by_h(ll i, ll j) {
    return height[euler_tour[i]] < height[euler_tour[j]] ? i : j;
}

void precompute_lca(ll root) {
    // get euler tour & indices of first occurences
    first_visit.assign(n, -1);
    height.assign(n, 0);
    euler_tour.reserve(2 * n);
    dfs(root, -1, 0);

    // precompute all log values
    ll m = euler_tour.size();
    log_2.reserve(m + 1);
    log_2.push_back(-1);
    for (ll i = 1; i <= m; i++)
        log_2.push_back(log_2[i / 2] + 1);

    block_size = max((ll)1, log_2[m] / 2);
    block_cnt = (m + block_size - 1) / block_size;

    // precompute minimum of each block and build sparse table
    st.assign(block_cnt, vector<ll>(log_2[block_cnt] + 1));
    for (ll i = 0, j = 0, b = 0; i < m; i++, j++) {
        if (j == block_size)
            j = 0, b++;
        if (j == 0 || min_by_h(i, st[b][0]) == i)
            st[b][0] = i;
    }
    for (ll l = 1; l <= log_2[block_cnt]; l++) {
        for (ll i = 0; i < block_cnt; i++) {
            ll ni = i + (1 << (l - 1));
            if (ni >= block_cnt)
                st[i][l] = st[i][l-1];
            else
                st[i][l] = min_by_h(st[i][l-1], st[ni][l-1]);
        }
    }

    // precompute mask for each block
    block_mask.assign(block_cnt, 0);
    for (ll i = 0, j = 0, b = 0; i < m; i++, j++) {
        if (j == block_size)
            j = 0, b++;
        if (j > 0 && (i >= m || min_by_h(i - 1, i) == i - 1))
            block_mask[b] += 1 << (j - 1);
    }

    // precompute RMQ for each unique block
    ll possibilities = 1 << (block_size - 1);
    blocks.resize(possibilities);
    for (ll b = 0; b < block_cnt; b++) {
        ll mask = block_mask[b];
        if (!blocks[mask].empty())
            continue;
        blocks[mask].assign(block_size, vector<ll>(block_size));
        for (ll l = 0; l < block_size; l++) {
            blocks[mask][l][l] = l;
            for (ll r = l + 1; r < block_size; r++) {
                blocks[mask][l][r] = blocks[mask][l][r - 1];
                if (b * block_size + r < m)
                    blocks[mask][l][r] = min_by_h(b * block_size + blocks[mask][l][r], 
                            b * block_size + r) - b * block_size;
            }
        }
    }
}

ll lca_in_block(ll b, ll l, ll r) {
    return blocks[block_mask[b]][l][r] + b * block_size;
}

ll lca(ll v, ll u) {
    ll l = first_visit[v];
    ll r = first_visit[u];
    if (l > r)
        swap(l, r);
    ll bl = l / block_size;
    ll br = r / block_size;
    if (bl == br)
        return euler_tour[lca_in_block(bl, l % block_size, r % block_size)];
    ll ans1 = lca_in_block(bl, l % block_size, block_size - 1);
    ll ans2 = lca_in_block(br, 0, r % block_size);
    ll ans = min_by_h(ans1, ans2);
    if (bl + 1 < br) {
        ll l = log_2[br - bl - 1];
        ll ans3 = st[bl+1][l];
        ll ans4 = st[br - (1 << l)][l];
        ans = min_by_h(ans, min_by_h(ans3, ans4));
    }
    return euler_tour[ans];
}
void add_edge(ll u, ll v){
    adj[u].pb(v);
    adj[v].pb(u);
}
int main(){
    n = 5;
    adj.assign(n, vector<ll>(0));
    add_edge(0,1);
    add_edge(1,2);
    add_edge(2,3);
    add_edge(3,4);
    cout<<"asdf"<<endl;
    precompute_lca(2);
    cout<<lca(0,1)<<endl;
    cout<<lca(0,2)<<endl;
    cout<<lca(0,3)<<endl;
    cout<<lca(0,4)<<endl;
    cout<<lca(1,2)<<endl;
    cout<<lca(1,3)<<endl;
    cout<<lca(1,4)<<endl;
    cout<<lca(2,3)<<endl;
    cout<<lca(2,4)<<endl;
    cout<<lca(3,4)<<endl;
    return 0;
}