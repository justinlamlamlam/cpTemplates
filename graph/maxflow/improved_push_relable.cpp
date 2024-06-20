#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define inf INT_MAX
ll n;
vector< vector<ll> > cap, flow;
vector<ll> height, excess;
void push(ll u, ll v){
    ll d = min(excess[u], cap[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;
    excess[u] -= d;
    excess[v] += d;
}
void relebal(ll u){
    ll d = inf;
    for(int i = 0;i<n;i++){
        if(cap[u][i] - flow[u][i] > 0){
            d = min(d, height[i]);
        }
    }
    if(d < inf){
        height[u] = d+1;
    }
}
vector<ll> findmaxhv(ll s, ll t){
    vector<ll> maxh;
    for(int i = 0;i<n;i++){
        if(i!=s && i!=t && excess[i] > 0){
            if(!maxh.empty() && height[i] > height[maxh[0]]) maxh.clear();
            if(maxh.empty() || height[i] == height[maxh[0]]) maxh.pb(i);
        }
    }
    return maxh;
}
ll maxflow(ll s, ll t){
    height.assign(n, 0);
    height[s] = n;
    flow.assign(n, vector<ll>(n, 0));
    excess.assign(n, 0);
    excess[s] = inf;
    for(int i = 0;i<n;i++){
        if(i!=s){
            push(s,i);
        }
    }

    vector<ll> current;
    while(!(current = findmaxhv(s, t)).empty()){
        for(int i : current){
            bool pushed = false;
            for(int j = 0;j<n && excess[i];j++){
                if(cap[i][j] - flow[i][j] > 0 && height[i] == height[j]+1){
                    push(i, j);
                    pushed = true;
                }
            }
            if(!pushed){
                relebal(i);
                break;
            }
        }
    }
    ll maxf = 0;
    for(int i = 0;i<n;i++){
        maxf += flow[i][t];
    }
    return maxf;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //maxflow algorithm using improved push relabel
    //O(V3)
    n = 5;
    cap.assign(n, vector<ll>(n));
    cap[0][1] = 2;
    cap[1][2] = 3;
    cap[2][3] = 4;
    cap[0][4] = 2;
    cap[3][4] = 5;
    cout<<maxflow(0,4)<<endl;
    return 0;
}