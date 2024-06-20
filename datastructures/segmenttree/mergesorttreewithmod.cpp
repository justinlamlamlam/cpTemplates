#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define INF LLONG_MAX
ll const& MAXN = 200005;
ll n;
vector< multiset<ll> > t;
vector<ll> g;
void buildtree(ll v, ll tl, ll tr){
    if(tl == tr) t[v].insert(g[tl]);
    else{
        ll tm = (tl + tr) / 2;
        buildtree(v*2, tl, tm);
        buildtree(v*2 + 1, tm + 1, tr);
        set_union(t[v*2].begin(), t[v*2].end(), t[v*2+1].begin(), t[v*2+1].end(), inserter(t[v], t[v].begin()));
    }
}
ll segtreequery(ll v, ll tl, ll tr, ll l, ll r, ll x){
    if(l > r) return INF;
    if(l == tl && r == tr){
        multiset<ll>::iterator pos = lower_bound(t[v].begin(), t[v].end(), x);
        if(pos!=t[v].end()) return *pos;
        return INF;
    }
    ll tm = (tl + tr) / 2;
    return min(segtreequery(v*2, tl, tm, l, min(r, tm),x), segtreequery(v*2+1, tm+1, tr, max(l, tm+1), r, x));
}
void segtreeupdate(ll v, ll tl, ll tr, ll pos, ll newval){
    t[v].erase(t[v].find(g[pos]));
    t[v].insert(newval);
    if(tl != tr){
        ll tm = (tl + tr) / 2;
        if(pos <= tm) segtreeupdate(v*2, tl, tm, pos, newval);
        else segtreeupdate(v*2+1, tm+1, tr, pos, newval);
    }
    else{
        g[pos] = newval;
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //segment tree: Find smallest number >= x for some x between index i and j with modification
    //Time complexity: Update O(log n), Query(log^2 n)
    //if want query to be log n, use fractional cascading
    n = 10;
    t.resize(n*4+1);
    g.resize(n);
    for(int i = 0;i<n;i++) g[i] = (n-i);
    buildtree(1, 0, n-1);
    for(int i = 0;i<n;i++){
        segtreeupdate(1, 0, n-1, i, (i+1)*2);
    }
    for(int i = 0;i<n*4;i++){
        cout<<"i "<<i<<" : ";
        for(multiset<ll>::iterator j = t[i].begin(); j!=t[i].end();j++){
            cout<<*j<<' ';
        }
        cout<<endl;
    }
    cout<<"end of update query"<<endl;
    for(int i = 0;i<20;i++){
        cout<<"smallest number >= "<<i<<" is "<<segtreequery(1, 0, n-1, 0, n-1, i)<<endl;
    }
    return 0;
}