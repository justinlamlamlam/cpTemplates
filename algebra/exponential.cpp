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
    //find a^b mod c in log b time
    ll mod = 10000007;
    for(int i = 0;i<=40;i++){
        cout<<"2 ^ "<<i<<" = "<<pow(2,i,mod)<<" mod "<<mod<<endl;
    }
    cout<<pow(4, 7, 7)<<endl;
    return 0;
}