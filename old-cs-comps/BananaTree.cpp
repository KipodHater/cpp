#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main (){
    ll n, m;

    cin >> n >> m;

    vector<ll> b(n+1);
    b[0] = 0;
    for(ll i=1; i<n+1; i++) cin >> b[i];
    for(ll i=0; i<=n; i++) b[i] = b[i] - i*m;

    vector<ll> a(n+1, -1e11);
    a[0] = 0;

    ll c=0;
    for(ll i=1; i<=n; i++){
        if(b[i]>0) continue;
        ll j = upper_bound(a.begin(), a.end(), b[i], greater<>()) - a.begin();
        a[j] = b[i];

        c = max(j, c);
    }

    cout << n-c;
}