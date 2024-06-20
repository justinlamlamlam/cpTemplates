#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define INF LLONG_MAX
ll const& MAXN = 200005;
ll n;
vector<ll> t;
vector<ll> g;
vector<ll> marked;
void buildsegtree(ll v, ll tl, ll tr){
    if(tl == tr) t[v] = g[tl];
    else{
        ll tm = (tl + tr) / 2;
        buildsegtree(v*2, tl, tm);
        buildsegtree(v*2 + 1, tm+1, tr);
        t[v] = 0;
    }
}
void pushsegtree(ll v){
    if(marked[v]){
        t[v*2] = t[v*2+1] = t[v];
        marked[v*2] = marked[v*2+1] = true;
        marked[v] = false;
    }
}
void updatesegtree(ll v, ll tl, ll tr, ll l, ll r, ll newval){
    if(l > r) return;
    if(l == tl && r == tr){
        t[v] = newval;
        marked[v] = true;
    }
    else{
        pushsegtree(v);
        ll tm = (tl + tr) / 2;
        updatesegtree(v*2, tl, tm, l, min(tm, r), newval);
        updatesegtree(v*2+1, tm+1, tr, max(tm+1, l), r, newval);
    }
}
ll querysegtree(ll v, ll tl, ll tr, ll pos){
    if(tl == tr) return t[v];
    pushsegtree(v);
    ll tm = (tl + tr) / 2;
    if(pos <= tm) querysegtree(v*2, tl, tm, pos);
    else querysegtree(v*2+1, tm+1, tr, pos);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //Ask for value of g[i] after assignment modification query to g[i,i+1,i+2...i+x];
    //Query: O(log n)
    //Lazy Propagation
    n = 10;
    t.resize(n*4+1);
    g.resize(n);
    marked.resize(n*4+1);
    for(int i = 0;i<n;i++){
        g[i] = i+1;
    }
    buildsegtree(1, 0, n-1);
    updatesegtree(1, 0, n-1, 0, 9, 10);
    updatesegtree(1, 0, n-1, 1, 8, 11);
    updatesegtree(1, 0, n-1, 2, 7, 12);
    updatesegtree(1, 0, n-1, 3, 6, 13);
    updatesegtree(1, 0, n-1, 4, 5, 14);
    for(int i = 0;i<n;i++){
        cout<<"The element of "<<i<<" is : "<<querysegtree(1, 0, n-1, i)<<endl;
    }
    return 0;
}