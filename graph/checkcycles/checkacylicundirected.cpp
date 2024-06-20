#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
struct node{
    bool visited=false;
    ll key;
    ll adj_cnt;
    vector<ll> adj;
};
ll n;
node gra[200005];
vector<ll> vis;
ll cycles, cyclet;
vector<ll> cycle;
vector<ll> parent;
bool dfs(ll v, ll par){
    vis[v] = true;
    for(int u : gra[v].adj){
        if(u == par){
            continue;
        }
        if(vis[u]){
            cycles = u;
            cyclet = v;
            return true;
        }
        parent[u] = v;
        if(dfs(u, parent[u])){
            return true;
        }
    }
    return false;
}
bool findcycle(){
    vis.assign(n,false);
    parent.assign(n,-1);
    cycles = -1;
    for(int v = 0;v<n;v++){
        if(!vis[v] && dfs(v,parent[v])){
            break;
        }
    }
    if(cycles == -1){
        return false;
    }
    cycle.pb(cycles);
    for(int v = cyclet; v!=cycles; v = parent[v]){
        cycle.pb(v);
    }
    return true;
}
void add_edge(ll s, ll t){
    gra[s].adj.pb(t);
    gra[s].adj_cnt++;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    n =5;
    add_edge(0,1);
    add_edge(1,2);
    add_edge(2,3);
    add_edge(1,4);
    //add_edge(4,0);
    bool hc = findcycle();
    if(hc){
        cout<<"yes"<<endl;
        for(ll v : cycle){
            cout<<v<<' ';
        }
        cout<<endl;
    }
    else{
        cout<<"NO"<<endl;
    }
    return 0;
}