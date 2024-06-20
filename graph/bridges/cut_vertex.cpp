#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
struct node{
    ll key;
    ll adj_cnt;
    vector<ll> adj;
};
ll n;
node gra[200005];
ll timer;
vector<ll> tin, low;
vector<bool> visited;
bool cutpoints[200005];
void dfs(ll v, ll p = -1){
    visited[v]=true;
    tin[v] = low[v] = timer++;
    int children = 0;
    for(int i = 0;i<gra[v].adj_cnt;i++){
        ll to = gra[v].adj[i];
        if(!visited[to]){
            children++;
            dfs(to,v);
            low[v] = min(low[v], low[to]);
            if(low[to] >= tin[v] && p != -1){
                cutpoints[v]=true;
            }
        }
        else if(to != p){
            low[v] = min(low[v], tin[to]);
        }
    }
    if(children > 1 && p == -1){
        cutpoints[v]=true;
    }
}
void findcutpoints(){
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for(int i = 0;i<n;i++){
        cutpoints[i]=false;
    }
    for(int i = 0;i<n;i++){
        if(!visited[i]){
            dfs(i);
        }
    }
}
void add_edge(ll s, ll t){
    gra[s].adj.pb(t);
    gra[s].adj_cnt++;
    gra[t].adj.pb(s);
    gra[t].adj_cnt++;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //algorithm to find cut vertex (vertex when removed with its edges makes the graph disconnected)
    //Unconnected graph
    //O(v+e)
    n =5;
    add_edge(0,1);
    add_edge(1,2);
    add_edge(2,3);
    add_edge(3,4);
    findcutpoints();
    for(int i = 0;i<n;i++) cout<<cutpoints[i]<<' ';
    cout<<endl;
    return 0;
}