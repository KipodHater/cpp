#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    map<ll, ll> m;
    ll n; cin >> n;
    vector<ll> a(n);
    for(ll i=0; i<n; i++) cin >> a[i];
    for(ll i:a) m[i] = -1;
    vector<ll> b(n);
    b[0] = 1;
    m[a[0]] = 0;
    for(ll i=1; i<n; i++) {
        b[i] = min(b[i-1]+1, i - m[a[i]]);
        m[a[i]] = i;
    }
    ll s = 0;
    for(ll i:b) s+= i;
    cout << s;
}