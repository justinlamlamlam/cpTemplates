#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define INF LLONG_MAX
ll const& MAXN = 200005;
ll n;
vector<ll> t;
vector<ll> g;
vector<ll> lazy;
void push(ll v){
    t[v*2] += lazy[v];
    lazy[v*2] += lazy[v];
    t[v*2+1] += lazy[v];
    lazy[v*2+1] += lazy[v];
    lazy[v] = 0;
}
void buildsegtree(ll v, ll tl, ll tr){
    if(tl == tr) t[v] = g[tl];
    else{
        ll tm = (tl + tr) / 2;
        buildsegtree(v*2, tl, tm);
        buildsegtree(v*2 + 1, tm+1, tr);
        t[v] = max(t[v*2], t[v*2+1]);
    }
}
void updatesegtree(ll v, ll tl, ll tr, ll l, ll r, ll add){
    if(l > r) return;
    if(l == tl && r == tr){
        t[v] += add;
        lazy[v] += add;
    }
    else{
        push(v);
        ll tm = (tl + tr) / 2;
        updatesegtree(v*2, tl, tm, l, min(tm, r), add);
        updatesegtree(v*2+1, tm+1, tr, max(tm+1, l), r, add);
        t[v] = max(t[v*2], t[v*2+1]);
    }
}
ll querysegtree(ll v, ll tl, ll tr, ll l, ll r){
    if(l > r) return -INF;
    if(l <= tl && tr <= r) return t[v];
    push(v);
    ll tm = (tl + tr) / 2;
    return max(querysegtree(v*2, tl, tm, l, min(tm, r)), querysegtree(v*2+1, tm+1, tr, max(tm+1, l), r));
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //Ask for max value from g[x] to g[y] after addition modification query to g[i,i+1,i+2...i+x];
    //Query: O(log n)
    //Lazy Propagation
    n = 10;
    t.resize(n*4+1);
    g.resize(n);
    lazy.resize(n*4+1);
    for(int i = 0;i<n;i++){
        g[i] = i+1;
    }
    buildsegtree(1, 0, n-1);
    updatesegtree(1, 0, n-1, 2, 8, 7);
    for(int i = 0;i<n;i++){
        for(int j = i;j<n;j++){
            cout<<"max element from "<<i<<" to "<<j<<" is "<<querysegtree(1, 0, n-1, i, j)<<endl;
        }
    }
    return 0;
}