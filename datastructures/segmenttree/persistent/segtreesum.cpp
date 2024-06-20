#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
ll n;
vector<ll> t;
vector<ll> g;
struct vertex{
    vertex *l, *r;
    ll sum;

    vertex(ll val) : l (nullptr), r(nullptr), sum(val){};
    vertex(vertex *l, vertex *r) : l(l), r(r), sum(0){
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    };
};
vertex* buildsegtree(ll tl, ll tr){
    if(tl == tr) return new vertex(g[tl]);
    ll tm = (tl + tr)/2;
    return new vertex(buildsegtree(tl, tm), buildsegtree(tm+1, tr));
}
ll segtreequery(vertex* v, ll tl, ll tr, ll l, ll r){
    if(l>r) return 0;
    if(tl == l && tr == r) return v -> sum;
    ll tm = (tl + tr)/2;
    return segtreequery(v->l, tl, tm, l, min(tm, r)) + segtreequery(v->r, tm+1, tr, max(l, tm+1), r);
}
vertex* segtreeupdate(vertex* v, ll tl, ll tr, ll pos, ll newval){
    if(tl == tr) return new vertex(newval);
    ll tm = (tl + tr) / 2;
    if(pos <= tm) return new vertex(segtreeupdate(v->l, tl, tm, pos, newval), v->r);
    else return new vertex(v->l, segtreeupdate(v->r, tm+1, tr, pos, newval));
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //segment tree: Range sum query with persistency
    //Time complexity: Update O(log n), Query(log n)
    n = 10;
    t.resize(n*4+1, -1);
    g.resize(n);
    for(int i = 0;i<n;i++) g[i] = i+1;
    return 0;
}