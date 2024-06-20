#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
struct node{
    bool visited=false;
    ll key;
    ll chi_cnt;
    vector<ll> chi;
};
ll n;
node gra[200005];
vector<ll> par;
vector<ll> colour;
ll cycles, cyclet;
vector<ll> cycle;
bool dfs(ll v){
    colour[v] = 1;
    for(int i : gra[v].chi){
        if(colour[i] == 0){
            par[i] = v;
            if(dfs(i)){
                return true;
            }
        }
        else if(colour[i] == 1){
            cyclet = v;
            cycles = i;
            return true;
        }
    }
    colour[v] = 2;
    return false;
}
bool findcycle(){
    colour.assign(n,0);
    par.assign(n,-1);
    cycles = -1;
    for(int i = 0;i<n;i++){
        if(colour[i] == 0 && dfs(i)){
            break;
        }
    }
    if(cycles == -1){
        return false;
    }
    cycle.pb(cycles);
    for(int v = cyclet; v!=cycles;v = par[v]){
        cycle.pb(v);
    }
    reverse(cycle.begin(), cycle.end());
    return true;
}
void add_edge(ll s, ll t){
    gra[s].chi.pb(t);
    gra[s].chi_cnt++;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    n =5;
    add_edge(0,1);
    add_edge(1,2);
    add_edge(2,3);
    add_edge(1,4);
    add_edge(4,0);
    bool hc = findcycle();
    if(hc){
        cout<<"yes"<<endl;
        for(ll v : cycle){
            cout<<v<<' ';
        }
        cout<<endl;
    }
    else{
        cout<<"NO"<<endl;
    }
    return 0;
}