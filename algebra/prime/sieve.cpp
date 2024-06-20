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
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n = 1000;
    sieve(n);
    for(int i : primes) cout<<i<<" ";
    cout<<endl;
    return 0;
}