#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e11;

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    ll n; cin >> n;
    vector<vector<pair<ll, vector<ll>>>> a (n, vector<pair<ll, vector<ll>>>(n+2, {INF, vector<ll>(0)}));
    vector<ll> c(n);
    for(ll i=0; i<n; i++) cin >> c[i];
    a[0][0] = {0, {0}};
    ll i=0;
    while(i < n) {
        ll j = i+a[0][i].second[0] + 1;
        if(j >= n) break;
        a[0][j] = {a[0][i].first + c[j], {a[0][i].second[0] + 1}};
        i = j;
    }

    for(ll i=0; i<n-1; i++) {
        for(ll j=0; j<n; j++) {
            if(a[i][j].first >= INF || a[i][j].second.size() == 0) continue;
            for(ll u : a[i][j].second) {
            ll k = j-u;
            if(k < 0 || k > n-1) continue;
            a[i+1][k].first = c[k] + a[i][j].first;
            a[i+1][k].second.push_back(u);
            }
        }
        for(ll j=0; j<n; j++) {
            if(a[i+1][j].first >= INF || a[i+1][j].second.size() == 0) continue;
            for(ll u : a[i+1][j].second) {
                ll k = j+u+1;
                if(k >= n || k < 0) continue;
                ll s = c[k] + a[i+1][j].first;
                if(s < a[i+1][k].first) {
                    a[i+1][k].first = c[k] + a[i+1][j].first; 
                    a[i+1][k].second.push_back(u + 1);
                }
            }
        }
    }

    ll res = INF;
    for(ll i=0; i<a.size(); i++) {
        res = min(res, a[i][n-1].first);
    }
    cout << res;
}