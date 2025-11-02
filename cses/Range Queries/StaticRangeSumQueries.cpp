#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    ll n, q; cin >> n >> q;
    vector<ll> a(n+1);
    a[0] = 0;
    for(ll i=1; i<n+1; i++) cin >> a[i];
    for(ll i=1; i<n+1; i++) a[i] += a[i-1];
    ll l, r;
    while(q--) {
        cin >> l >> r;
        cout << a[r] - a[l-1] << "\n";
    }
}