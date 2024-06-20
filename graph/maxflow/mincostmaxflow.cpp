#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
struct edge{
    ll from, to, cap, cost;
};
vector< vector<ll> > adj, cost, cap;
const ll inf = 1e9;
void shortestpath(ll n, ll v0, vector<ll>& d, vector<ll>& p){
    d.assign(n, inf);
    d[v0] = 0;
    vector<bool> inq(n, false);
    queue<ll> q;
    q.push(v0);
    p.assign(n, -1);

    while(!q.empty()){
        ll u = q.front();
        q.pop();
        inq[u] = false;
        for(int v : adj[u]){
            if(cap[u][v] > 0 && d[v] > d[u] + cost[u][v]){
                d[v] = d[u] + cost[u][v];
                p[v] = u;
                if(!inq[v]){
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
}
ll mincostflow(ll n, vector<edge> edges, int k, int s, int t){
    adj.assign(n, vector<ll>());
    cost.assign(n, vector<ll>(n, 0));
    cap.assign(n, vector<ll>(n, 0));
    for(edge e : edges){
        adj[e.from].pb(e.to);
        adj[e.to].pb(e.from);
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost;
        cap[e.from][e.to] = e.cap;
    }
    
    ll flow = 0;
    ll cost = 0;
    vector<ll> d, p;
    while(flow < k){
        shortestpath(n, s, d, p);
        if(d[t] == inf){
            break;
        }

        ll f = k - flow;
        ll cur = t;
        while(cur != s){
            f = min(f, cap[p[cur]][cur]);
            cur = p[cur];
        }

        flow += f;
        cost += f * d[t];
        cur = t;
        while(cur != s){
            cap[p[cur]][cur] -= f;
            cap[cur][p[cur]] += f;
            cur = p[cur];
        }
        return cost;
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //min cost max flow
    //O(V3)
    ll n = 5;
    vector<edge> edges;
    edges.pb({0,1,2,3});
    edges.pb({1,2,3,1});
    edges.pb({2,3,4,4});
    edges.pb({3,4,5,5});
    cout<<mincostflow(n, edges, inf, 0, 4)<<endl;
    
    return 0;
}