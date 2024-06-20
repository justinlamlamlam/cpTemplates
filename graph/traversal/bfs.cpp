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
ll len[200005];
bool vis[200005];
ll bfs_par[200005];
void bfs(ll v){
    queue<ll> q;
    queue<ll> lenq;
    queue<ll> parq;
    q.push(v);
    lenq.push(0);
    parq.push(0);
    while(q.size()>0){
        ll p = q.front();
        q.pop();
        ll lenp = lenq.front();
        lenq.pop();
        ll parp = parq.front();
        parq.pop();
        vis[p]=true;
        len[p]=lenp;
        bfs_par[p]=parp;
        for(int i = 0;i<gra[p].chi_cnt;i++){
            if(!vis[gra[p].chi[i]]){
                q.push(gra[p].chi[i]);
                lenq.push(lenp+1);
                parq.push(p);
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
    ll n =5;
    add_edge(0,1);
    add_edge(1,2);
    add_edge(2,3);
    add_edge(1,4);
    bfs(0);
    for(int i = 0;i<5;i++) cout<<i<<":"<<bfs_par[i]<<' '<<len[i]<<endl;
    return 0;
}