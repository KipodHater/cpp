#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
const ll INF = -1e10;

struct LazySeg {
    ll n;
    vector<pair<ll, ll>> seg;
    vector<pair<ll, ll>> segM;
    vl add;
    LazySeg(ll m) {
        for(n=1; n<m; n<<=1);
        seg.resize(2*n, {0, 0});
        segM.resize(2*n, {0, 0});
        add.resize(2*n, 0);
    }

    void push(ll i) {
        add[2*i] += add[i];
        add[2*i+1] += add[i];
        seg[2*i].first += add[i];
        seg[2*i+1].first += add[i];
        segM[2*i].first += add[i];
        segM[2*i+1].first += add[i];
        add[i] = 0;
    }

    void pull(ll i) {
        seg[i] = max(seg[2*i], seg[2*i+1]);
        segM[i] = min(segM[2*i], segM[2*i+1]);
    }

    void update(ll tl, ll tr, ll val, ll i, ll l, ll r) {
        if(tl >= r || tr < l) return ;
        if(tl <= l && tr >= r-1) {
            add[i] += val;
            seg[i].first += val;
            segM[i].first += val;
            return ;
        }
        push(i);
        ll m = (r+l)/2;
        update(tl, tr, val, 2*i, l, m);
        update(tl, tr, val, 2*i+1, m, r);
        pull(i);
    }

    void update(ll tl, ll tr, ll val) {
        update(tl, tr, val, 1, 0, n);
    }

    pair<pair<ll, ll>, pair<ll, ll>> query(ll tl, ll tr, ll i, ll l, ll r) {
        if(tl >= r || tr < l) return {{INF, 0}, {-INF, 0}};
        if(tl <= l && tr >= r-1) return {segM[i], seg[i]};
        push(i);
        pull(i);
        ll m = (r+l)/2;
        auto q1 = query(tl, tr, 2*i, l, m);
        auto q2 = query(tl, tr, 2*i+1, m, r);
        return {max(q1.first, q2.first), min(q1.second, q2.second)};
    }

    pair<pair<ll, ll>, pair<ll, ll>> query(ll tl, ll tr) {
        return query(tl, tr, 1, 0, n);
    }
};

int main() {
    ll n; 
    LazySeg s = 
}