#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
vector< vector<ll> > g;
vector<ll> deg;
vector<ll> res;
ll n;
bool findeucycle(){
    ll fir = 0;
    while(fir<n && !deg[fir]){
        fir++;
    }
    if(fir == n) return false;
    ll v1 = -1, v2 = -1;
    bool gg = false;
    for(int i = 0;i<n;i++){
        if(deg[i] & 1){
            if(v1 == -1) v1 = i;
            else if(v2 == -1) v2 = i;
            else gg = true;
        }
    }
    if(v1 != -1){
        g[v1][v2]++;
        g[v2][v1]++;
    }
    stack<ll> s;
    s.push(fir);
    while(!s.empty()){
        ll v = s.top();
        ll i;
        for(i = 0;i<n;i++){
            if(g[v][i]) break;
        }
        if(i == n){
            res.pb(v);
            s.pop();
        }
        else{
            g[v][i]--;
            g[i][v]--;
            s.push(i);
        }
    }
    if(v1 != -1){
        for(size_t i = 0;i+1 < res.size(); i++){
            if((res[i] == v1 && res[i+1] == v2) || (res[i] == v2 && res[i+1] == v1)){
                vector<ll> res2;
                for(size_t j = i+1; j < res.size(); j++){
                    res2.pb(res[j]);
                }
                for(size_t j = 1; j <= i; j++){
                    res2.pb(res[j]);
                }
                res = res2;
                break;
            }
        }
    }
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            if(g[i][j]) gg = true;
        }
    }
    if(gg) return false;
    else return true;
}
void init(){
    vector<ll> v;
    v.assign(n, 0);
    g.assign(n, v);
    deg.assign(n,0);
    res.clear();
}
void add_edge(ll s, ll t, ll cnt){
    g[s][t] = cnt;
    deg[s] += cnt;
    g[t][s] = cnt;
    deg[t] += cnt;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    n =5;
    init();
    add_edge(0,1,1);
    add_edge(1,2,1);
    add_edge(2,3,1);
    add_edge(3,4,1);
    add_edge(1,4,2);
    //add_edge(4,0);
    bool hc = findeucycle();
    if(hc){
        cout<<"YES"<<endl;
        for(int i = 0;i<res.size();i++) cout<<res[i]<<' ';
        cout<<endl;
    }
    else{
        cout<<"NO"<<endl;
    }
    return 0;
}