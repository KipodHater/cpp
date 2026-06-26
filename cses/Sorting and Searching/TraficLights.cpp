#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);
    set<ll> s;
    multiset<ll> l;
    ll n, x; cin >> x >> n;
    l.insert(x);
    s.insert({0, x});

    ll p;
    for(ll i=0; i<n; i++) {
        cin >> p;
        if(s.count(p) == 0) {
            auto it = s.lower_bound(p);
            ll j = *it;
            ll k = *prev(it);
            s.insert(p);
            l.erase(l.find(j-k));
            l.insert(j-p);
            l.insert(p-k);
            cout << *prev(l.end()) << " ";
        }
    }
}