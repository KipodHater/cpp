#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

struct Seg {
    int n, m;
    vl seg;

    Seg(int x) {
        m = x;
        for(n = 1; n<m; n<<=1);
        seg.resize(2*n, 1);
        for(int i=n-1; i>0; i--) {
            seg[i] = seg[2*i] + seg[2*i+1];
        }
    }

    ll query(ll tl, ll tr, ll val, ll i, ll l, ll r) {
        if(tl >= r || tr <= l) return 0;
        if(tl >= l && tr <= r-1) return seg[i];
        ll m = (r+l)/2;
        return query(tl, tr, val, 2*i, l, m) + query(tl, tr, val, 2*i+1, m, r);
    }

    ll remove(ll index, ll i, ll l, ll r, ll sum) {
        if(l == r-1 && seg[i] == 1) {
            seg[i] = 0;
            return i-n;
        }
        if(l == r-1) return -1;
        seg[i]--;
        if(seg[2*i] + sum >= index && seg[2*i] != 0) {
            return remove(index, 2*i, l, (l+r)/2, sum);
        }
        else {
            return remove(index, 2*i+1, (l+r)/2, r, sum + seg[2*i]);
        }
    }

    ll remove(ll index) {
        return remove(index, 1, 0, n, 0);
    }
};

int main() {
    ll n; cin >> n;
    vl a(n); for(ll i=0; i<n; i++) cin >> a[i];
    vl b(n); for(ll i=0; i<n; i++) cin >> b[i];

    Seg *s = new Seg(n);

    for(ll c:b) {
        cout << a[s->remove(c)] << " ";
    }
}