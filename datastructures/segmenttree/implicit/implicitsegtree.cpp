#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
struct vertex{
    ll left, right;
    ll sum = 0;
    vertex *leftchild = nullptr, *rightchild = nullptr;
    vertex(ll lb, ll rb){
        left = lb;
        right = rb;
    }
    void extend(){
        if(!leftchild && left + 1 < right){
            ll t = (left + right) / 2;
            leftchild = new vertex(left, t);
            rightchild = new vertex(t, right);
        }
    }
    void add(ll k, ll x){
        extend();
        sum += x;
        if(leftchild){
            if(k < leftchild->right){
                leftchild->add(k, x);
            }
            else{
                rightchild->add(k, x);
            }
        }
    }
    ll getsum(ll lq, ll rq){
        if(lq<=left && right<=rq) return sum;
        if(max(left, lq) >= min(right, rq)) return 0;
        extend();
        return leftchild->getsum(lq, rq) + rightchild->getsum(lq,rq);
    }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //not building the entire tree at first

    return 0;
}