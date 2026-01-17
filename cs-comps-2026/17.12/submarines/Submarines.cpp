#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
const ll SIZE = 1e6+1;

vector<long long> get_amount_of_sails(int N, int Q, vector<int> D, vector<int> Y) {
    vl a(Q, 0);
    vl b(N + 1, 0);
    set<ll> s2;
    for(ll u: Y) s2.insert(-u);
    for(ll i=1; i<N+1; i++) b[i] = b[i-1] + i;
    vl dic(SIZE+1, b[N]);
    vl c(N+1, -1);
    set<ll> s;
    s.insert(1);
    vector<vl> v(SIZE+1, vl(0));
    vl dp(SIZE+1, -1);
    dp[0] = N;
    for(ll i =0; i<N; i++) {
        v[D[i]].push_back(i);
    }
    dic[SIZE] = b[N];
    ll x = b[N];
    for(ll i : s2) {
        i *= -1;
        if(v[i].size() == 0) {
            dic[i] = dic[i+1];
        }
        for(ll j=0; j<v[i].size(); j++) {
            auto itr = s.lower_bound(v[i][j]+2);
            itr = prev(itr);
            ll z = *itr -1;
            ll diff = v[i][j] - (z);
            x -= b[dp[z]]; // here out of bounds
            dp[v[i][j]+1] = dp[z] - diff - 1;
            dp[z] = diff;
            x += b[dp[v[i][j]+1]] + b[dp[z]];
            s.insert(v[i][j]+ 2); // also follow what im changing!
        }
        dic[i] = x;
    }
    ll m = 10000000000;
    for(ll i = SIZE-1; i>=0; i--) {
        if(dic[i] != -1) m = min(m, dic[i]);
        dic[i] = m;
    }
    for(ll i=0; i<Q; i++) {
        a[i] = dic[Y[i]];
    }
    return a;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> D(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> D[i];
    }
    std::vector<int> Y(Q);
    for (int i = 0; i < Q; ++i) {
        std::cin >> Y[i];
    }

    std::vector<long long> result = get_amount_of_sails(N, Q, std::move(D), std::move(Y));
    for (long long r : result) {
        std::cout << r << '\n';
    }
    return 0;
}
