#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
struct edge{
    ll u, v, w;
};
struct node{
    bool visited=false;
    int key;
    int adj_cnt;
    vector< pair<int,int> > adj;
};
ll n;
node gra[200005];
vector<ll> d;
vector<edge> edges;
ll ecnt=0;
void bford(ll root){
    d.assign(n, LLONG_MAX);
    d[root]=0;
    while(true){
        bool any = false;
        for(int j = 0;j<ecnt;j++){
            if(d[edges[j].u] < LLONG_MAX){
                if(d[edges[j].v] > d[edges[j].u] + edges[j].w){
                    d[edges[j].v] = d[edges[j].u] + edges[j].w;
                    any = true;
                }
            }
        }
        if(!any) break;
    }
}
bool spfa(ll root){
    d.assign(n,LLONG_MAX);
    vector<ll> cnt(n,0);
    vector<bool> inqueue(n,false);
    queue<ll> q;

    d[root] = 0;
    q.push(root);
    inqueue[root] = true;
    while(!q.empty()){
        ll v = q.front();
        q.pop();
        inqueue[v]=false;
        for(int i = 0;i<gra[v].adj_cnt;i++){
            pair<ll,ll> edge = gra[v].adj[i];
            ll to = edge.first;
            ll w = edge.second;
            if(d[v] + w < d[to]){
                d[to] = d[v] + w;
                if(!inqueue[to]){
                    q.push(to);
                    inqueue[to] = true;
                    cnt[to]++;
                    if(cnt[to] > n){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
void add_edge(ll s, ll t, ll w){
    edge e;
    e.u=s;e.v=t;e.w=w;
    edges.pb(e);
    ecnt++;
    gra[s].adj.pb(make_pair(t,w));
    gra[s].adj_cnt++;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //bellman ford algorithm: find shortest path from root, can handle negative weight edges
    //O(v*e) worst case, but much smaller when graph is normal
    //for optimised version, use spfa
    //spfa --> false: negative loop present
    n = 5;
    add_edge(0,1,4);
    add_edge(1,2,-3);
    add_edge(2,3,5);
    add_edge(1,4,9);
    add_edge(2,4,1);
    bford(0);
    for(int i = 0;i<n;i++) cout<<d[i]<<' ';
    cout<<endl;
    add_edge(2,1,2);
    bool nc = spfa(0);
    cout<<"is there negative cycle: "<<(nc ? "no" : "yes")<<endl;
    for(int i = 0;i<n;i++) cout<<d[i]<<' ';
    cout<<endl;
    return 0;
}