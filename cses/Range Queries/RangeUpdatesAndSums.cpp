#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

struct LazySeg {
    ll n;
    vl seg, lazySet, lazyAdd;
    LazySeg(ll m) {
        for(n = 1; n < m; n<<=1);
        seg.resize(n* 2);
        lazySet.resize(n * 2, -1);
        lazyAdd.resize(n * 2, 0);
    }

    void pull(ll i) {
        seg[i] = seg[2*i] + seg[2*i+1];
    }
    
    void push(ll i, ll l, ll r) {
        ll m = (r+l)/2;
        if(l == r-1) return ;
        if(lazySet[i] != -1) {
            lazySet[2 * i] = lazySet[2*i+1] = lazySet[i];
            lazyAdd[2*i] = lazyAdd[2*i+1] = 0;
            seg[2*i] = (m-l) * lazySet[i];
            seg[2*i+1] = (r-m) * lazySet[i];
            lazySet[i] = -1;
        }
        lazyAdd[2*i] += lazyAdd[i];
        lazyAdd[2*i+1] += lazyAdd[i];
        seg[2*i] += (m-l) * lazyAdd[i];
        seg[2*i+1] += (r-m) * lazyAdd[i];
        lazyAdd[i] = 0;
    }

    void update(ll tl, ll tr, ll add, ll se, ll i, ll l, ll r) {
        ll m = (r+l)/2;
        if(tl >= r || tr < l) return ;
        if(tl <= l && tr >= r-1) {
            if(se != -1) {
                lazySet[i] = se;
                lazyAdd[i] = 0;
                seg[i] = (r-l) * se;
            }
            lazyAdd[i] += add;
            seg[i] += add * (r-l);
            return ;
        }
        push(i, l, r);
        update(tl, tr, add, se, i * 2, l, m);
        update(tl, tr, add, se, i * 2+1, m, r);
        pull(i);
    }

    void update(ll tl, ll tr, ll add, ll se) {
        update(tl, tr, add, se, 1, 0, n);
    }

    ll query(ll tl, ll tr, ll i, ll l, ll r) {
        if(tl >= r || tr < l) return 0;
        if(tl <= l && tr >= r-1) {
        return seg[i];
        }
        push(i, l, r);
        pull(i);
        ll m = (r+l)/2;
        return query(tl, tr, i*2, l, m) + 
                query(tl, tr, i*2+1, m, r);
    }

    ll query(ll tl, ll tr) {
        return query(tl, tr, 1, 0, n);
    }
};

int main() {
    ll n, t; cin >> n >> t;
    vl a(n);
    LazySeg *s = new LazySeg(n);
    ll b, c, d, e;
    for(ll i=0; i<n; i++) cin >> a[i];
        for(ll i=0; i<n; i++) s->update(i, i, 0, a[i]);
    while(t--) {
        cin >> b;
        if(b == 1){
            cin >> c >> d >> e;
            s->update(c-1, d-1, e, -1);
        } else if(b == 2) {
            cin >> c >> d >> e;
            s->update(c-1, d-1, 0, e);
        } else {
            cin >> c >> d;
            cout << s->query(c-1, d-1) << "\n";
        }
    }
}