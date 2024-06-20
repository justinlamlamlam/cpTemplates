#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
ll pow(ll a, ll b, ll mod){
    if(b == 0) return 1;
    ll res = pow(a, b/2, mod);
    if(b % 2) return (((res*res)%mod)*a)%mod;
    else return (res*res)%mod;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //a/b mod m
    //reference: fermat's last theorem
    ll a = 1, b = 2, mod = 1e9+7;
    ll t = ((a % mod) * ((pow(b, mod-2, mod))) % mod);
    cout<<t<<endl;
    return 0;
}