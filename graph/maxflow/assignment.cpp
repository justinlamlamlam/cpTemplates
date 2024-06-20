#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
ll n;
vector<ll> assignment(vector< vector<ll> > a){
    ll m = n * 2 + 2;
    vector< vector<ll> > f(m, vector<ll>(m));
    ll s = m - 2, t = m - 1;
    ll cost = 0;
    ll inf = LLONG_MAX;
    while(true){
        vector<ll> dist(m, inf);
        vector<ll> p(m);
        vector<bool> inq(m, false);
        queue<ll> q;
        dist[s] = 0;
        p[s] = -1;
        q.push(s);
        while(!q.empty()){
            ll v = q.front();
            q.pop();
            inq[v] = false;
            if(v == s){
                for(ll i = 0;i<n;i++){
                    if(f[s][i] == 0){
                        dist[i] = 0;
                        p[i] = s;
                        inq[i] = true;
                        q.push(i);
                    }
                }
            }
            else{
                if(v < n){
                    for(ll j = n; j<n+n;j++){
                        if(f[v][j] < 1 && dist[j] > dist[v] + a[v][j-n]){
                            dist[j] = dist[v] + a[v][j-n];
                            p[j] = v;
                            if(!inq[j]){
                                q.push(j);
                                inq[j] = true;
                            }
                        }
                    }
                }
                else{
                    for(ll j = 0; j<n;j++){
                        if(f[v][j] < 0 && dist[j] > dist[v] - a[j][v-n]){
                            dist[j] = dist[v] - a[j][v-n];
                            p[j] = v;
                            if(!inq[j]){
                                q.push(j);
                                inq[j] = true;
                            }
                        }
                    }
                }
            }
        }
        ll curcost = inf;
        for(ll i = n;i<n+n;i++){
            if(f[i][t] == 0 && dist[i] < curcost){
                curcost = dist[i];
                p[t] = i;
            }
        }
        if(curcost == inf){
            break;
        }
        cost += curcost;
        for(ll cur = t; cur != -1; cur = p[cur]){
            ll prev = p[cur];
            if(prev != -1){
                f[cur][prev] = -(f[prev][cur] = 1);
            }
        }
    }
    
    vector<ll> ans(n);
    for(ll i = 0;i<n;i++){
        for(ll j = 0;j<n;j++){
            if(f[i][j+n] == 1){
                ans[i] = j;
            }
        }
    }
    return ans;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //Assignment problem: select n elements from each row and column from a n x n array
    //                    so the sum of the n elements is the smallest
    //O(n3)
    n = 3;
    vector< vector<ll> > a;
    a.assign(n, vector<ll>(n));
    for(ll i = 0;i<n;i++){
        for(ll j = 0;j<n;j++){
            a[i][j] = i+j+1;
        }
    }
    vector<ll> ans = assignment(a);
    for(ll i : ans){
        cout<<ans[i]<<' ';
    }
    cout<<endl;
    return 0;
}