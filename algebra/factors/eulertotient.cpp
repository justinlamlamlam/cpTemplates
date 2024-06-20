#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
vector<int> phi;
void eulertotientarr(ll n){
    //find euler totient for ints from 1 to n
    //O(n log log n)
    phi.resize(n+1);
    for(int i = 0;i<=n;i++){
        phi[i] = i;
    }
    for(int i = 2;i<=n;i++){
        if(phi[i] == i){
            for(int j = i;j<=n;j+=i){
                phi[j] -= phi[j]/i;
            }
        }
    }
}
int eulertotient(ll x){
    //O(sqrt x)
    ll result = x;
    for(int i = 2;i*i<=x;i++){
        if(x%i==0){
            while(x%i==0) x/=i;
            result -= result/i;
        }
    }
    if(x>1) result -= result/x;
    return result;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    n = 100;
    eulertotientarr(n);
    for(int i = 0;i<=100;i++) cout<<i<<" "<<phi[i]<<" "<<eulertotient(i)<<"\n";
    cout<<endl;
    return 0;
}