#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<pair<ll, ll>> a;

struct MyHash {
    size_t operator()(const pair<ll, ll>& p) const {
        return hash<ll>()(p.first + 1000LL * p.second);
    }
};

map<pair<ll, ll>, ll> memo;

ll combinations(ll i, ll j) {
    if(i+1 == j) return (a[i].first == 0 && a[i].second == 0) ? 1 : 0;
    
    auto key = make_pair(i, j);
    if(memo.count(key)) return memo[key];
    
    ll sum = 0;
    ll mid = (i+j)/2;
    sum += (combinations(i, mid) + 1) * (combinations(mid, j) + 1) - 1;
    
    unordered_multiset<pair<ll, ll>, MyHash> s;
    for(ll b = 1; b < (1 << (j - mid)); b++){
        pair<ll, ll> c = {0, 0};
        ll d = mid;
        for(ll e=b; e > 0; e >>= 1) {
            c.first += e & 1 ? a[d].first : 0;
            c.second += e & 1 ? a[d].second : 0;
            d++;
        }
        if(c.first != 0 || c.second != 0) s.insert(c);
    }
    
    for(ll b = 1; b < (1 << (mid - i)); b++){
        pair<ll, ll> c = {0, 0};
        ll d = i;
        for(ll e=b; e > 0; e >>= 1) {
            c.first -= e & 1 ? a[d].first : 0;
            c.second -= e & 1 ? a[d].second : 0;
            d++;
        }
        if(c.first != 0 || c.second != 0) sum += s.count(c);
    }
    
    return memo[key] = sum;
}

int main() {
    ll n; cin >> n;
    a.resize(n);
    for(ll i=0; i<n; i++) cin >> a[i].first >> a[i].second;
    cout << combinations(0, n);
}