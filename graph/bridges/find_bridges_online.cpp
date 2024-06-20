#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
ll n;
vector<ll> par, dsu_2ecc, dsu_cc, dsu_cc_size;
ll bridges;
ll lca_iteration;
vector<ll> last_vis;
void init(){
    par.resize(n);
    dsu_2ecc.resize(n);
    dsu_cc.resize(n);
    dsu_cc_size.resize(n);
    lca_iteration=0;
    last_vis.assign(n,0);
    for(int i=0;i<n;i++){
        dsu_2ecc[i]=i;
        dsu_cc[i]=i;
        dsu_cc_size[i]=1;
        par[i]=-1;
    }
    bridges=0;
}
ll find_2ecc(ll v){
    if(v==-1){
        return -1;
    }
    if(dsu_2ecc[v]==v){
        return v;
    }
    return dsu_2ecc[v] = find_2ecc(dsu_2ecc[v]);
}
ll find_cc(ll v){
    v = find_2ecc(v);
    if(dsu_cc[v]==v){
        return v;
    }
    return dsu_cc[v] = find_cc(dsu_cc[v]);
}
void make_root(ll v){
    v = find_2ecc(v);
    ll root = v;
    ll child = -1;
    while(v!=-1){
        ll p = find_2ecc(par[v]);
        par[v] = child;
        dsu_cc[v] = root;
        child = v;
        v = p;
    }
    dsu_cc_size[root] = dsu_cc_size[child];
}
void merge_path(ll a, ll b){
    lca_iteration++;
    vector<ll> patha, pathb;
    ll lca = -1;
    while(lca == -1){
        if(a != -1){
            a = find_2ecc(a);
            patha.pb(a);
            if(last_vis[a] == lca_iteration){
                lca = a;
                break;
            }
            last_vis[a] = lca_iteration;
            a = par[a];
        }
        if(b != -1){
            b = find_2ecc(b);
            pathb.pb(b);
            if(last_vis[b] == lca_iteration){
                lca = b;
                break;
            }
            last_vis[b] = lca_iteration;
            b = par[b];
        }
    }
    for(int i = 0;i<patha.size();i++){
            ll v = patha[i];
            dsu_2ecc[v] = lca;
            if(v==lca){
                break;
            }
            bridges--;
        }
        for(int i = 0;i<pathb.size();i++){
            ll v = pathb[i];
            dsu_2ecc[v] = lca;
            if(v==lca){
                break;
            }
            bridges--;
        }
}
void add_edge(ll a, ll b){
    a = find_2ecc(a);
    b = find_2ecc(b);
    if(a==b) return;
    ll ca = find_cc(a);
    ll cb = find_cc(b);
    if(ca != cb){
        bridges++;
        if(dsu_cc_size[a] > dsu_cc_size[b]){
            swap(a,b);
            swap(ca,cb);
        }
        make_root(a);
        par[a] = dsu_cc[a] = b;
        dsu_cc_size[cb] += dsu_cc_size[a];
    }
    else{
        merge_path(a,b);
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //find bridges online (edge when removed makes the graph unconnected)
    //graph is UNdirected
    //DSU used
    //Time complexity: O(vlogv+elogv)
    n = 6;
    init();
    add_edge(0,1);
    add_edge(1,2);
    add_edge(2,3);
    add_edge(3,4);
    add_edge(4,0);
    add_edge(0,5);
    cout<<bridges<<endl;
    add_edge(5,1);
    cout<<bridges<<endl;
    return 0;
}