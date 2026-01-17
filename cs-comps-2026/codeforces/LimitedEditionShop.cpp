#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e10;
vector<ll> a, b;

struct Node {
    ll l, r, m;
    ll x = 0;

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

    void pull() {
        x = lp->x + rp->x;
    }

    void update(ll k, ll u) {
        if(k < l || k >= r) return ;
        if(k == l && k == r-1) x = u;
        else {
            lp->update(k, u);
            rp->update(k, u);
            pull();
        }
    }

    ll query(ll tl, ll tr) {
        if(tl >= r || tr < l) return 0;
        if(tl <= l && tr >= r-1) {
            return x;
        }
        return lp->query(tl, tr) + rp->query(tl, tr);
    }
};

int main() {
    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        ll res = 0;
        vector<ll> a(n);
        vector<ll> b(n);
        vector<ll> v(n);
        vector<pair<ll, ll>> c(n);

        for(ll i=0; i<n; i++) cin >> v[i];
        for(ll i=0; i<n; i++) cin >> a[i];
        for(ll i=0; i<n; i++) cin >> b[i];

        vector<ll> a1(n, 0);
        vector<ll> b1(n, 0);
        a1[0] = v[a[0]-1];
        b1[0] = -v[b[0]-1];
        Node *segA = new Node(0, n);
        Node *segB = new Node(0, n);
        for(ll i=0; i<n; i++) {
            a1[i] = v[a[i]-1];
            c[a[i]-1].first = i;
            segA->update(i, a1[i]);
            b1[i] = -v[b[i]-1];
            c[b[i]-1].second = i;
            segB->update(i, b1[i]);
        }
        // vector<bool> visited(n, false);
        ll i, j;
        i = 0; j = 0;
        while(i<n && j < n) {
            if(v[a[i]-1] >= 0)  {
                res += v[a[i]-1];
                v[a[i]-1] = 0;
                segA->update(a[i]-1, 0);
                segB->update(c[a[i]-1].second, 0);
                i++;
            }
            else if(v[b[j]-1] <= 0) {
                // res -= v[b[j]-1];
                v[b[j]-1] = 0;
                segA->update(c[b[j]-1].first, 0);
                segB->update(b[j]-1, 0);
                j++;
            }
            else {
                ll d = segA->query(i ,c[b[j]-1].first);
                ll e = segB->query(j, c[a[i]-1].second);
                if(segA->query(i ,c[b[j]-1].first) > segB->query(j, c[a[i]-1].second)) {
                    
                res += v[a[i]-1];
                v[a[i]-1] = 0;
                segA->update(a[i]-1, 0);
                segB->update(c[a[i]-1].second, 0);
                i++;
                } else {
                    
                // res -= v[b[j]-1];
                v[b[j]-1] = 0;
                segA->update(c[b[j]-1].first, 0);
                segB->update(b[j]-1, 0);
                j++;
                }
            }
        }
        cout << res << "\n";
    }
}