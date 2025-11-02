#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);// fast input-output
    ll n, f;
    f = 1;
    cin >> n;
    vector<ll> a(n);
    multiset<ll> c;
    set<ll> d;
    for(ll i=0; i<n; i++) cin >> a[i];

    ll b = 0;
    for(ll i=1; i<n; i++){
        if(a[i-1] < a[i]) b++;
        else if(a[i-1] > a[i]) b--;

        if(b!= 0 && a[i] == a[0]){
            c.insert(0);
            d.insert(0);
        }        
        else if(b != 0){
            ll k;
            k = (a[i] - a[0]) / b;
            if((a[i] - a[0]) % b == 0){
            c.insert(k);
            d.insert(k);
            }
        }
        if(a[i] == a[0] && b == 0) f++;
    }
    ll e = 0;
    ll res = 0;
    for(ll i : d){
        if(e <= c.count(i) && i>=0) {
            e = c.count(i);
            res = i;
        }
    }

    cout << e + f << " " << res;
}