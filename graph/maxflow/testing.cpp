#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define INF INT_MAX
int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}
void add_edge(int u, int v, int w){
    adj[u][v] = w;
    adj[v][u] = w;
}
int main(){
    n = 5;
    adj.assign(n, vector<int>(n));
    capacity.assign(n, vector<int>(n));
    add_edge(0,1,1);
    add_edge(1,2,2);
    add_edge(2,3,3);
    add_edge(3,4,4);
    cout<<maxflow(0,4)<<endl;
}