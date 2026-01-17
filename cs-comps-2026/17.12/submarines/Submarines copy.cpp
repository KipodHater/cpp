#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

struct segTree {
    ll n;
    vl seg;
    segTree(ll m) {
        for(n=1; n<m; n <<= 2);
        seg.resize(2*n, -1);
    }

    void update(ll k, ll u, ll i, ll l, ll r) {
        if(k < l || k >= r) return ;
        if(k == l && k == r-1) seg[i] = u;
        else {
            ll m = (l+r)/2;
            update(k, u, 2*i, l, m);
            update(k, u, 2*i+1, m, r);
            seg[i] = max(seg[2*i], seg[2*i+1]);
        }
    }

    void update(ll k, ll u) {
        update(k, u, 1, 0, n);
    }

    ll query(ll tl, ll tr, ll i, ll l, ll r) {
        if(tl >= r || tr < l) return -1;
        if(tl <= l && tr >= r-1) return seg[i];
        ll m = (l+r)/2;
        return max(query(tl, tr, i, l, m), query(tl, tr, i, m, r));
    }
};

vector<long long> get_amount_of_sails(int N, int Q, vector<int> D, vector<int> Y) {
    vl a(Q, 0);
    vl b(N + 1, 0);
    for(ll i=1; i<N+1; i++) b[i] = b[i-1] + i;
    for(ll i=0; i<Q; i++) {
        ll c = upper_bound(D.begin(), D.end(), Y[i]) - D.begin();
        a[i] = b[c];
    }
    return a;
}

// int main() {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);

//     int N, Q;
//     std::cin >> N >> Q;
//     std::vector<int> D(N);
//     for (int i = 0; i < N; ++i) {
//         std::cin >> D[i];
//     }
//     std::vector<int> Y(Q);
//     for (int i = 0; i < Q; ++i) {
//         std::cin >> Y[i];
//     }

//     std::vector<long long> result = get_amount_of_sails(N, Q, std::move(D), std::move(Y));
//     for (long long r : result) {
//         std::cout << r << '\n';
//     }
//     return 0;
// }
