#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
ll gcdext(ll a, ll b, ll &x, ll &y){
    x = 1, y = 0;
    ll x1 = 0, y1 = 1, a1 = a, b1 = b;
    while(b1){
        ll q = a1/b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //solving ax + by = gcd(a,b)
    ll a = 4, b = 5, x, y;
    ll gcd = gcdext(a, b, x, y);
    cout<<"gcd("<<a<<","<<b<<") = "<<gcd<<" = "<<a<<" * "<<x<<" + "<<b<<" * "<<y<<endl;
    return 0;
}