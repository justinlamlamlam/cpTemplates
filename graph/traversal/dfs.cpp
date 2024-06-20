#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
struct node{
    bool visited=false;
    ll key;
    ll par_cnt;
    ll chi_cnt;
    vector<ll> chi;
    vector<ll> par;
};
ll n;
node gra[200005];
void dfs(ll v){
    gra[v].visited=true;
    for(int i = 0;i<gra[v].chi_cnt;i++){
        if(!gra[gra[v].chi[i]].visited){
            dfs(gra[v].chi[i]);
        }
    }
}
void add_edge(ll s, ll t){
    gra[s].chi.pb(t);
    gra[s].chi_cnt++;
    gra[t].par.pb(s);
    gra[t].par_cnt++;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    n =5;
    add_edge(0,1);
    add_edge(1,2);
    add_edge(2,3);
    add_edge(1,4);
    dfs(0);
    for(int i = 0;i<5;i++) cout<<gra[i].visited<<' ';
    cout<<endl;
    return 0;
}