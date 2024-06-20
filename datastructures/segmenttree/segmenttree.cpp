#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
ll n;
vector<ll> t;
vector<ll> g;
void buildtree(ll v, ll tl, ll tr){
    if(tl == tr) t[v] = g[tl];
    else{
        ll tm = (tl+tr)/2;
        buildtree(v*2, tl, tm);
        buildtree(v*2+1, tm+1, tr);
        t[v] = t[v*2] + t[v*2+1];
    }
}
ll segtreequery(ll v, ll tl, ll tr, ll l, ll r){
    //cout<<v<<' '<<tl<<' '<<tr<<' '<<l<<' '<<r<<endl;
    if(l>r) return 0;
    if(l == tl && r == tr) return t[v];
    ll tm = (tl + tr) / 2;
    return segtreequery(v*2, tl, tm, l, min(r, tm)) + segtreequery(v*2+1, tm + 1, tr, max(l, tm+1), r);
}
void updatesegtree(ll v, ll tl, ll tr, ll pos, ll newval){
    if(tl == tr) t[v] = newval;
    else{
        ll tm = (tl + tr)/2;
        if(pos <= tm) updatesegtree(v*2, tl, tm, pos, newval);
        else updatesegtree(v*2+1, tm+1, tr, pos, newval);
        t[v] = t[v*2] + t[v*2+1];
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //segment tree: Range sum query
    //Time complexity: Update O(log n), Query(log n)
    n = 10;
    t.resize(n*4+1, -1);
    g.resize(n);
    for(int i = 0;i<n;i++) g[i] = i+1;
    buildtree(1, 0, n-1);
    for(int i = 0;i<n;i++){
        g[i] = n-i;
        updatesegtree(1, 0, n-1, i, n-i);
    }
    for(int i = 0;i<n;i++){
        for(int j = i;j<n;j++){
            cout<<"sum from "<<i<<" to "<<j<<" = "<<segtreequery(1, 0, n-1, i, j)<<"\n";
        }
    }
    return 0;
}