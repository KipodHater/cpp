#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e10;

struct Seg {
    ll n;
    vector<ll> a, b, c, d;

    Seg(ll x) {
        for(n=1; n<x; n<<1);
        a.resize(n, 0);
        b.resize(n, 0);
        c.resize(n, -INF);
        d.resize(n, INF);
    }

    void update(ll l, ll r, ll ) {
        
    }

    void update(ll l, ll r, ll u) {
        return ;
    }
};

int main() {
    
}