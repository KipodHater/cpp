#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n);
    for(ll i=0; i<n; i++) cin >> a[i];
    vector<ll> b(n+1);
    b[n] = 1e10;
    for(ll i=0; i<n; i++) b[a[i]-1] = i;
    ll sum = 0;
    vector<ll> v(n);
    for(ll i=0; i<n-1; i++){
        sum += b[i] > b[i+1] ? 1 : 0;
        v[i] = b[i] < b[i+1];

    }
    while(m--){
        ll c, d;
        cin >> c >> d;
        // swap(a[c], a[d]);
        c--; d--;
        swap(b[a[c]-1], b[a[d]-1]);
        swap(a[c], a[d]);
        if(a[c]<n)
        if(v[a[c]-1] != (c < b[a[c]])){
            sum += v[a[c]-1] ? 1 : -1;
            v[a[c]-1] = c < b[a[c]];
        }
        if(a[c] > 1){
        if(v[a[c]-2] != (c > b[a[c]-2])){
            sum += v[a[c]-2] ? 1 : -1;
            v[a[c]-2] = c > b[a[c]-2];
        }
        }

        if(a[d]<n)
        if(v[a[d]-1] != (d < b[a[d]])){
            sum += v[a[d]-1] ? 1 : -1;
            v[a[d]-1] = d < b[a[d]];
        }
        if(a[d] > 1){
        if(v[a[d]-2] != (d > b[a[d]-2])){
            sum += v[a[d]-2] ? 1 : -1;
            v[a[d]-2] = d > b[a[d]-2];
        }
        }
        cout << sum + 1 << "\n";
    }
}