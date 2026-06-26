#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main () {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    ll n; cin >> n;
    priority_queue<pair<ll, ll>> q;
    vector<ll> b(2*n);
    for(ll i=0; i<2*n; i++) {
        cin >> b[i];
        q.push({b[i], i});
    }
    ll m = 0;
    ll i=0; ll j=0;
    while(q.size()) {
        i = q.top().second;
        q.pop();
        j = q.top().second;
        q.pop();
        if(b[i] == -1 || b[j] == -1) {
            continue;
        }
        if(i >= n && j < n) {
            m = max(m, b[i]);
            b[i] = b[j] = -1;
            continue;
        }
        for(ll k = j+1; k<i; k++) {
            m = max(m, b[k]);
            b[k] = -1;
        }
        b[i] = b[j] = -1;
    }
    cout << m; 
}