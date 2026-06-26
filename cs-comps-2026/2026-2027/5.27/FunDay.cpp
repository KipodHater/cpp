#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e10;
int main(){
    ll n; cin >> n;
    vector<ll> a(n);
    ll m = INF;
    ll s = 0;
    for(int i =0; i<n; i++) {
        cin >> a[i];
        m = min(m, a[i]);
        s += a[i];
    }
    cout << s + m * (n-2);
}