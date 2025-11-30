#include "new_rehovot.h"
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e10;

struct Node {
    ll l, r, m;
    ll x = INF;
    Node *lp;
    Node *rp;

    Node(ll l, ll r):l(l), r(r) {
        m = (l+r)/2;

        if(l == r-1) return ;
        lp = new Node(l, m);
        rp = new Node(m, r);
    }

    void pull() {
        x = max(lp->x, rp->x);
    }

    void update(ll k, ll u) {
        if(k < l  || k >= r) return ;
        if(k == l && k == r-1) x = u;
        lp->update(k, u); 
        rp->update(k, u); 
        pull();
    }

    ll query(ll tl, ll tr) {
        if(tr < l || tl >= r) return INF;
        if(tl <= l && tr >= r-1) return x;
        return max(lp->query(tl, tr), rp->query(tl, tr));
    }
};

void init(int N, int Q, vector<int> H) {
    // TODO: implement this function.
}

long long build_new_rehovot(int L, int R) {
    // TODO: implement this function.
    return 0;
}
