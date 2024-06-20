#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
struct node{
    bool visited=false;
    ll key;
    ll adj_cnt;
    vector< pair<ll,ll> > adj;
};
ll n;
node gra[200005];
vector<ll> d;
vector<ll> p;
void desopo(ll root){
    d.assign(n, LLONG_MAX);
    d[root] = 0;
    vector<ll> m(n,2);
    deque<ll> q;
    q.pb(root);
    p.assign(n,-1);

    while(!q.empty()){
        ll u = q.front();
        q.pop_front();
        m[u] = 0;
        for(ll i = 0;i<gra[u].adj_cnt;i++){
            pair<ll,ll> edge = gra[u].adj[i];
            ll to = edge.first;
            ll w = edge.second;
            if(d[to] > d[u] + w){
                d[to] = d[u] + w;
                p[to] = u;
                if(m[to] == 2){
                    m[to] = 1;
                    q.pb(to);
                }
                else if(m[to] == 0){
                    m[to] = 1;
                    q.push_front(to);
                }
            }
        }
    }
}
void add_edge(ll s, ll t, ll weight){
    gra[s].adj.pb(make_pair(t,weight));
    gra[s].adj_cnt++;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //D'Esopo-pape algorithm: find single source shortest path
    //Normally faster than dijkstra, but has exponential cases
    n =5;
    add_edge(0,1,4);
    add_edge(1,2,3);
    add_edge(2,3,5);
    add_edge(1,4,9);
    add_edge(2,4,1);
    desopo(0);
    for(ll i = 0;i<n;i++) cout<<d[i]<<' ';
    cout<<"\n";
    return 0;
}