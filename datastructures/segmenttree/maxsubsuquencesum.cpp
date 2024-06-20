#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
ll n;
struct node {
    ll sum, pref, suff, ans;
};
vector<ll> g;
vector<node> t;
node combine(node l, node r){
    node res;
    res.sum = l.sum + r.sum;
    res.pref = max(l.pref, l.sum + r.pref);
    res.suff = max(l.suff + r.sum, r.suff);
    res.ans = max(max(l.ans, r.ans), l.suff + r.suff);
    return res;
}
node make_node(ll val){
    node res;
    res.sum = val;
    res.pref = res.suff = res.ans = max((ll)0, val);
    return res;
}
void buildtree(ll v, ll tl, ll tr){
    if(tl == tr){
        t[v] = make_node(g[tl]);
    }
    else{
        ll tm = (tl+tr)/2;
        buildtree(v*2, tl, tm);
        buildtree(v*2+1, tm+1, tr);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}
void segtreeupdate(ll v, ll tl, ll tr, ll pos, ll newval){
    if(tl == tr){
        t[v] = make_node(newval);
    }
    else{
        ll tm = (tl + tr)/2;
        if(pos <= tm){
            segtreeupdate(v*2, tl, tm, pos, newval);
        }
        else{
            segtreeupdate(v*2+1, tm+1, tr, pos, newval);
        }
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}
node segtreequery(ll v, ll tl, ll tr, ll l, ll r){
    if(l>r) return make_node(0);
    if(l == tl && r == tr) return t[v];
    ll tm = (tl + tr) / 2;
    return combine(segtreequery(v*2, tl, tm, l, min(r, tm)), segtreequery(v*2+1, tm+1, tr, max(l, tm+1), r));
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //segment tree: Find maximum subsequence sum from i to j
    //Time complexity: Update O(log n), Query(log n)
    n = 10;
    t.resize(n*4+1);
    g.resize(n);
    for(int i = 0;i<n;i++) g[i] = n-i;
    buildtree(1, 0, n-1);
    for(int i = 0;i<n;i++){
        g[i] = i+1;
        segtreeupdate(1, 0, n-1, i, i+1);
    }
    for(int i = 0;i<10;i++){
        for(int j = i;j<10;j++){
            cout<<"smallest subsequence sum in from "<<i<<" to "<<j<<" is "<<segtreequery(1, 0, n-1, i, j).ans<<endl;
        }
    }
    return 0;
}