#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

int main(){
    multiset<ll> s;
    ll n; cin >> n;
    vector<ll> a(n);
    for(ll i=0; i<n; i++) cin >> a[i];
    ll b = 0;
    s.insert(-1);
    // ll c = 1e10;
    for(ll i : a) {
        if(*(--s.end()) <= i) s.insert(i);
        else {
        ll j = *s.upper_bound(i);
        s.extract(j);
        s.insert(i);
        }
    }
    cout << s.size()-1;
}