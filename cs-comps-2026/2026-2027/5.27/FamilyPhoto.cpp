#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    ll n; cin >> n;
    vector<ll> a(n); for(int i=0; i<n; i++) cin >> a[i];
    vector<ll> b; b = a;
    sort(b.begin(), b.end());
    if(n == 2) {
        if(a[0] <= a[1]) cout << 0;
        else cout << 1;
        return 0;
    }
    ll c = -1;
    ll d = 0;
    for(ll i=0; i<n; i++) {
        if(a[i] != b[i]) {
            d++;
            // if(a[i+1] == b[i]) {
            //     c = i;
            //     break;
            // }
        }
    }
    if(c == -1) c = n-1;
    // if(c == n-1 && a[n-1] == b[n-1]) {
    //     cout << 0; return 0;
    // }
    cout << d - 1;
}