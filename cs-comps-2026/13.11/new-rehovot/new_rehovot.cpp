#include "new_rehovot.h"
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e10;

vector<vector<pair<ll, ll>>> b, c;

struct Node {
    ll l, r, m;
    pair<ll, ll> x;
    ll sum = 0;
    Node *lp = nullptr;
    Node *rp = nullptr;

    Node(ll l, ll r):l(l), r(r) {
        m = (l+r)/2;

        if(l == r-1) return ;
        lp = new Node(l, m);
        rp = new Node(m, r);
    }

    void pull() {
        x = max(lp->x, rp->x);
        sum = lp->sum + rp-> sum;
    }

    void update(ll k, ll u) {
        if(k < l  || k >= r) return ;
        if(k == l && k == r-1) {
            x = {u, k};
            sum = u;
        }
        else {
        lp->update(k, u); 
        rp->update(k, u); 
        pull();
        }
    }

    pair<ll, ll> query(ll tl, ll tr) {
        if(tr < l || tl >= r) return {0, 0};
        if(tl <= l && tr >= r-1) return x;
        return max(lp->query(tl, tr), rp->query(tl, tr));
    }

    ll sumQuery(ll tl, ll tr) {
        if(tr < l || tl >= r) return 0;
        if(tl <= l && tr >= r-1) return sum;
        return lp->sumQuery(tl, tr) + rp->sumQuery(tl, tr);
    }
};


Node* seg;

void init(int N, int Q, vector<int> H) {
    seg = new Node(0, N);
    b.resize(N);
    c.resize(N);
    for(ll i=0; i<N; i++) seg->update(i, H[i]);

    make_pair(1, 2);
    for(ll i=N-2; i>=0; i--) {
        b[i].push_back(make_pair((H[i+1] > H[i]) ? (H[i+1]- H[i]) : 0, max(H[i], H[i+1])));
        for(ll j=1; 2*j+i<N; j*=2) {
            ll val;
            if(b[i][b[i].size()-1].second >= b[i+j][b[i].size()-1].second) val = b[i][b[i].size()-1].first + b[i+j][b[i].size()-1].first;
            else val = b[i+j][b[i].size()-1].first + (b[i+j][b[i].size()-1].second - b[i][b[i].size()-1].second) * j + b[i][b[i].size()-1].first;
            b[i].push_back({val, max(b[i+j][b[i].size()-1].second, b[i][b[i].size()-1].second)});
        }
    }
    // for(ll i=1; i<N; i++) {
    //     c[i].push_back((H[i-1] > H[i]) ? (H[i-1]- H[i]) : 0);
    //     for(ll j=1; i-j*2>=0; j*=2) {
    //         c[i].push_back(c[i][c[i].size()-1] + c[i-j][c[i].size()-1]);
    //     }
    // }
    for(ll i=1; i<N; i++) {
        c[i].push_back(make_pair((H[i-1] > H[i]) ? (H[i-1]- H[i]) : 0, max(H[i], H[i-1])));
        for(ll j=1; i-2*j>=0; j*=2) {
            ll val;
            if(c[i][c[i].size()-1].second >= c[i-j][c[i].size()-1].second) val = c[i][c[i].size()-1].first + c[i-j][c[i].size()-1].first;
            else val = c[i-j][c[i].size()-1].first + (c[i-j][c[i].size()-1].second - c[i][c[i].size()-1].second) * j + c[i][c[i].size()-1].first;
            c[i].push_back({val, max(c[i-j][c[i].size()-1].second, c[i][c[i].size()-1].second)});
        }
    }
}

long long build_new_rehovot(int L, int R) {
    // TODO: implement this function.
    pair<ll, ll> d = seg->query(L, R);
    ll i = R;
    ll m = 0;
    ll s = 0;
    for(ll j = 19; j>=0; j--) {
        if(i - d.second -1< 1<<j) continue;
        ll e = b[i-(1<<j)][j].first;
        if(b[i-(1<<j)][j].second >= m) s+= e;
        else s += (m - b[i-(1<<j)][j].second)*(1<<j) + e;
        m = max(m, b[i-(1<<j)][j].second);
        i -= 1 << j;
    }

    i = L;
    m = 0;
    for(ll j = 19; j>=0; j--) {
        if(d.second-i -1 < 1<<j) continue;
        ll e = c[i + (1 << j)][j].first;
        if(c[i + (1 << j)][j].second >= m) s+= e;
        else s += e + (m -c[i + (1 << j)][j].second)  *(1<<j);
        // s += c[i + (1 << j)][j].first;
        m = max(m, c[i + (1 << j)][j].second);
        i += 1 << j;
    }
    
    return s;
}
