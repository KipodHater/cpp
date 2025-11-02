#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll n; cin >> n;
    vector<ll> a(n);
    map<ll, ll> m;
    ll c=0; ll b=-1;
    for(ll i=0; i<n; i++) {
        cin >> a[i];
    }
    for(ll i=0; i<n; i++){
        if(m.count(a[i]))
            b = max(b, m[a[i]]);
        m.erase(a[i]);
        m.insert({a[i], i});
        c = max(c, i-b);
    }
    cout << c;
}