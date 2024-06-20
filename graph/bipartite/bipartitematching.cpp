#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
ll n, k;
vector< vector<ll> > g;
vector<ll> mt;
vector<bool> used;
bool try_kuhn(ll v){
    if(used[v]) return false;
    used[v] = true;
    for(ll to : g[v]){
        if(mt[to] == -1 || try_kuhn(mt[to])){
            mt[to] = v;
            return true;
        }
    }
    return false;
}
void findmatching(){
    mt.assign(k, -1);
    vector<bool> used1(n, false);
    for(ll v = 0;v<n;v++){
        for(ll to : g[v]){
            if(mt[to] == -1){
                mt[to] = v;
                used1[v] = true;
                break;
            }
        }
    }
    for(ll v = 0;v<n;v++){
        if(used1[v]) continue;
        used.assign(n, false);
        try_kuhn(v);
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //kuhn's algorithm for max matching
    //O(nm) worst case, but usually better
    //O(sqrt(n)m) --> Hopcroft-Karp-Karzanov algorithm
    //n = top part, m = bottom part, g[v] = edge from v in n to g[v] in m
    n = 2;
    k = 3;
    g.assign(n, vector<ll>(0));
    g[0].pb(0);
    g[1].pb(0);
    g[1].pb(1);
    g[1].pb(2);
    findmatching();
    for(int i = 0;i<k;i++){
        if(mt[i] != -1){
            cout<<mt[i] + 1<<' '<<i+1<<endl;
        }
    }
    return 0;
}