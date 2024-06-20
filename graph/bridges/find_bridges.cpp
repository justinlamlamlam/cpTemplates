#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
struct node{
    ll key;
    ll chi_cnt;
    vector<ll> chi;
};
ll n;
ll timer;
bool visited[200005];
ll tin[200005];
ll low[200005];
vector< pair<ll,ll> > bridges;
node gra[200005];
void dfs(ll v, ll p = -1){
    visited[v]=true;
    tin[v] = low[v] = timer++;
    for(int i = 0;i<gra[v].chi_cnt;i++){
        if(p == gra[v].chi[i]) continue;
        if(visited[gra[v].chi[i]]){
            low[v] = min(low[v], tin[gra[v].chi[i]]);
        }
        else{
            dfs(gra[v].chi[i],v);
            low[v] = min(low[v], low[gra[v].chi[i]]);
            if(low[gra[v].chi[i]] > tin[v]){
                bridges.pb(make_pair(v,gra[v].chi[i]));
            }
        }
    }
}
void find_bridges(){
    timer = 0;
    bridges.clear();
    for(int i = 0;i<n;i++) visited[i]=false;
    for(int i = 0;i<n;i++) tin[i]=-1;
    for(int i = 0;i<n;i++) low[i]=-1;
    for(int i = 0;i<n;i++){
        if(!visited[i]){
            dfs(i);
        }
    }

}
void add_edge(ll s, ll t){
    gra[s].chi.pb(t);
    gra[s].chi_cnt++;
    gra[t].chi.pb(s);
    gra[t].chi_cnt++;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //find bridges (edge when removed makes the graph unconnected)
    //graph is UNdirected
    //Time complexity: O(v+e)
    n = 6;
    add_edge(0,1);
    add_edge(1,2);
    add_edge(2,3);
    add_edge(3,4);
    add_edge(4,0);
    add_edge(0,5);
    find_bridges();
    for(int i = 0;i<bridges.size();i++) cout<<bridges[i].first<<' '<<bridges[i].second<<endl;
    return 0;
}