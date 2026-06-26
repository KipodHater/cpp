#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    string v, t; cin >> v >> t;
    string s = t + '#' + v;
    ll n = v.size() + 1 + t.size();
    vector<ll> pi(n, 0);

    for(ll i=1; i<n; i++) {
        int j = i-1;
        int last = pi[j]-1;
        while(j >= 0) {
            if(s[last+1] == s[i]) {
                pi[i] = pi[j] + 1;
                break;
            }
            j = last;
            last = pi[j]-1;
        }
    }
    ll c = 0;
    for(ll i:pi) c += i == t.size();
    cout << c;
}