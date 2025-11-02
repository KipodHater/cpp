#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<pair<ll, ll>> a;

ll combinations(ll i, ll j) { // [i, j)
    if(i >= j) return 0;
    if(i+1 == j) return (a[i].first == 0 && a[i].second == 0) ? 1 : 0;
    ll sum = 0;
    sum += (combinations(i, (i+j)/2) + 1) * (combinations((i+j)/2, j) + 1) - 1;
    // vector<vector<short>> s((j - (i+j)/2) * 20, vector<short>((j - (i+j)/2) * 20, 0));
    map<pair<ll, ll>, ll> m;
    for(ll b = 1; b< (1 << (j - (i+j)/2)); b++){
        pair<ll, ll> c = {0, 0};
        ll d = (i+j)/2;
        for(ll e=b; e > 0; e >>= 1) {
            c.first += e & 1 ? a[d].first : 0;
            c.second += e & 1 ? a[d].second : 0;
            d++;
        }
        if(c.first != 0 || c.second != 0) {
            // s[c.first + (j - (i+j)/2) * 10][c.second + (j - (i+j)/2) * 10]++;
            ll f = m[c];
            m[c] = f + 1;
        }
    
    }
    for(ll b = 1; b < (1 << ((i+j)/2 - i)); b++){
        pair<ll, ll> c = {0, 0};
        ll d = i;
        for(ll e=b; e > 0; e >>= 1) {
            c.first -= e & 1 ? a[d].first : 0;
            c.second -= e & 1 ? a[d].second : 0;
            d++;
        }
        if(c.first != 0 || c.second != 0) sum += m[c];
        // sum += s[c.first + (j - (i+j)/2) * 10][c.second + (j - (i+j)/2) * 10];
    }
    return sum;
}

int main() {
    ll n; cin >> n;
    a.resize(n);
    for(ll i=0; i<n; i++) cin >> a[i].first >> a[i].second;
    random_shuffle(a.begin(), a.end());
    cout << combinations(0, n);
}