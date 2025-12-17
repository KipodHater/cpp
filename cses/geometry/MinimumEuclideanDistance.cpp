#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e10;

ll dist(ll x1, ll x2, ll y1, ll y2) {
    return (x1-x2) * (x1-x2) + (y1-y2) * (y1-y2);
}

int main() {
    std::ios_base::sync_with_stdio(0); cin.tie(NULL);
    ll n;
    cin >> n;
    vector<pair<ll, ll>> p(n);
    for(ll i=0; i<n; i++) cin >> p[i].first >> p[i].second;

    sort(p.begin(), p.end());
    ll d = dist(p[0].first, p[1].first, p[0].second, p[1].second);
    set<pair<ll, ll>> s;
    ll l, r;
    l = 0;
    r = 0;
    set<pair<ll, ll>>::iterator itr;
    ll e;
    for(ll i=0; i<n; i++) {
        e = ceil(sqrt(d));
        while(r > l) {
            if(p[i].first - e > p[l].first) {
                s.erase({p[l].second, p[l].first});
                l++;
            }
            else break;
        }
        itr = s.lower_bound({p[i].second - e, -INF});
        while(itr != s.end()) {
            if(itr->first > p[i].second + e) break;
            ll f = dist(itr->second, p[i].first, itr->first, p[i].second);
            if(f < d) {
                d = f;
                e = ceil(sqrt(d));
            }
            itr++;
        }
        s.insert({p[i].second, p[i].first});
        r = i;
    }
    cout << d;
}