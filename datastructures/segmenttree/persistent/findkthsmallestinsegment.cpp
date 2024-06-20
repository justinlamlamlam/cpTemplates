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
    if(tl == tr) return new vertex(0);
    ll tm = (tl + tr)/2;
    return new vertex(buildsegtree(tl, tm), buildsegtree(tm+1, tr));
}
ll segtreequery(vertex* vl, vertex* vr, ll tl, ll tr, ll k){
    if(tl == tr) return tl;
    ll tm = (tl + tr)/2, leftcnt = vr->l->sum - vl->l->sum;
    if(leftcnt >= k) return segtreequery(vl->l, vr->l, tl, tm, k);
    return segtreequery(vl->r, vr->r, tm+1, tr, k-leftcnt);
}
vertex* segtreeupdate(vertex* v, ll tl, ll tr, ll pos){
    if(tl == tr) return new vertex(v -> sum+1);
    ll tm = (tl + tr) / 2;
    if(pos <= tm) return new vertex(segtreeupdate(v->l, tl, tm, pos), v->r);
    else return new vertex(v->l, segtreeupdate(v->r, tm+1, tr, pos));
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //Find kth smallest element in segment g[i ... i+x]
    //Time complexity: Update O(log n), Query(log n)
    n = 10;
    ll tl = 0, tr = n+1;
    vector<vertex*> roots;
    roots.pb(buildsegtree(tl, tr));
    t.resize(n*4+1, -1);
    g.resize(n);
    for(int i = 0;i<n;i++) g[i] = i+1;
    for(int i = 0;i<n;i++){
        roots.pb(segtreeupdate(roots.back(), tl, tr, g[i]));
    }
    for(int i = 0;i<n;i++){
        for(int j = i+2;j<n;j++){
            cout<<"2nd smallest number from g["<<i<<"] to g["<<j-1<<"] is "<<segtreequery(roots[i], roots[j], tl, tr, 2)<<endl;
        }
    }
    return 0;
}