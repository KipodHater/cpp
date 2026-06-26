#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n, k, x, a, b, c, x1;
    ll d = 1;
    cin >> n >> k >> x >> a >> b >> c;
    for(d=1; c>>d > 0; d++);
    vector<ll> e(d, 0);
    queue<ll> q;
    ll res = 0;
    ll h = 1;
    for(ll i=0; i<k; i++) {
        x1 = x;
        h = 1;
        for(ll j=0; x1>0; j++) {
            e[j] += x1&1;
            if(e[j] == 1 && x1&1) res+= h;
            x1>>=1;
            h <<= 1;
        }
        q.push(x);
        x = (a*x+b) % c;
    }
    ll f;
    f = res;
    ll newRes = 0;
    for(ll i = k; i < n; i++) {
        x1 = q.front();
        ll x2 = x;
        q.pop();
        ll g = 1;
        ll m;
        newRes = 0;
        for(ll j=0; x1>0 || x2>0; j++) {
            m = e[j];
            ll t = 0;
            if(x1&1) t-=1;
            if(x2&1) t+=1;
            e[j] += t;
            if(m^(e[j]>0)) newRes += g;
            if(m == 0 && e[j] > 0) f+= g;
            if(m > 0 && e[j] == 0) f-= g;
            g<<=1;
            x1>>=1;
            x2>>=1;
            // res = newRes;
        }
        res = newRes;
        newRes = f;
        q.push(x);
        x = (a*x+b) % c;
    }
    cout << res;
}