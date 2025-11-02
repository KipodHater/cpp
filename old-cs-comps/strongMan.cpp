#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll n;
    cin >> n;
    vector<ll> a (n);

    for(ll i=0; i<n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    ll sum = 0;
    for(ll i=1; i<=n; i++){
        sum += i%3 != 0 ? a[n-i] : 0;
    }
    cout << sum; 
}