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
stack<ll> dfss;
bool assigned[200005];
ll con_com[200005];
void dfs(ll v){
    gra[v].visited=true;
    for(int i = 0;i<gra[v].chi_cnt;i++){
        if(!gra[gra[v].chi[i]].visited){
            dfs(gra[v].chi[i]);
        }
    }
    dfss.push(v);
}
void rev_dfs(ll v, ll root){
    if(!assigned[v]){
        assigned[v]=true;
        con_com[v]=root;
        for(int i = 0;i<gra[v].par_cnt;i++){
            if(!assigned[gra[v].par[i]]){
                rev_dfs(gra[v].par[i],root);
            }
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
    add_edge(2,0);
    add_edge(0,3);
    add_edge(3,4);
    for(int i = 0;i<5;i++){
        if(!gra[i].visited){
            dfs(i);
        }
    }
    for(int i = 0;i<5;i++){
        ll a = dfss.top();
        rev_dfs(a,a);
        dfss.pop();
    }
    for(int i = 0;i<5;i++) cout<<i<<": "<<con_com[i]<<endl;
    return 0;
}