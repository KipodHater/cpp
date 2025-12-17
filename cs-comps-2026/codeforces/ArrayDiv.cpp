#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int n; cin >> n;
    vector<ll> a(n);
    ll b=0;
    ll c=0;
    multiset<ll> z;
    for(ll i=0; i<n; i++) {
        cin >> a[i];
        z.insert(a[i]);
        b += a[i];
    }
    multiset<ll> s;
    if((c-b)%2 == 0 && s.find((c - b) / 2) != s.end()) {
            cout << "YES\n";
            return 0;
        }
    for(ll i=0; i<n; i++) {
        s.insert(a[i]);
        c+= a[i];
        b-=a[i];
        z.erase(z.find(a[i]));
        if((c-b)%2 == 0 && s.find((c - b) / 2) != s.end()) {
            cout << "YES\n";
            return 0;
        }
        if((b-c)%2 == 0 && z.find((b - c) / 2) != z.end()) {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";
}