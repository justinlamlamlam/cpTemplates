#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
ll n;
vector< vector<ll> > adj, adjt;
vector<bool> used;
vector<ll> order, comp;
vector<bool> assignment;
void dfs1(ll v){
    used[v] = true;
    for(ll u : adj[v]){
        if(!used[u]){
            dfs1(u);
        }
    }
    order.pb(v);
}
void dfs2(ll v, ll cl){
    comp[v] = cl;
    for(ll u : adjt[v]){
        if(comp[u] == -1){
            dfs2(u, cl);
        }
    }
}
bool solve2sat(){
    order.clear();
    used.assign(n, false);
    for(ll i = 0;i<n;i++){
        if(!used[i]) dfs1(i);
    }
    comp.assign(n, -1);
    for(int i = 0,j = 0; i<n;i++){
        ll v = order[n - i - 1];
        if(comp[v] == -1) dfs2(v, j++);
    }
    assignment.assign(n/2, false);
    for(int i = 0;i<n;i+=2){
        if(comp[i] == comp[i+1]){
            return false;
        }
        assignment[i/2] = comp[i] > comp[i+1];
    }
    return true;
}
void add_disjunction(ll a, bool na, ll b, bool nb){
    a = 2*a ^ na;
    b = 2*b ^ nb;
    ll nega = a^1;
    ll negb = b^1;
    adj[nega].pb(b);
    adj[negb].pb(a);
    adjt[b].pb(nega);
    adjt[a].pb(negb);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    n = 3;
    adj.assign(n+n, vector<ll>(0));
    adjt.assign(n+n, vector<ll>(0));
    add_disjunction(0, false, 0, false);
    add_disjunction(0, true, 0, true);
    bool ans = solve2sat();
    cout<< (ans ? "yes" : "no")<<endl;
    return 0;
}