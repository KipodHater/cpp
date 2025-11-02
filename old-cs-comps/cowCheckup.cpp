#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef vector<ll> vll;
// ll N;
// boolean legal(ll left, ll right){
//     return ((right > 0 && right < N) && (left>0 && left<N)) && l<=r;
// }
int main(){
    ll n;
    cin >> n;
    // N = n;
    vll a(n), b(n);
    for(ll i=0; i<n; i++) cin >> a[i];
    for(ll i=0; i<n; i++) cin >> b[i];

    vector<vll> d(n, vll(n, -1)); // r, l

    ll e=0;
    for(ll i=0; i<n; i++){
        if(a[i] == b[i]) e++;
    }
    vll res(n+1, 0);
    for(ll i=0; i<n; i++){ // r
        for(ll j=0; j<=i; j++){ // l
            ll r = i-1;
            ll l = j+1;
            if(((r > 0 && r < n) && (l>0 && l<n)) && l<=r){
                    ll cur = 0;
                    if(a[i] == b[i]) cur++;
                    if(a[j] == b[j]) cur++;
                    ll chan = 0;
                    if(a[j] == b[i]) chan++;
                    if(a[i] == b[j]) chan++;

                    d[i][j] = d[r][l] - cur + chan;
            } else{
                if(i == j){
                    d[i][j] = e;
                } else {
                    ll cur = 0;
                    if(a[i] == b[i]) cur++;
                    if(a[j] == b[j]) cur++;
                    ll chan = 0;
                    if(a[j] == b[i]) chan++;
                    if(a[i] == b[j]) chan++;

                    d[i][j] = e - cur + chan;
                }
            }
            res[d[i][j]]++;
        }
    }

    for(ll i : res) cout<< i << endl; 
}