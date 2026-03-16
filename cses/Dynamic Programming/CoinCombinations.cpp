 
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1e9+7;

int main() {
	ll n,x; cin>>n>>x;
 
	vector<ll> a(x+1, 0);
    a[0] = 1;
	vector<ll> coins(n);
	for(ll i=0;i<n;i++){
		cin>>coins[i];
	}
 
    sort(coins.begin(), coins.end());
    
    for(ll c : coins) {
        for(ll i=0; i<x+1; i++) {
            if(a[i] != 0 && i+c <= x) {
                a[i+c] += a[i];
                a[i+c] %= MOD;
            }
        } 
    }
    cout << a[x] % MOD;
}