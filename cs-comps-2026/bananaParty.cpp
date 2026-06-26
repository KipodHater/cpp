#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    ll n; cin >> n;
    vector<ll> h(n);
    for(ll i=0; i<n; i++) cin >> h[i];
    vector<vector<ll>> a(1000000);
    for(ll i=0; i<n; i++) {
        a[h[i]].push_back(i);
    }
    ll res = a[a.size()-1].size();
    for(ll i=a.size()-2; i>=0; i--) {
        ll j = 0;
        ll k = 0;
        while(j<a[i].size() && k < a[i+1].size()) {
            if(a[i][j] > a[i+1][k]) {
                j++;
                k++;
                continue;
            }
            j++;
            res++;
        }
        // if(k + 1 == a[i+1].size()) {
        if(a[i].size() != 0)res += a[i].size() - j;
        
    }
    cout << res;
}