#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
ll n;
vector< vector<ll> > adj;
vector<bool> vis;
vector<ll> ans;
void dfs(ll v){
    vis[v] = true;
    for(ll u : adj[v]){
        if(!vis[u]) dfs(u);
    }
    ans.pb(v);
}
void topsort(){
    vis.assign(n, false);
    ans.clear();
    for(int i = 0;i<n;i++){
        if(!vis[i]) dfs(i);
    }
    reverse(ans.begin(), ans.end());
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    n = 5;
    adj.assign(n,vector<ll>(0));
    adj[0].pb(1);
    adj[1].pb(2);
    adj[2].pb(3);
    adj[3].pb(4);
    adj[0].pb(2);
    adj[0].pb(4);
    topsort();
    for(int i : ans) cout<<i<<' ';
    cout<<endl;
    return 0;
}