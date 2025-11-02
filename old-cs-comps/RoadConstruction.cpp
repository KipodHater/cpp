#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 1e9 + 7;
const ll INF = 1e10;
using vll = vector<ll>;
vector<pair<ll, ll>> a;
vll par;
vll sizes;
ll c;

ll dsu(ll ver){
    if(par[ver] == ver) return ver;
    par[ver] = dsu(par[ver]);
    return par[ver];
}
bool un(ll v, ll u){
    ll pv = dsu(v);
    ll pu = dsu(u);
    if(pv == pu) return false;

    if(sizes[pv] < sizes[pu]) swap(pv, pu);
    par[pu] = pv;
    sizes[pv] += sizes[pu];
    c = max(sizes[pv], c);
    return true;
}

int main(){
    ll n, m;
    cin >> n >> m;
    sizes.resize(n+1, 1);
    par.resize(n+1, 0);
    a.resize(m);

    for(ll i=0; i<m; i++) cin >> a[i].first >> a[i].second;
    for(ll i=1; i<n+1; i++) par[i] = i;

    c = 1;
    ll comp = n;
    for(pair<ll, ll> i:a){
        if(un(i.first, i.second)){
            comp--;
        }

        cout << comp << " " << c << endl;
    }
}