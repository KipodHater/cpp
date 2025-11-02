#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);

    
    ll n;
    
    cin >> n;

    vector<ll> x(n);
    vector<ll> y(n);
    for(ll i=0; i<n; i++){
        cin >> x[i] >> y[i];
    }

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    ll resx;
    ll resy;
    if(n%2 != 0){
        resx = x[n/2];
        resy = y[n/2];
    } else{
        resx = x[n/2];
        resy = y[n/2];
    }

     cout << resx << " " << resy; 
}