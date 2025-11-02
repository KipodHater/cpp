#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll n; cin >> n;
    vector<ll> a(n);
    vector<ll> b(n);
    for(ll i=0; i<n; i++) cin >> a[i] >> b[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    ll i = 0; ll j=0;
    ll c=0;
    ll m=0;
    while(i<n && j<n){
        if(a[i]<=b[j]) {
            c++; i++;
        }
        else  {
            c--; j++;
        }
        m = max(m, c);
    }
    cout << m;
}