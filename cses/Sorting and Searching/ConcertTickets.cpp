#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll n, m, a;
    cin >> n >> m;
    // vector<ll> a(n);
    multiset<ll> s;
    vector<ll> b(m);
    vector<ll> c(m, -1);
    for(ll i=0; i<n; i++) {
        cin >> a;
        s.insert(-a);
    }
    s.insert(0);
    for(ll i=0; i<m; i++) {
        cin >> b[i];
    }

    // sort(a.begin(), a.end());

    for(ll i=0; i<m; i++){
        ll d = *s.lower_bound(-b[i]);
        if(d == 0) {
            cout << -1 << "\n";
        } else{
        s.erase(s.find(d));
        cout << -d << "\n";
        }
    }
}