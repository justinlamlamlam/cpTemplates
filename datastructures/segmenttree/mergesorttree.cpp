#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define INF LLONG_MAX
ll const& MAXN = 200005;
ll n;
vector<ll> t[4*200005+1];
vector<ll> g;
void buildtree(ll v, ll tl, ll tr){
    if(tl == tr) t[v] = vector<ll> (1, g[tl]);
    else{
        ll tm = (tl + tr) / 2;
        buildtree(v*2, tl, tm);
        buildtree(v*2 + 1, tm + 1, tr);
        merge(t[v*2].begin(), t[v*2].end(), t[v*2+1].begin(), t[v*2+1].end(), back_inserter(t[v]));
    }
}
ll segtreequery(ll v, ll tl, ll tr, ll l, ll r, ll x){
    if(l > r) return INF;
    if(l == tl && r == tr){
        vector<ll>::iterator pos = lower_bound(t[v].begin(), t[v].end(), x);
        if(pos!=t[v].end()) return *pos;
        return INF;
    }
    ll tm = (tl + tr) / 2;
    return min(segtreequery(v*2, tl, tm, l, min(r, tm),x), segtreequery(v*2+1, tm+1, tr, max(l, tm+1), r, x));
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //segment tree: Find smallest number >= x for some x between index i and j
    //Time complexity: Cannot update (see mergesorttreewithmod.cpp with modifications available), Query(log^2 n)
    //just use mergesorttreewithmod.cpp.
    n = 10;
    g.resize(n);
    for(int i = 0;i<n;i++) g[i] = n-i;
    buildtree(1, 0, n-1);
    /*for(int i = 0;i<n;i++){
        g[i] = i+1;
        segtreeupdate(1, 0, n-1, i, i+1);
    }*/
    for(int i = 0;i<10;i++){
        cout<<"smallest number > "<<i<<" is "<<segtreequery(1, 0, n-1, 0, n-1, i)<<endl;
    }
    return 0;
}