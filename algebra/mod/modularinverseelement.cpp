#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
vector<int> phi;
ll pow(ll a, ll b, ll mod){
    if(b == 0) return 1;
    ll res = pow(a, b/2, mod);
    if(b % 2) return (((res*res)%mod)*a)%mod;
    else return (res*res)%mod;
}
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
int modinverse(ll x, ll m){
    //x and m has to be coprime
    if(__gcd(x,m)!=1) return -1;
    if(m==1) return -1;
    return eulertotient(m);
}
ll modinvelem(ll a, ll b, ll m){
    ll g = __gcd(a,m);
    a = a/g;
    m = m/g;
    return b*modinverse(a,m);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //find modular inverse element of a and b (a*? = b mod M)
    //idk right or wrong
    ll n;
    n = 10;
    for(int i = 1;i<=n;i++){
        for(int j = 2;j<=10;j++){
            cout<<i<<" "<<j<<" "<<modinvelem(i,j,10)<<(i*modinvelem(i,j,10))%10<<"\n";
        }
    }
    return 0;
}