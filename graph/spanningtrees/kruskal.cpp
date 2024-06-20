#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
struct edge{
    ll u, v, w;
    bool operator<(edge const& other){
        return w < other.w;
    }
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
vector<ll> par;
vector<ll> rk;
vector<edge> result;
ll cost;
ll ecnt=0;
void makeset(ll v){
    par[v] = v;
}
ll findset(ll v){
    if(v==par[v]) return v;
    return par[v] = findset(par[v]);
}
void unionset(ll a, ll b){
    a = findset(a);
    b = findset(b);
    if(a!=b){
        if(rk[a] < rk[b]) swap(a,b);
        par[b] = a;
        if(rk[a] == rk[b]) rk[a]++;
    }
}
void init(){
    cost=0;
    par.resize(n);
    rk.resize(n);
    for(int i = 0;i<n;i++) makeset(i);
}
void kruskal(){
    sort(edges.begin(), edges.end());
    ll cnt=0;
    for(edge e: edges){
        if(findset(e.u) != findset(e.v)){
            cost += e.w;
            result.pb(e);
            unionset(e.u, e.v);
            cnt++;
            if(cnt == n-1) break;
        }
    }
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
    //kruskal: find mst using DSU
    //O(ElogE)
    n = 5;
    add_edge(0,1,4);
    add_edge(1,2,-3);
    add_edge(2,3,5);
    add_edge(1,4,9);
    add_edge(2,4,1);
    init();
    kruskal();
    cout<<result.size()<<endl;
    for(edge e:result){
        cout<<e.u<<' '<<e.v<<' '<<e.w<<"\n";
    }
    return 0;
}