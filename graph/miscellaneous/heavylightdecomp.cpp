#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
vector<ll> parent, depth, heavy, head, pos;
ll cur_pos;
ll dfs(ll v, vector< vector<ll> > const& adj){
    ll size = 1;
    ll max_c_size = 0;
    for(ll c : adj[v]){
        if(c != parent[v]){
            parent[c] = v, depth[c] = depth[v] + 1;
            ll c_size = dfs(c, adj);
            size += c_size;
            if(c_size > max_c_size){
                max_c_size = c_size, heavy[v] = c;
            }
        }
    }
    return size;
}

void decompose(ll v, ll h, vector< vector<ll> > const& adj){
    head[v] = h, pos[v] = cur_pos++;
    if(heavy[v] != -1){
        decompose(heavy[v], h, adj);
    }
    for(ll c : adj[v]){
        if(c != parent[v] && c != heavy[v]){
            decompose(c, c, adj);
        }
    }
}

void init(vector< vector<ll> > const& adj){
    ll n = adj.size();
    parent.assign(n, 0);
    depth.assign(n, 0);
    heavy.assign(n, -1);
    head.assign(n, 0);
    pos.assign(n, 0);
    cur_pos = 0;
    dfs(0, adj);
    decompose(0, 0, adj);
}

ll query(ll a, ll b){
    ll res = 0;
    for(; head[a] != head[b]; b = parent[head[b]]){
        if(depth[head[a]] > depth[head[b]]){
            swap(a, b);
        }
        //ll cur_heavy_path_max = segtreequery(pos[hea[b]], pos[b]);
        //res = max(res, cur_heavy_path_max);
    }
    if(depth[a] > depth[b]){
        swap(a, b);
    }
    //ll last_heavy_path_max = segtreequery(pos[a], pos[b]);
    //res = max(res, last_heavy_path_max);
    //return res;
    return 0;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n = 5;
    vector< vector<ll> > adj;
    adj.assign(n, vector<ll>(0));
    adj[0].pb(1);
    adj[1].pb(2);
    adj[2].pb(3);
    adj[3].pb(4);
    init(adj);
    return 0;
}