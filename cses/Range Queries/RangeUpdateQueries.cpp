#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
    ll l, r, m;
    Node *rp = nullptr;
    Node *lp = nullptr;
    ll x = 0;
    ll y = 0;

    Node(ll l, ll r):l(l),r(r){
       m = (r+l)/2;
       if(l == r-1) return ;
        lp = new Node(l, m);
        rp = new Node(m, r);
    }

    void update(ll tl, ll tr, ll v) {
        if(tr<l || tl >= r) return ;
        if(tl <= l &&  r-1 <= tr) {
            y += v;
            x += v*(r-l);
        }
        else {
            push();
            lp->update(tl, tr, v);
            rp->update(tl, tr, v);
            pull();
        }
    }

    void push() {
        if(l == r-1) {
            // x += y;
            y = 0;
        } else {
            lp->y+=y;
            rp->y+=y;
            lp->x+=y*(lp->r-lp->l);
            rp->x+=y*(rp->r-rp->l);
            y=0;
        }
    }

    void pull() {
        x = lp->x + rp->x;
    }

    ll query(ll tl, ll tr){
        
        if(tr<l || tl >= r) return 0;
        if(tl <= l &&  r-1 <= tr) {
            // pull();
            return x;
        }
        else {
            // pull();
            push();
            return lp->query(tl, tr) + rp->query(tl, tr);
        }
    }
};

int main() {
    ll n, q; cin >> n >> q;
    vector<ll> a(n);
    Node *seg = new Node(0, n);
    for(ll i=0; i<n; i++){
        cin >> a[i];
        seg->update(i, i, a[i]);
    }
    while(q--){
        ll b;
        cin >> b;
        if(b == 2) {
            ll c;
            cin >> c;
            cout << seg->query(c-1, c-1) << "\n";
        }
        else {
            ll c, d, e;
            cin >> c >> d >> e;
            seg->update(c-1, d-1, e);
        }
    }
}