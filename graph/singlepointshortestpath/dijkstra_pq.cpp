#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
struct node{
    bool visited=false;
    int key;
    int adj_cnt;
    vector< pair<int,int> > adj;
};
int n;
node gra[200005];
vector<int> d;
vector<int> p;
void dijkstra(int root){
    d.assign(n, INT_MAX);
    p.assign(n, -1);

    d[root]=0;
    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<pii> > q;
    q.push({0,root});

    while(!q.empty()){
        int v = q.top().first;
        int dv = q.top().second;
        q.pop();
        if(dv != d[v]){
            continue;
        }
        for(pii i : gra[v].adj){
            int to = i.first;
            int len = i.second;
            if(d[v] + len < d[to]){
                d[to] = d[v] + len;
                p[to] = v;
                q.push({to, d[to]});
            }
        }
    }
}
vector<int> bt_path(int s, int t){
    vector<int> path;
    for(int v = t; v != s; v=p[v]){
        path.pb(v);
    }
    path.pb(s);
    reverse(path.begin(), path.end());
    return path;
}
void add_edge(int s, int t, int weight){
    gra[s].adj.pb(make_pair(t,weight));
    gra[s].adj_cnt++;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //dijkstra using priority queue
    //Faster when everything is int
    //for faster version with exception, see desopo
    n =5;
    add_edge(0,1,4);
    add_edge(1,2,3);
    add_edge(2,3,5);
    add_edge(1,4,9);
    add_edge(2,4,1);
    dijkstra(0);
    for(int i = 0;i<n;i++) cout<<i<<": "<<d[i]<<"\n";
    for(int i = 1;i<n;i++){
        vector<int> path = bt_path(0, i);
        for(int j = 0;j<path.size();j++) cout<<path[j]<<' ';
        cout<<"\n";
    }
    cout<<endl;
    return 0;
}