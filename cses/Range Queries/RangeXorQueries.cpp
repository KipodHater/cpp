#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> a;

struct Node {
    ll l, r, m;
    ll x = 0;
    Node *lp = nullptr;
    Node *rp = nullptr;

    Node(ll l, ll r):l(l),r(r){
        m = (l+r)/2;
        if(l == r-1) {
            return ;
        }
        else {
            lp = new Node(l, m);
            rp = new Node(m, r);
        }
    }

    void update(ll k, ll u) {
        if(k < l || k >= r) return ;
        if(k == l && k == r-1) {
            x = u;
            return ;
        }
        lp->update(k, u);
        rp->update(k, u);

        pull();
    }

    void pull() {
        x = (lp->x) ^ (rp->x);
    }

    ll query(ll tl, ll tr) {
        if(tr < l || tl >= r) return 0;
        if(tl <= l && tr >= r-1) return x;
        return (lp->query(tl, tr)) ^ (rp->query(tl, tr));
    }
};

int main() {
    ll n, q;
    cin >> n >> q;
    a.resize(n);
    for(ll i=0; i<n; i++) cin >> a[i];

    Node *seg = new Node(0, n);
    for(ll i=0; i<n; i++) seg->update(i, a[i]);

    ll b, c;
    while(q--) {
        cin >> b >> c;
        cout << seg->query(b-1, c-1) << "\n";
    }
}