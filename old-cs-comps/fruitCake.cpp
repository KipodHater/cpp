#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);// fast input-output
    ll n, m, e;
    cin >> n >> m;
    vll a(50001, 0);
    vll b(50001, 0);

    for(ll i=0; i<n-1; i++){
        cin >> e;
        a[e]++;
    } 
    for(ll i=0; i<m-1; i++) {
        cin >> e;
        b[e]++;
    }
    ll sum = 0;
    ll c = 1;
    ll d=1;
    for(ll i=50000; i>0; i--){
        sum += d*a[i] * i;
        c+= a[i];
        sum += c * b[i] * i;
        d+= b[i];
    }
    cout << sum;
}