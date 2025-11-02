#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

std::vector<long long> choose_magic_cubes(int N, std::vector<long long> A, long long T) {
    sort(A.begin(), A.end());
    set<pair<ll, ll>> s;
    map<ll, ll> b;
    map<pair<ll, ll>, pair<ll, ll>> c;
    map<ll, pair<ll, ll>> m;
    for(ll i:A) {
        s.insert({i, b[i]});
        c[{i, b[i]}] = {i, 1};
        m[i] = {i, 1};
        b[i]++;
    }
    while(s.size() > 1) {
        pair<ll, ll> cur = *s.begin();
        s.erase(cur);
        for(ll j=0; j<s.size(); j++){
            auto it = next(s.begin(), j);
            ll c = cur.first * (*it).first;
            ll num = cur.second + (*it).second;
            if()
            if(m[cur].second )
        }
    }
    return {};
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    long long T;
    if (!(std::cin >> N >> T)) return 0;
    std::vector<long long> A(N);
    for (int i = 0; i < N; ++i) std::cin >> A[i];

    std::vector<long long> ans = choose_magic_cubes(N, A, T);
    if (ans.empty()) {
        std::cout << "Impossible\n";
    } else {
        std::cout << ans.size() << '\n';
        for (size_t i = 0; i < ans.size(); ++i) {
            if (i) std::cout << ' ';
            std::cout << ans[i];
        }
        std::cout << '\n';
    }
    return 0;
}
