#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int t; cin >> t;
    while (t--) {
        ll n, k; cin >> n >> k;
        vector<ll> a(60, 0);
        vector<ll> b(n);
        for(ll i=0; i<n; i++) cin >> b[i];
        bool flag = false;
        for(ll u:b) {
            ll i = 1;
            ll d = 0;
            while(u > 0) {
                int c = u % k;
                if(c == 1){
                    if(d >= 60) 
                    {
                        flag = true;
                        break;
                    }
                    if(a[d] == 0) {
                        a[d] = 1;
                    } else {
                        flag = true;
                        break;
                    }
                }
                else if (c != 0) {
                    flag = true;
                    break;
                }
                i*=k;
                u/=i;
                d++;
            }
            if(flag) break;
        }
        if(flag) cout << "NO\n";
        else cout << "YES\n";
    }
}