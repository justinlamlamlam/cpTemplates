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
ll d[2005][2005];
void init(){
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            if(i==j){
                d[i][j]=0;
                continue;
            }
            d[i][j] = INT_MAX;
        }
    }
}
void fw(){   
    for(ll k = 0;k<n;k++){
        for(ll i = 0;i<n;i++){
            for(ll j = 0;j<n;j++){
                //if weights are non ints, if(d[i][k] + d[k][j] < d[i][j] - EPS), where EPS doubles
                if(d[i][k] < INT_MAX && d[k][j] < INT_MAX){
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }
}
void add_edge(ll s, ll t, ll weight){
    gra[s].adj.pb(make_pair(t,weight));
    gra[s].adj_cnt++;
    d[s][t] = weight;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //floyd warshall algo: finding all pairs shortest path
    //O(v3)
    n =5;
    init();
    add_edge(0,1,4);
    add_edge(1,2,3);
    add_edge(2,3,5);
    add_edge(1,4,9);
    add_edge(2,4,1);
    fw();
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            cout<<d[i][j]<<' ';
        }
        cout<<"\n";
    }
    return 0;
}