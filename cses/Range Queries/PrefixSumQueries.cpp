#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
const ll INF = 1e10;

struct LazySeg {
    ll n;
    vl seg;
    vl add;
    LazySeg(ll m) {
        for(n=1; n<m; n<<=1);
        seg.resize(2*n, -INF);
        add.resize(2*n, 0);
    }

    void push(ll i) {
        add[2*i] += add[i];
        add[2*i+1] += add[i];
        seg[2*i] += add[i];
        seg[2*i+1] += add[i];
        add[i] = 0;
    }

    void pull(ll i) {
        seg[i] = max(seg[2*i], seg[2*i+1]);
    }

    void update(ll tl, ll tr, ll val, ll i, ll l, ll r) {
        if(tl >= r || tr < l) return ;
        if(tl <=l && tr >= r-1) {
            add[i] += val;
            seg[i] += val;
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

    ll query(ll tl, ll tr, ll i, ll l, ll r) {
        if(tl >= r || tr < l) return -INF;
        if(tl <= l && tr >= r-1) return seg[i];
        push(i);
        pull(i);
        ll m = (l+r)/2;
        return max(query(tl, tr, 2*i, l, m), query(tl, tr, 2*i+1, m, r));
    }
    ll query(ll tl, ll tr) {
        return query(tl, tr, 1, 0, n);
    }
};

int main() {
    ll n, q; cin >> n >> q;
    vl a(n);
    for(ll i=0; i<n; i++) cin >> a[i];
    vl b(n, 0);
    b[0] = a[0];
    LazySeg *s = new LazySeg(n);
    s->update(0, 0, a[0]);
    for(ll i=1; i<n; i++) {
        b[i] = b[i-1] + a[i];
        s->update(0, i, a[i]);
    }
    ll c, d, e;
    while(q--) {
        cin >> c >> d >> e;
        if(c == 1) {
            ll f = e - a[d-1];
            s->update(d-1, n-1, f);
        } else {
            ll res = s->query(d, e);
            if(res < 0) res = 0;
            else if(d > 0) res -= s->query(d-1, d-1);
            
            cout << res << "\n";
        }
    }
}