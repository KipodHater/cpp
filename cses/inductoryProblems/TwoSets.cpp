#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll n; cin >> n;
    vector<ll> c, d;
    ll a = 0; ll b=0;
    for(int i = n; i>0; i--){
        if(b<a){
            b += i;
            d.push_back(i);
        } else {
            a+= i;
            c.push_back(i);
        }
    }
    if(a == b) {
        cout << "YES" << "\n" << c.size() << "\n";
        for(ll i : c) cout << i << " ";
        cout << "\n";
        cout << d.size() << "\n";
        for(ll i : d) cout << i << " ";
    } else cout << "NO";
}