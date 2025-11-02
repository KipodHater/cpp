#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll n;
    cin >> n;
    vector<ll> a(n);
    for(ll i=0; i<n; i++) cin >> a[i];
    vector<ll> b(n+1, 1e10);
    b[0] = 0;
    ll m=0;
    for(ll i=0; i<n; i++){
        ll low = lower_bound(b.begin(), b.end(), a[i]) - b.begin();

        b[low] = a[i];
        m = max(low, m);
    }
    cout << m;
}