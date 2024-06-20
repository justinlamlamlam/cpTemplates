#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
vector<bool> isprime;
vector<int> primes;
void sieve(ll n){
    isprime.assign(n, true);
    isprime[0] = isprime[1] = false;
    for(int i = 2;i<=n;i++){
        if(isprime[i] && (ll)i*i<=n){
            for(int j = i*i;j<=n;j+=i) isprime[j] = false;
        }
    }
    for(int i = 2;i<=n;i++){
        if(isprime[i]) primes.pb(i);
    }
}
vector<ll> factorization(ll n){
    vector<ll> ans;
    for(ll d : primes){
        if(d*d > n) break;
        while(n%d==0){
            ans.pb(d);
            n/=d;
        }
    }
    if(n>1) ans.pb(n);
    return ans;
}
ll numofdivisors(ll x){
    //sieve before using
    vector<ll> p = factorization(x);
    ll ans = 1;
    ll cnt = 0;
    ll cur = 0;
    for(int i : p){
        if(i!=cur){
            ans *= (cnt+1);
            cnt = 1;
            cur = i;
        }
        else cnt++;
    }
    ans *= (cnt+1);
    return ans;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve(105);
    for(int i = 2;i<=100;i++) cout<<i<<": "<<numofdivisors(i)<<endl;
    return 0;
}