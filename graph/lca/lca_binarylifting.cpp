#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
struct node{
    bool visited=false;
    ll key;
    ll par;
    ll chi_cnt;
    vector<ll> chi;
};
node gra[200005];
vector< vector<ll> > up;
vector<ll> tin, tout;
ll timer;
ll n,l;
void dfs(int v, int p){
    tin[v]=++timer;
    up[v][0]=p;
    for(int i=1;i<=l;++i){
        up[v][i] = up[up[v][i-1]][i-1];
    }
    for(int i = 0;i<gra[v].chi_cnt;i++){
        if(gra[v].chi[i]!=p){
            dfs(gra[v].chi[i],v);
        }
    }
    tout[v] = ++timer;
}
bool is_ancestor(ll a, ll b){
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}
ll lca(ll a, ll b){
    if(is_ancestor(a,b)){
        return a;
    }
    if(is_ancestor(b,a)){
        return b;
    }
    for(int i = l; i>=0;i--){
        if(!is_ancestor(up[a][i],b)){
            a = up[a][i];
        }
    }
    return up[a][0];
}
void add_edge(ll n, ll s, ll t){
    gra[s].chi.pb(t);
    gra[s].chi_cnt++;
    gra[t].par = s;
}
void preprocess(ll root){
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n,vector<ll>(l+1));
    dfs(root, root);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //LCA: lowest common ancestor using binary lifting
    //both preprocess and query time worse than farach cholton and bender
    //Preprocess: O(nlogn)
    //Per query: O(logn)
    n = 5;
    add_edge(n,0,1);
    add_edge(n,1,2);
    add_edge(n,2,3);
    add_edge(n,1,4);
    preprocess(0);
    cout<<lca(2,3)<<endl;
    return 0;
}