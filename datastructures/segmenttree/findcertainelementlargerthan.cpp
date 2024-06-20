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
        t[v] = max(t[v*2], t[v*2+1]);
    }
}
ll segtreequery(ll v, ll lv, ll rv, ll l, ll r, ll x){
    if(lv > r || rv < l) return -1;
    if(l <= lv && rv <= r){
        if(t[v] <= x) return -1;
        while(lv != rv){
            ll mv = lv + (rv - lv)/2;
            if(t[v*2] > x){
                v = 2*v;
                rv = mv;
            }
            else{
                v = 2*v + 1;
                lv = mv+1;
            }
        }
        return lv;
    }
    ll mv = lv + (rv + lv)/2;
    ll rs = segtreequery(2*v, lv, mv, l, r, x);
    if(rs != -1) return rs;
    return segtreequery(2*v+1, mv+1, rv, l, r, x);
}
void updatesegtree(ll v, ll tl, ll tr, ll pos, ll newval){
    if(tl == tr) t[v] = newval;
    else{
        ll tm = (tl + tr)/2;
        if(pos <= tm) updatesegtree(v*2, tl, tm, pos, newval);
        else updatesegtree(v*2+1, tm+1, tr, pos, newval);
        t[v] = max(t[v*2], t[v*2+1]);
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //segment tree: Find smallest index i such that sum of a[0] + ... + a[i] > x
    //Time complexity: Update O(log n), Query(log n)
    n = 10;
    t.resize(n*4+1, -1);
    g.resize(n);
    for(int i = 0;i<n;i++) g[i] = n-i;
    buildtree(1, 0, n-1);
    for(int i = 0;i<n;i++){
        g[i] = i+1;
        updatesegtree(1, 0, n-1, i, i+1);
    }
    for(int i = 1;i<=10;i++){
        cout<<"smallest index i such that a[i] > "<<i<<" : "<<segtreequery(1, 0, n-1, 0, n-1, i)<<endl;
    }
    return 0;
}