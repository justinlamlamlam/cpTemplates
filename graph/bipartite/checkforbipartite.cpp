#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
ll n;
vector< vector<ll> > adj;
bool checkbipartite(){
    vector<ll> side(n, -1);
    bool ans = true;
    queue<ll> q;
    for(int st = 0; st < n; st++){
        if(side[st] == -1){
            q.push(st);
            side[st] = 0;
            while(!q.empty()){
                ll v = q.front();
                q.pop();
                for(int u : adj[v]){
                    if(side[u] == -1){
                        side[u] = side[v] ^ 1;
                        q.push(u);
                    }
                    else{
                        ans &= side[u] != side[v];
                    }
                }
            }
        }
    }
    return ans;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    n = 5;
    adj.assign(n, vector<ll>());
    adj[0].pb(2);
    adj[0].pb(3);
    adj[0].pb(4);
    adj[1].pb(2);
    adj[1].pb(3);
    adj[2].pb(0);
    adj[2].pb(1);
    adj[3].pb(0);
    adj[3].pb(1);
    adj[4].pb(0);
    cout<<"is bipartite: "<<(checkbipartite() ? "yes" : "no")<<endl;
    return 0;
}