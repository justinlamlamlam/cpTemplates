#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
ll m, n;
vector< vector<ll> > t;
vector< vector<ll> > g;
void buildy(ll vx, ll lx, ll rx, ll vy, ll ly, ll ry) {
    if (ly == ry) {
        if (lx == rx)
            t[vx][vy] = g[lx][ly];
        else
            t[vx][vy] = t[vx*2][vy] + t[vx*2+1][vy];
    } else {
        ll my = (ly + ry) / 2;
        buildy(vx, lx, rx, vy*2, ly, my);
        buildy(vx, lx, rx, vy*2+1, my+1, ry);
        t[vx][vy] = t[vx][vy*2] + t[vx][vy*2+1];
    }
}
void buildx(ll vx, ll lx, ll rx) {
    if (lx != rx) {
        ll mx = (lx + rx) / 2;
        buildx(vx*2, lx, mx);
        buildx(vx*2+1, mx+1, rx);
    }
    buildy(vx, lx, rx, 1, 0, m-1);
}

ll sumy(ll vx, ll vy, ll tly, ll try_, ll ly, ll ry) {
    if (ly > ry) 
        return 0;
    if (ly == tly && try_ == ry)
        return t[vx][vy];
    ll tmy = (tly + try_) / 2;
    return sumy(vx, vy*2, tly, tmy, ly, min(ry, tmy)) + sumy(vx, vy*2+1, tmy+1, try_, max(ly, tmy+1), ry);
}
ll sumx(ll vx, ll tlx, ll trx, ll lx, ll rx, ll ly, ll ry) {
    if (lx > rx)
        return 0;
    if (lx == tlx && trx == rx)
        return sumy(vx, 1, 0, m-1, ly, ry);
    ll tmx = (tlx + trx) / 2;
    return sumx(vx*2, tlx, tmx, lx, min(rx, tmx), ly, ry) + sumx(vx*2+1, tmx+1, trx, max(lx, tmx+1), rx, ly, ry);
}
void updatey(ll vx, ll lx, ll rx, ll vy, ll ly, ll ry, ll x, ll y, ll new_val) {
    if (ly == ry) {
        if (lx == rx)
            t[vx][vy] = new_val;
        else
            t[vx][vy] = t[vx*2][vy] + t[vx*2+1][vy];
    } else {
        ll my = (ly + ry) / 2;
        if (y <= my)
            updatey(vx, lx, rx, vy*2, ly, my, x, y, new_val);
        else
            updatey(vx, lx, rx, vy*2+1, my+1, ry, x, y, new_val);
        t[vx][vy] = t[vx][vy*2] + t[vx][vy*2+1];
    }
}

void updatex(ll vx, ll lx, ll rx, ll x, ll y, ll new_val) {
    if (lx != rx) {
        ll mx = (lx + rx) / 2;
        if (x <= mx)
            updatex(vx*2, lx, mx, x, y, new_val);
        else
            updatex(vx*2+1, mx+1, rx, x, y, new_val);
    }
    updatey(vx, lx, rx, 1, 0, m-1, x, y, new_val);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //find subarray sum with indivual update query
    //Query: O(log n log m), Update O(log n log m)
    //Call ???x functions not ???y functions
    m = 5, n = 5;
    g.assign(m, vector<ll>(n));
    t.assign(m*4+1, vector<ll>(n*4+1));
    for(int i = 0;i<m;i++){
        for(int j = 0;j<n;j++){
            g[i][j] = (i+1)*j + j + 1;
        }
    }
    buildx(1, 0, m-1);
    for(int i = 0;i<m;i++){
        for(int j = 0;j<n;j++){
            g[i][j] = (i+2) * (j+2);
            updatex(1, 0, m-1, i, j, g[i][j]);
        }
    }
    cout<<"subarray sum = "<<sumx(1, 0, m-1, 0, m-1, 0, n-1)<<endl;
    
    return 0;
}