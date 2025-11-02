#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll n, x; cin >> n >> x;
    vector<ll> a(n);
    multiset<ll> s;
    for(ll i=0; i<n; i++) {
        cin >> a[i];
        s.insert(a[i]);
    }
    bool flag = true;
    for(ll i =0; i<n; i++){
        if(s.count(x-a[i]) && !(a[i] == x-a[i] && s.count(x-a[i]) == 1)) {
            ll k;
            for(ll j =0; j<n;j++){
                if(a[i] == x-a[j] && i != j){
                    k=j;
                }
            }
            cout << i + 1 << " " << k + 1;
            
            flag = false;
            break;
        }
    }
    if(flag) cout << "IMPOSSIBLE";
}