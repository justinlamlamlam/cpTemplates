#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define INF LLONG_MAX
ll const& MAXN = 200005;
ll n;
vector<ll> t;
vector<ll> g;
void buildsegtree(ll v, ll tl, ll tr){
    if(tl == tr) t[v] = g[tl];
    else{
        ll tm = (tl + tr) / 2;
        buildsegtree(v*2, tl, tm);
        buildsegtree(v*2 + 1, tm+1, tr);
        t[v] = 0;
    }
}
void updatesegtree(ll v, ll tl, ll tr, ll l, ll r, ll add){
    if(l > r) return;
    if(l == tl && r == tr){
        t[v] += add;
    }
    else{
        ll tm = (tl + tr) / 2;
        updatesegtree(v*2, tl, tm, l, min(tm, r), add);
        updatesegtree(v*2+1, tm+1, tr, max(tm+1, l), r, add);
    }
}
ll querysegtree(ll v, ll tl, ll tr, ll pos){
    if(tl == tr) return t[v];
    ll tm = (tl + tr) / 2;
    if(pos <= tm) return t[v] + querysegtree(v*2, tl, tm, pos);
    else return t[v] + querysegtree(v*2+1, tm+1, tr, pos);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //Ask for value of g[i] after addition modification query to g[i,i+1,i+2...i+x];
    //Query: O(log n)
    //Lazy Propagation
    n = 10;
    t.resize(n*4+1);
    g.resize(n);
    for(int i = 0;i<n;i++){
        g[i] = i+1;
    }
    buildsegtree(1, 0, n-1);
    updatesegtree(1, 0, n-1, 2, 8, 7);
    for(int i = 0;i<n;i++){
        cout<<"The element of "<<i<<" is : "<<querysegtree(1, 0, n-1, i)<<endl;
    }
    return 0;
}