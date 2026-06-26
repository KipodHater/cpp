#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e10;

int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    ll n, k; cin >> n >> k;
    vector<ll> b(n); for(ll i=0; i<n; i++) cin >> b[i];
    vector<vector<ll>> a(k, vector<ll>(n));
    sort(b.begin(), b.end());
    ll m;
    for(ll i=0; i<k; i++) {
        for(ll j=i+1; j<n; j++) {
            if(i == 0) {
                a[i][j] = ceil((b[j] - b[0])/2.0);
            }
            // } else if(i >= j) {
            //     a[i][j] = 0;
            // } 
            else {
                m = INF;
                ll l = i;
                ll r = j+1;
                ll mid =0;
                while (l < r) {
                    mid = (l+r) / 2;
                    m = min(m, max(a[i-1][mid], (ll) ceil((b[j] - b[mid+1]) / 2.0)));
                    if (a[i-1][mid] > ceil((b[j] - b[mid+1]) / 2.0)) {
                        r = mid;
                    } else {
                        l = mid+1;
                    }
                }

                // for(ll f = i; f<j; f++) {
                //     m = min(max(a[i-1][f], (ll) ceil((b[j] - b[f+1]) / 2.0)), m);
                // }
                a[i][j] = m;
            }
        }
    }
    cout << a[k-1][n-1]; 
}