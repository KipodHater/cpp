#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
    ll l, r, m;
    ll x = 0;
    Node *lp;
    Node *rp;

    Node(ll l, ll r):l(l), r(r) {
        m = (l + r) / 2;

        if(l == r-1) return ;
        lp = new Node(l, m);
        rp = new Node(m, r);
    }

    void pull() {
        x = max(lp->x, rp->x);
    }

    ll query(ll tl, ll tr) {
        if(tl >= r || tr < l) return 0;
        if(tl <= l && tr >= r-1) return x;
        return max(rp->query(tl, tr), lp->query(tl, tr));
    }

    void update(ll k, ll val) {
        if(l > k || k >= r) return ;
        if(l == k && k == r-1) x = val;
        else {
            rp->update(k, val);
            lp->update(k, val);
            pull();
        }
    }
};

long long presentation(int N, std::vector<std::pair<int, int>> V) {
    sort(V.begin(), V.end(), greater<>());
    vector<ll> y;
    for(auto u : V) y.push_back(u.second);
    sort(y.begin(), y.end());
    y.erase(unique(y.begin(), y.end()), y.end());
    Node *seg = new Node(0, V.size());
    // seg->query(0, -1);

    for(ll i=0; i<N; i++) {
        if(i > 0) if(V[i] == V[i-1]) continue;
        auto u = V[i];
        ll j = lower_bound(y.begin(),y.end(), u.second)-y.begin();
        seg->update(j, seg->query(0, j) + u.second);
    }
    return seg->query(0, N);
}