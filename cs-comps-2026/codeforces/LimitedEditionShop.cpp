#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e10;
vector<ll> a, b;

struct Node {
    ll l, r, m;
    ll x = 0;
    ll plus = 0;

    Node *lp = nullptr;
    Node *rp = nullptr;

    Node(ll l, ll r):l(l),r(r) {
        m = (l + r)/2;

        if(l == r-1) {
            // x = a[l];
            return ;
        }
        lp = new Node(l, m);
        rp = new Node(m, r);
    }

    void push() {
        lp->update(lp->l, lp->r - 1, plus);
        rp->update(rp->l, rp->r - 1, plus);
        plus = 0;
    }

    void pull() {
        x = max(lp->x, rp->x);
    }

    void update(ll tl, ll tr, ll val) {
        if(tl >= r || tr <= l) return ;
        if(tl <= l && tr >= r-1) {
            plus += val;
            x += val;
            return ;
        }
        push();
        lp->update(tl, tr, val);
        rp->update(tl, tr, val);
        pull();
    }

    ll query(ll tl, ll tr) {
        if(tl >= r || tr <= l) return -INF;
        if(tl <= l && tr >= r-1) {
            return x;
        }
        push();
        pull();
        return max(lp->query(tl, tr), rp->query(tl, tr));
    }
};

int main() {
    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<ll> a(n);
        vector<ll> b(n);
        vector<ll> v(n);

        for(ll i=0; i<n; i++) cin >> v[i];
        for(ll i=0; i<n; i++) cin >> a[i];
        for(ll i=0; i<n; i++) cin >> b[i];

        vector<ll> a1(n, 0);
        vector<ll> b1(n, 0);
        a1[0] = v[a[0]];
        b1[0] = -v[b[0]];
        Node *segA = new Node(0, n);
        segA->update(0, 1, a1[0]);
        Node *segB = new Node(0, n);
        segB->update(0, 1, b1[0]);
        for(ll i=0; i<n; i++) {
            a1[i] = a1[i-1] + v[a[i]];
            segA->update(i, i+1, a1[i]);
            b1[i] = b1[i-1] - v[b[i]];
            segA->update(i, i+1, b1[i]);
        }

    }
}